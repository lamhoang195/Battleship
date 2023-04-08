#include "CommonFunction.h"

bool SDL_Common::player_bullet_overlap_enemy(const SDL_Rect& playerlaser, const SDL_Rect& threats) {
    if (playerlaser.y - threats.y >= 0 && playerlaser.y - threats.y <= 74 && playerlaser.x - threats.x > 36 &&  playerlaser.x - threats.x < (80 - 11))
    {
        return true;
    }
    if (playerlaser.y - threats.y >= 0 && playerlaser.y - threats.y < 60 && ((playerlaser.x - threats.x >= 0 && playerlaser.x - threats.x <= 36)
                                                                       || (playerlaser.x - threats.x >= 80 && playerlaser.x - threats.x<=103)))
    {
        return true;
    }
    return false;
}

bool SDL_Common::enemy_bullet_overlap_player_object(const SDL_Rect& enemybullet, const SDL_Rect& playerobject)
{
    if (playerobject.y - enemybullet.y < 25 && enemybullet.x - playerobject.x > 52 && enemybullet.x - playerobject.x < 60)
        return true;
    if (playerobject.y - enemybullet.y < 21 && enemybullet.x - playerobject.x > 80 && enemybullet.x - playerobject.x < 90)
        return true;
    if (playerobject.y - enemybullet.y < 35 && ((enemybullet.x - playerobject.x > 0 && enemybullet.x - playerobject.x < 10)
                                            || ( enemybullet.x - playerobject.x > 100 && enemybullet.x - playerobject.x < 112)))
        return true;
    return false;
}

bool SDL_Common::two_objects_overlap(const SDL_Rect& object1, const SDL_Rect& object2)
{
    if(object1.x + object1.w - 5 < object2.x || object2.x + object2.w < object1.x)
    {
        return false;
    }
    if(object1.y + object1.h < object2.y + 22 || object2.y + object2.h < object1.y + 22)
    {
        return false;
    }
    return true;
};
