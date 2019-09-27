
set (CMAKE_CXX_STANDARD 14)

set (CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package (SDL2 REQUIRED)
find_package (SDL2_ttf REQUIRED)

add_subdirectory(
  ${CMAKE_CURRENT_SOURCE_DIR}/events
  )

add_subdirectory(
  ${CMAKE_CURRENT_SOURCE_DIR}/fonts
  )

add_subdirectory(
  ${CMAKE_CURRENT_SOURCE_DIR}/textures
  )

set (SOURCES
  ${SOURCES}
  Color.cc
  Palette.cc
  Window.cc
  SdlEngine.cc
  EngineDecorator.cc
  MouseState.cc
  )

add_library (sdl_engine SHARED
  ${SOURCES}
  ${SDL2_INCLUDE_DIR}
  ${SDL2_TTF_INCLUDE_DIRS}
  )

set(SDL_ENGINE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

target_link_libraries(sdl_engine
  ${SDL2_LIBRARY}
  ${SDL2_TTF_LIBRARIES}
  core_utils
  )

target_include_directories (sdl_engine PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/events
  ${CMAKE_CURRENT_SOURCE_DIR}/fonts
  ${CMAKE_CURRENT_SOURCE_DIR}/textures
  ${SDL2_INCLUDE_DIR}
  ${SDL2_TTF_INCLUDE_DIRS}
  )

