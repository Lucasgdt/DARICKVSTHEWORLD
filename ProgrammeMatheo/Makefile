CC = gcc
CFLAGS = -Wall
SDL_DIR = C:/SDL2
SDLLIB_DIR = $(SDL_DIR)/lib
SDLINC_DIR = $(SDL_DIR)/include

LIBS = -L$(SDLLIB_DIR) -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES = -I$(SDLINC_DIR)

all: jeu.exe

jeu.exe: menu.o move.o inventaire.o main.o personnage.o mob.o action.o name.o outil.o 
	$(CC) $(CFLAGS) menu.o move.o inventaire.o main.o personnage.o mob.o action.o name.o outil.o -o jeu.exe -lm -lmingw32 $(LIBS) $(INCLUDES) 

menu.o: menu.c
	$(CC) $(CFLAGS) -c menu.c $(INCLUDES)

move.o: move.c
	$(CC) $(CFLAGS) -c move.c $(INCLUDES)

inventaire.o: inventaire.c
	$(CC) $(CFLAGS) -c inventaire.c $(INCLUDES)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(INCLUDES)

personnage.o : personnage.c
	$(CC) $(CFLAGS) -c personnage.c $(INCLUDES)

mob.o : mob.c
	$(CC) $(CFLAGS) -c mob.c $(INCLUDES)

action.o : action.c
	$(CC) $(CFLAGS) -c action.c $(INCLUDES)

name.o : name.c
	$(CC) $(CFLAGS) -c name.c $(INCLUDES)

outil.o : outil.c
	$(CC) $(CFLAGS) -c outil.c $(INCLUDES)

clean:
	rm -f *.o jeu.exe