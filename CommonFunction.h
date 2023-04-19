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
	bool check_overlap(const SDL_Rect& object1, const SDL_Rect& object2);

	void ApplySurface(SDL_Renderer *renderer, SDL_Texture *src, int x, int y, int w, int h);
}

#endif // COMMON_FUNCTION_H
