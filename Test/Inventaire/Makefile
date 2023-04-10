CC=gcc
CFLAGS=-Wall
SDL_DIR=E:/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include


LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR} 

all: test_inventaire_exec

test_inventaire_exec: inventaire.o personnage.o mob.o outil.o test_inventaire.o
	$(CC) $(CFLAGS) inventaire.o personnage.o mob.o outil.o test_inventaire.o -o test_inventaire_exec ${LIBS} ${INCLUDES}

test_inventaire.o: test_inventaire.c
	$(CC) $(CFLAGS) -c test_inventaire.c ${LIBS} ${INCLUDES}

personnage.o: personnage.c
	$(CC) $(CFLAGS) -c personnage.c ${LIBS} ${INCLUDES}

mob.o: mob.c
	$(CC) $(CFLAGS) -c mob.c ${LIBS} ${INCLUDES}

outil.o: outil.c
	$(CC) $(CFLAGS) -c outil.c ${LIBS} ${INCLUDES}

inventaire.o: inventaire.c
	$(CC) $(CFLAGS) -c inventaire.c ${LIBS} ${INCLUDES}

clean:
	del -f *.o test_inventaire_exec.exe
