CC=g++

CFLAGS=-c -Wall

LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net


all: patrik

clean:
	rm -rf patrik *.o

patrik: core.o map.o character.o enemy.o player.o patrik.o
	$(CC) core.o map.o character.o enemy.o player.o patrik.o -o patrik $(LDFLAGS)

core.o: core.cpp
	$(CC) $(CFLAGS) core.cpp

map.o: map.cpp
	$(CC) $(CFLAGS) map.cpp

character.o:
	$(CC) $(CFLAGS) character.cpp

player.o: player.cpp
	$(CC) $(CFLAGS) player.cpp

enemy.o: enemy.cpp
	$(CC) $(CFLAGS) enemy.cpp

sdl_patrick.o: sdl_patrick.cpp
	$(CC) $(CFLAGS) sdl_patrick.cpp



	
