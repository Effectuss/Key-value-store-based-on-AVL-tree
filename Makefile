all: build

rebuild: clean build

build:
	cmake -S . -B ./build -D CMAKE_CXX_COMPILER=g++
	cmake --build ./build
	
run: build
	cd build; ./KeyValueStoreAVLTree

test: build
	cmake --build build --target tests_binary_tree
	cd build/tests; ./tests_binary_tree

check: build
	cmake --build build --target clangformat
	cmake --build build --target cppcheck

clean:
	@rm -rf build
	@cd resources; rm -f tree_100_elements.dot tree_with_delet_node.dot
