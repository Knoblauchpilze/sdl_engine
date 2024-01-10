
target_include_directories (sdl_engine PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/events
	)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/fonts
	)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/textures
	)

target_sources (sdl_engine PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Color.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Palette.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Window.cc
	${CMAKE_CURRENT_SOURCE_DIR}/SdlEngine.cc
	${CMAKE_CURRENT_SOURCE_DIR}/EngineDecorator.cc
	${CMAKE_CURRENT_SOURCE_DIR}/MouseState.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Gradient.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Brush.cc
)
