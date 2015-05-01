# cs335 game
CFLAGS	= -I ./include
LIB	= ./libggfonts.so

all: game

game: main.cpp ppm.cpp GameEngine.cpp IntroState.cpp PlayState.cpp
	g++ $(CFLAGS) main.cpp ppm.cpp GameEngine.cpp  IntroState.cpp PlayState.cpp -Wall $(LIB) -o game -lX11 -lGL -lm -I/usr/X11R6/include -L/usr/X11R6/lib -lX11

clean:
	rm -f game
	rm -f *.o

