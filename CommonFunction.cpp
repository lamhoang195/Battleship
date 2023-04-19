#include "CommonFunction.h"

bool SDL_Common::check_overlap(const SDL_Rect& object1, const SDL_Rect& object2)
{
    if(object1.x + object1.w - 5 < object2.x || object2.x + object2.w - 5 < object1.x)//trái + rộng < phải ngược lại
    {
        return false;
    }
    if(object1.y + object1.h < object2.y + 35 || object2.y + object2.h < object1.y + 35)
    {
        return false;
    }
    return true;
};

void SDL_Common::ApplySurface(SDL_Renderer *renderer , SDL_Texture *src, int x, int y, int w, int h)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	offset.h = h;
	offset.w = w;
	SDL_RenderCopy(renderer, src , NULL, &offset);
	SDL_RenderPresent(renderer);
}

