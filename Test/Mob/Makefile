CC=gcc
CFLAGS=-Wall
SDL_DIR=E:/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include


LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR} 

all: test_mob_exec

test_mob_exec: move.o mob.o outil.o test_mob.o
	$(CC) $(CFLAGS) move.o mob.o outil.o test_mob.o -o test_mob_exec ${LIBS} ${INCLUDES}

test_mob.o: test_mob.c
	$(CC) $(CFLAGS) -c test_mob.c ${LIBS} ${INCLUDES}

mob.o: mob.c
	$(CC) $(CFLAGS) -c mob.c ${LIBS} ${INCLUDES}

outil.o: outil.c
	$(CC) $(CFLAGS) -c outil.c ${LIBS} ${INCLUDES}

move.o: move.c
	$(CC) $(CFLAGS) -c move.c ${LIBS} ${INCLUDES}

move.o: move.c
	$(CC) $(CFLAGS) -c move.c ${LIBS} ${INCLUDES}

clean:
	del -f *.o test_mob_exec.exe
