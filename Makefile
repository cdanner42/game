# cs335 game
CFLAGS	= -I ./include

all: game script

game: main.cpp ppm.cpp
	g++ $(CFLAGS) main.cpp ppm.cpp -Wall -o game -lX11 -lGL -lGLU -lm -I/usr/X11R6/include -L/usr/X11R6/lib -lX11

clean:
	rm -f game
	rm -f *.o

script:
	export LD_PRELOAD=/usr/lib/x86_64-linux-gnu/mesa/libGL.so.1
