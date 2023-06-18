build:
	g++ main.cpp interface.cpp -o main -std=c++11 -I/opt/homebrew/Cellar/sdl2/2.26.5/include -L/opt/homebrew/Cellar/sdl2/2.26.5/lib -I/opt/homebrew/Cellar/sdl2_image/2.6.3_1/include -L/opt/homebrew/Cellar/sdl2_image/2.6.3_1/lib -lSDL2 -lSDL2_image
.PHONY: build

debug:
	g++ main.cpp interface.cpp -o -g -Wall main -std=c++11 -I/opt/homebrew/Cellar/sdl2/2.26.5/include -L/opt/homebrew/Cellar/sdl2/2.26.5/lib -I/opt/homebrew/Cellar/sdl2_image/2.6.3_1/include -L/opt/homebrew/Cellar/sdl2_image/2.6.3_1/lib -lSDL2 -lSDL2_image
.PHONY: debug

buildw32:
# pick which cmd you use and delete the other
# then to compile use `make buildw32`
	g++ -IC:/Users/new/OneDrive/Desktop/projects/libs/SDLinclude -LC:/Users/new/OneDrive/Desktop/projects/libs/SDLlibs -o main main.cpp interface.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	g++ -IC:/projects/libs/SDLinclude -LC:/projects/libs/SDLlibs -o main main.cpp interface.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
.PHONY: buildw32