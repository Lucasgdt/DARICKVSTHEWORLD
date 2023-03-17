#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "move.h"
#include "joueur.h"
#include "environnement.h"


int move(coord_t dir, SDL_Rect * destRect, Tile_t ** Map_Rect)
{ 
  if (dir.up && Map_Rect[destRect->x/ZOOM][(destRect->y-2)/ZOOM].mur == 0) {
    destRect->y -= 1;
  }
  if (dir.down && Map_Rect[destRect->x/ZOOM][(destRect->y+2)/ZOOM].mur == 0) {
    destRect->y += 1;
  }
  if (dir.left && Map_Rect[(destRect->x-2)/ZOOM][destRect->y/ZOOM].mur == 0) {
    destRect->x -= 1;
  }
  if (dir.right && Map_Rect[(destRect->x+2)/ZOOM][destRect->y/ZOOM].mur == 0){
    destRect->x += 1;
  }

  SDL_Delay(1000 / (speed * 10));
  return 1;
}


