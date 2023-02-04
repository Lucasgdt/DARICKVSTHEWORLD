CC=gcc
CFLAGS=-Wall -Wextra -I/usr/local/include/SDL2 -D_REENTRANT
LDFLAGS=-L/usr/local/lib -lSDL2 -lSDL2_image

main: main.c move.c move.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o main main.c move.c

clean:
	rm -f main

.PHONY: clean
