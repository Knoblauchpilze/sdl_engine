
target_include_directories (sdl_engine PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)

target_sources (sdl_engine PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/EventFactory.cc
	${CMAKE_CURRENT_SOURCE_DIR}/EngineObject.cc
	${CMAKE_CURRENT_SOURCE_DIR}/EventsDispatcher.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Event.cc
	${CMAKE_CURRENT_SOURCE_DIR}/DropEvent.cc
	${CMAKE_CURRENT_SOURCE_DIR}/EnterEvent.cc
	${CMAKE_CURRENT_SOURCE_DIR}/FocusEvent.cc
	${CMAKE_CURRENT_SOURCE_DIR}/HideEvent.cc
	${CMAKE_CURRENT_SOURCE_DIR}/KeyEvent.cc
	${CMAKE_CURRENT_SOURCE_DIR}/KeyUtils.cc
	${CMAKE_CURRENT_SOURCE_DIR}/MouseEvent.cc
	${CMAKE_CURRENT_SOURCE_DIR}/PaintEvent.cc
	${CMAKE_CURRENT_SOURCE_DIR}/QuitEvent.cc
	${CMAKE_CURRENT_SOURCE_DIR}/ResizeEvent.cc
	${CMAKE_CURRENT_SOURCE_DIR}/WindowEvent.cc
	)
