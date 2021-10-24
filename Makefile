CC := g++
CCFLAGS += -std=c++11 -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

BUILD_DIR := build
RSDL_DIR := src

all: game.out

game.out: $(BUILD_DIR)/enemy.o $(BUILD_DIR)/gamer.o $(BUILD_DIR)/functions.o $(BUILD_DIR)/tower.o $(BUILD_DIR)/main.o $(BUILD_DIR)/rsdl.o
	$(CC) $(BUILD_DIR)/enemy.o $(BUILD_DIR)/gamer.o $(BUILD_DIR)/functions.o $(BUILD_DIR)/tower.o $(BUILD_DIR)/main.o $(BUILD_DIR)/rsdl.o $(CCFLAGS) -o game.out

$(BUILD_DIR)/tower.o: Tower.cpp $(RSDL_DIR)/rsdl.hpp Tower.hpp
	$(CC) -c Tower.cpp -o $(BUILD_DIR)/tower.o

$(BUILD_DIR)/enemy.o: Enemy.cpp $(RSDL_DIR)/rsdl.hpp Enemy.hpp
		$(CC) -c Enemy.cpp -o $(BUILD_DIR)/enemy.o

$(BUILD_DIR)/functions.o: functions.cpp $(RSDL_DIR)/rsdl.hpp functions.hpp
		$(CC) -c functions.cpp -o $(BUILD_DIR)/functions.o

$(BUILD_DIR)/gamer.o: Gamer.cpp $(RSDL_DIR)/rsdl.hpp Gamer.hpp
				$(CC) -c Gamer.cpp -o $(BUILD_DIR)/gamer.o

$(BUILD_DIR)/main.o: main.cpp $(RSDL_DIR)/rsdl.hpp
				$(CC) -c main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/rsdl.o: $(RSDL_DIR)/rsdl.hpp $(RSDL_DIR)/rsdl.cpp
	$(CC) -c $(RSDL_DIR)/rsdl.cpp -o $(BUILD_DIR)/rsdl.o

.PHONY: clean
clean:
	rm -rf build/ game.out && mkdir -p build
