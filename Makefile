all: build

rebuild: clean build

build:
	cmake -S . -B ./build
	cmake --build ./build
	
run: build
	cd build; ./KeyValueStoreAVLTree

check: build
	cmake --build build --target clangformat
	cmake --build build --target cppcheck

clean:
	@rm -rf build
