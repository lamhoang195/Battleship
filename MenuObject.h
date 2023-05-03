#ifndef MENU_OBJECT_H
#define MENU_OBJECT_H

#include "BaseObject.h"
#include "TextObject.h"
#include "CommonFunction.h"

namespace MenuObject
{
    bool LoadImg(std::string path, SDL_Renderer* screen);
    int ShowMenu(SDL_Renderer* screen, TTF_Font* font, BaseObject gBackground);
}

#endif // MENU_OBJECT_H
