CC=gcc
BUILD_DIR=build
INCLUDE_DIR=-Isrc

all: main.cpp src/*.cpp $(BUILD_DIR)
	$(CC) -std=c++20 -O2 $(INCLUDE_DIR) main.cpp src/*.cpp -o $(BUILD_DIR)/main -lstdc++

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

test1: all input_files/test1.txt
	./build/main input_files/test1.txt

test2: all input_files/test2.txt
	./build/main input_files/test2.txt

clean:
	rm -r build
