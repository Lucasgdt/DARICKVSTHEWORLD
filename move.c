#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "move.h"
int move(coord_t dir, SDL_Rect * destRect)
{

  if (dir.up && destRect->y > 0) {
    destRect->y -= 1;
  }
  if (dir.down && destRect->y < (SCREEN_HEIGHT - DARICK_SIZE)) {
    destRect->y += 1;
  }
  if (dir.left && destRect->x > 0) {
    destRect->x -= 1;
  }
  if (dir.right && destRect->x < (SCREEN_WIDTH - DARICK_SIZE)) {
    destRect->x += 1;
  }

  SDL_Delay(1000 / (speed * 10));
  return 1;
}


