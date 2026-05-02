#include "assetmanager.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "texture_streamer.h"
#include "uthash.h"

TextureEntry* texture_map = NULL;

ManagedTexture* asset_get_texture(const char* path) {
  if (!path) return NULL;
  TextureEntry* entry = NULL;

  HASH_FIND_STR(texture_map, path, entry);

  if (!entry) {
    entry = malloc(sizeof(TextureEntry));
    if (!entry) return NULL;
    entry->key = strdup(path);
    if (!entry->key) {
      free(entry);
      return NULL;
    }
    entry->managed.refCount = 1;
    entry->managed.texture = LoadTexture(path);
    entry->managed.loaded = (entry->managed.texture.id != 0);
    HASH_ADD_KEYPTR(hh, texture_map, entry->key, strlen(entry->key), entry);

    // static const char *pending_path = NULL;

    // pending_path = entry->key;
    // loader_start(&pending_path, 1);

  } else {
    entry->managed.refCount++;
  }

  return &entry->managed;
}

void asset_release_texture(const char* path) {
  TextureEntry* entry = NULL;
  HASH_FIND_STR(texture_map, path, entry);

  if (!entry) {
    return;
  }

  if (entry->managed.refCount <= 0) {
    return;
  }

  entry->managed.refCount--;

  if (entry->managed.refCount <= 0) {
    UnloadTexture(entry->managed.texture);
    HASH_DEL(texture_map, entry);

    free((void*)entry->key);
    free(entry);
  }
}

void asset_manager_shutdown(void) {
  TextureEntry *entry, *tmp;

  HASH_ITER(hh, texture_map, entry, tmp) {
    UnloadTexture(entry->managed.texture);
    HASH_DEL(texture_map, entry);
    free((void*)entry->key);
    free(entry);
  }
  texture_map = NULL;
}
