#pragma once

#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_video.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//Man hinh
const int SCREEN_WIDTH = 1200;// chieu rong
const int SCREEN_HEIGHT = 720;//chieu cao
const int SCREEN_BPP = 32;//pixel

const int COLOR_KEY_R =167;//mau
const int COLOR_KEY_G =175;
const int COLOR_KEY_B =180;

const int RENDER_DRAW_COLOR = 0xff;

#endif // COMMON_FUNCTION_H





