build:
	g++ main.cpp interface.cpp textures.cpp -o main -std=c++11 -I/opt/homebrew/Cellar/sdl2/2.26.5/include -L/opt/homebrew/Cellar/sdl2/2.26.5/lib -I/opt/homebrew/Cellar/sdl2_image/2.6.3_1/include -L/opt/homebrew/Cellar/sdl2_image/2.6.3_1/lib -lSDL2 -lSDL2_image
.PHONY: build