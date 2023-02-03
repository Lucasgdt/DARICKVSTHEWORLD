CC=gcc
CFLAGS=-Wall -Wextra -I/usr/local/include/SDL2 -D_REENTRANT
LDFLAGS=-L/usr/local/lib -lSDL2 -lSDL2_image

main: move.c
	$(CC) $(CFLAGS) move.c $(LDFLAGS) -o main

clean:
	rm -f main

.PHONY: clean
