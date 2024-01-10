
target_include_directories (sdl_engine PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)

target_sources (sdl_engine PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/FontCache.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Font.cc
	${CMAKE_CURRENT_SOURCE_DIR}/ColoredFont.cc
	${CMAKE_CURRENT_SOURCE_DIR}/FontFactory.cc
	)
