cmake_minimum_required(VERSION 3.20)

project(amiga_demo_v1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(APPLE)
  list(APPEND CMAKE_PREFIX_PATH
    /opt/homebrew
    /usr/local
  )
endif()

set(DEMO_SDL2_TARGET "")
set(DEMO_SDL2_MIXER_TARGET "")

find_package(SDL2 CONFIG QUIET)
if(TARGET SDL2::SDL2)
  set(DEMO_SDL2_TARGET SDL2::SDL2)
elseif(TARGET SDL2::SDL2-static)
  set(DEMO_SDL2_TARGET SDL2::SDL2-static)
endif()

find_package(SDL2_mixer CONFIG QUIET)
if(TARGET SDL2_mixer::SDL2_mixer)
  set(DEMO_SDL2_MIXER_TARGET SDL2_mixer::SDL2_mixer)
elseif(TARGET SDL2_mixer::SDL2_mixer-static)
  set(DEMO_SDL2_MIXER_TARGET SDL2_mixer::SDL2_mixer-static)
endif()

if(NOT DEMO_SDL2_TARGET OR NOT DEMO_SDL2_MIXER_TARGET)
  find_package(PkgConfig REQUIRED)
endif()

if(NOT DEMO_SDL2_TARGET)
  pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
  set(DEMO_SDL2_TARGET PkgConfig::SDL2)
endif()

if(NOT DEMO_SDL2_MIXER_TARGET)
  pkg_check_modules(SDL2_MIXER REQUIRED IMPORTED_TARGET SDL2_mixer)
  set(DEMO_SDL2_MIXER_TARGET PkgConfig::SDL2_MIXER)
endif()

add_executable(amiga_demo
  src/main.cpp
  src/app.cpp
  src/audio.cpp
  src/copper.cpp
  src/fire.cpp
  src/plasma.cpp
  src/renderer.cpp
  src/scroller.cpp
  src/starfield.cpp
  src/timeline.cpp
)

target_include_directories(amiga_demo PRIVATE src)

target_link_libraries(amiga_demo PRIVATE
  ${DEMO_SDL2_TARGET}
  ${DEMO_SDL2_MIXER_TARGET}
)

if(APPLE)
  target_link_libraries(amiga_demo PRIVATE
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
  )
endif()
