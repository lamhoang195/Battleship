#include "BossBullet.h"

BossBullet::BossBullet()
{
    rect_.w = WIDTH_BOSS;
    rect_.h = HEIGHT_BOSS;
}

BossBullet::~BossBullet()
{

}

void BossBullet::HandleBulletBoss(const int &x_border, const int &y_border)
{
    switch(bullet_boss_type_)
    {
        case 0://đạn thẳng
        {
            rect_.y += 2;
            if (rect_.y > y_border)
            {
                is_move_ = false;
            }
        }
            break;
    }
}


