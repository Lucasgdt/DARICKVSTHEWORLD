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


SDL_Rect moveCam(SDL_Rect camera, SDL_Rect * player){
  if( player->x < SCREEN_WIDTH/3 ){
    if(camera.x > 0)
    { camera.x -= 1;
      player->x += 10;
      }
    else
      camera.x = 0;
  }
  else if( player->x > (SCREEN_WIDTH - SCREEN_WIDTH/3) ){
    if(camera.x < TILES_X - SCREEN_WIDTH/SIZE_TILES)
    { camera.x += 1;
      player->x -= 10;
      }
    else 
      camera.x = TILES_X - SCREEN_WIDTH/SIZE_TILES;
  }
  if( player->y < SCREEN_HEIGHT/3 ){
    if( camera.y > 0 )
    { camera.y -= 1;
      player->y += 10;
      }
    else
      camera.y = 0;
  }
  if( player->y > (SCREEN_HEIGHT - SCREEN_HEIGHT/3 ) ){
    if(camera.x < TILES_Y - SCREEN_HEIGHT/SIZE_TILES)
    { camera.y += 1;
      player->y -= 10;
      }
    else
      camera.y = TILES_Y - SCREEN_HEIGHT/SIZE_TILES;
  }


  return(camera);
}


int move(coord_t dir, SDL_Rect * destRect, TILE_MAP map[TILES_X][TILES_Y])
{ 

  

  if (dir.up && ( map[destRect->x /SIZE_TILES][(destRect->y - 1) / SIZE_TILES].mur == 0)) {
    destRect->y -= 1;
  }
  if (dir.down && ( map[destRect->x /SIZE_TILES][((destRect->y + destRect->h)) / SIZE_TILES].mur == 0) ) {
    destRect->y += 1;
  }
  if (dir.left && ( map[(destRect->x - 1) /SIZE_TILES][destRect->y / SIZE_TILES].mur == 0 ) ) {
    destRect->x -= 1;
  }
  if (dir.right && ( map[((destRect->x + destRect->w)) /SIZE_TILES][destRect->y / SIZE_TILES].mur == 0 ) ){
    destRect->x += 1;
  }

  SDL_Delay(1000 / (speed * 10));
  return 1;
}


