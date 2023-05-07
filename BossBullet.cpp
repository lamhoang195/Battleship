#include "BossBullet.h"

BossBullet::BossBullet()
{
    rect_.w = WIDTH_BOSS;
    rect_.h = HEIGHT_BOSS;
    x_speed=0;
    y_speed=0;

    is_move_=false;
    angle=90;
    starting_point=0;
}

BossBullet::~BossBullet()
{

}

void BossBullet::HandleMove(const int &x_border,const int &y_border)
{
    x_pos += x_speed*cos(angle*PI/180);
    y_pos += y_speed*sin(angle*PI/180);
    if(y_pos + 2*height_frame > y_border || y_pos < -500)
    {
        is_move_ = false;
    }
    if(x_pos + width_frame > x_border || x_pos< -500)
    {
        is_move_ = false;
    }
    rect_.x=x_pos;
    rect_.y=y_pos;
}

