CC=gcc
CFLAGS=-Wall
SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include


LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR} 

all: jeu

jeu: menu.o move.o inventaire.o main.o personnage.o mob.o action.o name.o outil.o
	$(CC) $(CFLAGS) menu.o move.o inventaire.o main.o personnage.o mob.o action.o name.o outil.o -o jeu -lm ${LIBS} ${INCLUDES}

menu.o: menu.c
	$(CC) $(CFLAGS) -c menu.c ${LIBS} ${INCLUDES}

move.o: move.c
	$(CC) $(CFLAGS) -c move.c ${LIBS} ${INCLUDES}

inventaire.o: inventaire.c
	$(CC) $(CFLAGS) -c inventaire.c ${LIBS} ${INCLUDES}

main.o: main.c
	$(CC) $(CFLAGS) -c main.c ${LIBS} ${INCLUDES}

personnage.o : personnage.c
	$(CC) $(CFLAGS) -c personnage.c ${LIBS} ${INCLUDES}

mob.o : mob.c
	$(CC) $(CFLAGS) -c mob.c ${LIBS} ${INCLUDES}

action.o : action.c
	$(CC) $(CFLAGS) -c action.c ${LIBS} ${INCLUDES}

name.o : name.c
	$(CC) $(CFLAGS) -c name.c ${LIBS} ${INCLUDES}

outil.o : outil.c
	$(CC) $(CFLAGS) -c outil.c ${LIBS} ${INCLUDES}

clean:
	rm -f *.o jeu
