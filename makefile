CC=gcc
FLAGS=-Wall -g

SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2 image -lSDL2 ttf


INCS=-I${SDL_INC_DIR}
PROG=interface

all: interface

sdl_text: interface.c
	${CC} -o ${PROG} interface.c ${LIBS} ${INCS} ${FLAGS}
clean:
	rm -f ${PROG}
	rm -f *.o