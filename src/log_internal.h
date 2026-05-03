#pragma once
#include "stdbool.h"

typedef enum {
  _LOG_ENGINE,
  _LOG_GAME,
  _LOG_LUA,
  _LOG_ASSET
} _LogType;

typedef enum {
  _LOG_LEVEL_INFO,
  _LOG_LEVEL_WARN,
  _LOG_LEVEL_ERROR,
} _LogLevel;

void _log_msg(_LogType type, _LogLevel level, const char *fmt, ...);

extern bool log_show_engine;
extern bool log_show_lua;
extern bool log_show_alert;
