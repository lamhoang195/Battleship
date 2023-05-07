#include "EnemyBullet.h"

EnemyBullet::EnemyBullet() {
    rect_.w = ENEMY_BULLET_WIDTH;
    rect_.h = ENEMY_BULLET_HEIGHT;
}
EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::HandleBullet( const int &x_border, const int &y_border )
{
    switch(bullet_type_){
    case 0://đạn thẳng
    {
        rect_.y += 3;
        if (rect_.y > y_border) {
            is_move_ = false;
        }
    }
        break;
    default:
        break;
    }
}
