#include "ThreatsObject.h"
#include <ctime>

ThreatsObject::ThreatsObject()
{
    rect_.x = rand() % SCREEN_WIDTH;//vi tri dau threat xuat hien
    rect_.y = -HEIGHT_BLACKK4;
    rect_.w = WIDTH_BLACKK4;
    rect_.h = HEIGHT_BLACKK4;

    x_val_ = 0;
    y_val_ = 0;
}

ThreatsObject::~ThreatsObject()
{
    if(p_bullet_list_.size() > 0)
    {
        for(int i = 0; i < p_bullet_list_.size(); i++)
        {
            EnemyBullet* p_bullet = p_bullet_list_.at(i);
            if(p_bullet != NULL)
            {
                delete p_bullet;
                p_bullet = NULL;
            }
        }
        p_bullet_list_.clear();
    }
}

void ThreatsObject::GenerateBullet(SDL_Renderer* screen, Mix_Chunk* bullet_sound)
{
    Mix_PlayChannel(-1, bullet_sound, 0);

    EnemyBullet* p_enemy_bullet = new EnemyBullet();

    p_enemy_bullet->LoadImg("Image/Player/Meteors/meteorGrey_tiny2.png", screen);

    p_enemy_bullet->SetRect(this->rect_.x + 32, this->rect_.y + 80);

    p_enemy_bullet->set_bullet_type(rand()%3);

   // p_enemy_bullet->set_is_move(true);

    p_bullet_list_.push_back(p_enemy_bullet);

}

void ThreatsObject::MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit)
{
    for(int i = 0; i < p_bullet_list_.size(); i++)
    {
        EnemyBullet* p_bullet = p_bullet_list_.at(i);
        if(p_bullet)
        {
            if(p_bullet->get_is_move())
            {
                p_bullet->Render(des);
                p_bullet->HandleBullet(SCREEN_WIDTH, SCREEN_HEIGHT);
            }
            else
            {
                p_bullet->set_is_move(true);
                p_bullet->SetRect(this->rect_.x + 32, this->rect_.y + 80);
            }
        }
    }
}

void ThreatsObject::HandleMove(const int& x_border, const int& y_border)
{
    rect_.y += y_val_;
    if(rect_.y > 720)
    {
        rect_.y = -HEIGHT_BLACKK4;
        int rand_x = rand() % 1000;
        if(rand_x > SCREEN_WIDTH)
        {
            rand_x = SCREEN_WIDTH * 0.5;
        }
        rect_.x = rand_x;
    }
}

void ThreatsObject::ResetThreats(const int& yborder)
{
    rect_.y = yborder;
    rect_.y = -HEIGHT_BLACKK4;
    int rand_x = rand() % 1000;
    if(rand_x > SCREEN_WIDTH)
    {
        rand_x = SCREEN_WIDTH * 0.5;
    }
    rect_.x = rand_x;

    for(int i = 0; i < p_bullet_list_.size(); i++)
    {
        EnemyBullet* p_bullet = p_bullet_list_.at(i);
        if(p_bullet)
        {
            ResetBullet(p_bullet);
        }
    }
}

void ThreatsObject::ResetBullet(EnemyBullet* p_bullet)
{
    p_bullet->SetRect(this->rect_.x + 32, this->rect_.y + 80);
}

void ThreatsObject::RemoveBullet(const int& idx)//khởi tạo lại đạn khi va chạm ở viên đạn thứ bao nhiêu idx
{
    for(int i = 0; i < p_bullet_list_.size(); i++)
    {
        EnemyBullet* p_bullet = p_bullet_list_.at(i);
        if(p_bullet)
        {
            ResetBullet(p_bullet);
        }
    }
}

