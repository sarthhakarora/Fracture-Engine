cmake_minimum_required(VERSION 3.10)

project(FractureEngine C)

set(CMAKE_C_STANDARD 11)

# -------------------------
# ENGINE LIB
# -------------------------
add_library(engine STATIC
    src/engine.c
    src/scene.c
    src/entity.c
    src/camera.c
    src/log.c
    src/assetmanager.c
    src/texture_streamer.c
    src/platform/platform_win32.c
    src/platform/platform_win32_threading.c
)

# -------------------------
# INCLUDE DIRS
# -------------------------
target_include_directories(engine PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

# -------------------------
# LINK PREBUILT RAYLIB
# -------------------------
target_link_libraries(engine PUBLIC
    ${CMAKE_SOURCE_DIR}/lib/libraylib.a
)

# -------------------------
# WINDOWS SYSTEM LIBS
# -------------------------
if (WIN32)
    target_link_libraries(engine PUBLIC
        winmm
        gdi32
        opengl32
    )
endif()
