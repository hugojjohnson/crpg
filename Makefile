reset:
	rm -fR build
	mkdir build
	cd build && cmake .. && make
	cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON