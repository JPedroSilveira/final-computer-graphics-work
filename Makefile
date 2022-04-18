FLAGS=-lrt -lm -ldl -lX11 -lpthread -lXrandr -lXinerama -lXxf86vm -lXcursor
AUX_SOURCES=src/glad.c src/textrendering.cpp src/tiny_obj_loader.cpp src/stb_image.cpp ./lib-linux/libglfw3.a 
AUX_HEADERS=include/matrices.h include/utils.h include/dejavufont.h include/stb_image.h

GAME_SOURCE_PATH=src/game/Sources
GAME_HEADER_PATH=src/game/Headers

GAME_SOURCES=$(GAME_SOURCE_PATH)/object.cpp
GAME_HEADERS=$(GAME_HEADER_PATH)/object.h

./bin/Linux/main: src/main.cpp src/glad.c src/textrendering.cpp $(AUX_HEADERS) $(GAME_HEADERS)
	mkdir -p bin/Linux
	g++ -std=c++11 -Wall -Wno-unused-function -g -I ./include/ -o ./bin/Linux/main src/main.cpp $(AUX_SOURCES) $(GAME_SOURCES) $(FLAGS)

.PHONY: clean run
clean:
	rm -f bin/Linux/main

run: ./bin/Linux/main
	cd bin/Linux && ./main
