reset:
	rm -fR build
	mkdir build
	cp backups/first_world.json build/out.json
	cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	cd build && cmake .. && make

json:
	cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON