
target_include_directories (sdl_engine PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)

target_sources (sdl_engine PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Image.cc
	${CMAKE_CURRENT_SOURCE_DIR}/BasicTexture.cc
	${CMAKE_CURRENT_SOURCE_DIR}/FileTexture.cc
	${CMAKE_CURRENT_SOURCE_DIR}/SurfaceTexture.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Texture.cc
	)
