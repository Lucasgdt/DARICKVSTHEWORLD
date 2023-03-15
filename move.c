#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "move.h"
#include "joueur.h"
#include "environnement.h"





int move(coord_t dir, SDL_Rect * destRect, int map[TILES_X][TILES_Y])
{ 
  int transpose[TILES_X][TILES_Y];
  // computing the transpose
    for (int i = 0; i < TILES_X; ++i)
        for (int j = 0; j < TILES_Y; ++j) {
            transpose[j][i] = map[i][j];
    }
  map = transpose;
  

  if (dir.up && ( map[destRect->x /SIZE_TILES][(destRect->y - 1) / SIZE_TILES] == 1 || map[destRect->x /SIZE_TILES][(destRect->y - 1) / SIZE_TILES] == 9 ) ) {
    destRect->y -= 1;
  }
  if (dir.down && ( map[destRect->x /SIZE_TILES][((destRect->y + destRect->h)) / SIZE_TILES] == 1 || map[destRect->x /SIZE_TILES][((destRect->y + destRect->h)) / SIZE_TILES] == 9 ) ) {
    destRect->y += 1;
  }
  if (dir.left && ( map[(destRect->x - 1) /SIZE_TILES][destRect->y / SIZE_TILES] == 1 || map[(destRect->x - 1) /SIZE_TILES][destRect->y / SIZE_TILES] == 9 ) ) {
    destRect->x -= 1;
  }
  if (dir.right && ( map[((destRect->x + destRect->w)) /SIZE_TILES][destRect->y / SIZE_TILES] == 1 || map[((destRect->x + destRect->w)) /SIZE_TILES][destRect->y / SIZE_TILES] == 9 ) ){
    destRect->x += 1;
  }

  SDL_Delay(1000 / (speed * 10));
  return 1;
}


