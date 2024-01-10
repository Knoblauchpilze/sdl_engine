debug:
	mkdir -p build/Debug && cd build/Debug && cmake -DCMAKE_BUILD_TYPE=Debug ../.. && make -j 8

release:
	mkdir -p build/Release && cd build/Release && cmake -DCMAKE_BUILD_TYPE=Release ../.. && make -j 8

clean:
	rm -rf build

cleanInstall:
	sudo rm -rf /usr/local/include/sdl_engine
	sudo rm -rf /usr/local/lib/libsdl_engine.so

r: release

d: debug

copyRelease:
	sudo cp build/Release/lib/libsdl_engine.so /usr/local/lib

copyDebug:
	sudo cp build/Debug/lib/libsdl_engine.so /usr/local/lib

copyHeaders:
	sudo mkdir -p /usr/local/include/sdl_engine
	sudo cp src/*.hh /usr/local/include/sdl_engine
	sudo cp src/*.hxx /usr/local/include/sdl_engine
	sudo cp src/events/*.hh /usr/local/include/sdl_engine
	sudo cp src/events/*.hxx /usr/local/include/sdl_engine
	sudo cp src/fonts/*.hh /usr/local/include/sdl_engine
	sudo cp src/fonts/*.hxx /usr/local/include/sdl_engine
	sudo cp src/textures/*.hh /usr/local/include/sdl_engine
	sudo cp src/textures/*.hxx /usr/local/include/sdl_engine

install: r copyRelease copyHeaders

installD: d copyDebug copyHeaders
