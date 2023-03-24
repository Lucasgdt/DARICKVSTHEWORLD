
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef CAM_H
#define CAM_H



#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


int FocusScrollBox(Map_t * loaded_map, Sprite* sp,int x, int y, int w, int h);
void ClampScroll(Map_t * loaded_map);
int UpdateScroll(Map_t * loaded_map);

#endif