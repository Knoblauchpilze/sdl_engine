# FindSDL2_ttf
# ---------
#
# Purpose: Locate SDL2_ttf library
#
# This module defines:
#
# SDL2_TTF_LIBRARIES       - the name of the library to link against
# SDL2_TTF_FOUND           - if false, do not try to link to SDL
# SDL2_TTF_INCLUDE_DIRS    - where to find SDL.h
# SDL2_TTF_VERSION_STRING  - human-readable string containing the version of SDL

if(NOT SDL2_TTF_DIR)
  set(SDL2_TTF_DIR "" CACHE PATH "SDL2 directory")
endif()

find_path(SDL2_TTF_INCLUDE_DIR SDL_ttf.h
  HINTS
    ENV SDLTTFDIR
    ${SDL2_TTF_DIR}
  PATH_SUFFIXES SDL2
                # path suffixes to search inside ENV{SDLDIR}
                include/SDL2 include
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(VC_LIB_PATH_SUFFIX lib/x64)
else()
  set(VC_LIB_PATH_SUFFIX lib/x86)
endif()

find_library(
  SDL2_TTF_LIBRARY
  NAMES SDL2_ttf
  HINTS
    ENV SDLTTFDIR
    ${SDL2_TTF_DIR}
  PATH_SUFFIXES lib ${VC_LIB_PATH_SUFFIX}
)


if(SDL2_TTF_INCLUDE_DIR AND EXISTS "${SDL2_TTF_INCLUDE_DIR}/SDL_ttf.h")
  file(STRINGS "${SDL2_TTF_INCLUDE_DIR}/SDL_ttf.h" SDL2_TTF_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_TTF_MAJOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_TTF_INCLUDE_DIR}/SDL_ttf.h" SDL2_TTF_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL_TTF_MINOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_TTF_INCLUDE_DIR}/SDL_ttf.h" SDL2_TTF_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL_TTF_PATCHLEVEL[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+SDL_TTF_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_TTF_VERSION_MAJOR "${SDL2_TTF_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_TTF_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_TTF_VERSION_MINOR "${SDL2_TTF_VERSION_MINOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_TTF_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" SDL2_TTF_VERSION_PATCH "${SDL2_TTF_VERSION_PATCH_LINE}")

  set(SDL2_TTF_VERSION_STRING ${SDL2_TTF_VERSION_MAJOR}.${SDL2_TTF_VERSION_MINOR}.${SDL2_TTF_VERSION_PATCH})
  unset(SDL2_TTF_VERSION_MAJOR_LINE)
  unset(SDL2_TTF_VERSION_MINOR_LINE)
  unset(SDL2_TTF_VERSION_PATCH_LINE)
  unset(SDL2_TTF_VERSION_MAJOR)
  unset(SDL2_TTF_VERSION_MINOR)
  unset(SDL2_TTF_VERSION_PATCH)
endif()

set(SDL2_TTF_LIBRARIES ${SDL2_TTF_LIBRARY})
set(SDL2_TTF_INCLUDE_DIRS ${SDL2_TTF_INCLUDE_DIR})

find_package_handle_standard_args(SDL2_ttf
                                  REQUIRED_VARS SDL2_TTF_LIBRARIES SDL2_TTF_INCLUDE_DIRS
                                  VERSION_VAR SDL2_TTF_VERSION_STRING)

mark_as_advanced(SDL2_TTF_LIBRARY SDL2_TTF_INCLUDE_DIR)