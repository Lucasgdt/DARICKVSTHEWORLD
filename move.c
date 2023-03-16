#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "move.h"
#include "joueur.h"
#include "environnement.h"

/*

void centerCam(SDL_Rect player, SDL_Point * viewOffset, coord_t dir){
  SDL_Point viewFocus;
  viewFocus.x = player.x;
  viewFocus.y = player.y;
  viewOffset->x = viewFocus.x + speed;
  viewOffset->y = viewFocus.y + speed;

}

*/

int move(coord_t dir, SDL_Rect * destRect)
{ 

  

  if (dir.up) {
    destRect->y -= 1;
  }
  if (dir.down) {
    destRect->y += 1;
  }
  if (dir.left) {
    destRect->x -= 1;
  }
  if (dir.right){
    destRect->x += 1;
  }

  SDL_Delay(1000 / (speed * 10));
  return 1;
}


