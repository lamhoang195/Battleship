#pragma once

#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_video.h>
using namespace std;

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//Man hinh
const int FRAME_PER_SECOND = 200;
const int SCREEN_WIDTH = 1000;// chieu rong
const int SCREEN_HEIGHT = 720;//chieu cao
const int SCREEN_BPP = 32;//pixel
const int NUM_MAX_THREATS = 5;//số lượng máy bay

namespace SDL_Common
{
    bool player_bullet_overlap_enemy(const SDL_Rect& playerlaser, const SDL_Rect& threats);
	bool enemy_bullet_overlap_player_object(const SDL_Rect& enemybullet, const SDL_Rect& playerobject);
	bool two_objects_overlap(const SDL_Rect& object1, const SDL_Rect& object2);
}

#endif // COMMON_FUNCTION_H
