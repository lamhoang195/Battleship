#include "PlayerObject.h"
#include "ImpTimer.h"


PlayerObject::PlayerObject()
{
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = WIDTH_PLAYER_OBJECT;
    rect_.h = HEIGHT_PLAYER_OBJECT;

    x_val_ = 440;
    y_val_ = 600;
    canspawnbullet = 0;
    life = 3;
}

PlayerObject::~PlayerObject()
{
    ;
}

void PlayerObject::HanderInputAction(SDL_Event events, SDL_Renderer *screen, Mix_Chunk* laser_sound)
{
    if( events.type==SDL_MOUSEBUTTONUP || events.type==SDL_MOUSEMOTION)
    {
        input_mouse=1;
        int x,y;
        SDL_GetMouseState(&x,&y);
        x_val_=x-WIDTH_PLAYER_OBJECT/2;
        y_val_=y-HEIGHT_PLAYER_OBJECT/2;
    }
    else if(events.type == SDL_MOUSEBUTTONDOWN)
    {
        switch (events.button.button)
        {
        case SDL_BUTTON_LEFT:
            {
            Mix_PlayChannel(-1, laser_sound, 0);

            LaserObject* p_laserRed14 = new LaserObject();

            p_laserRed14->LoadImg("Image/Player/Lasers/bullet2.png", screen);

            p_laserRed14->SetRect(this->rect_.x + 20, this->rect_.y + 5);//vi tri cap nhat theo may bay

            p_laserRed14->set_is_move(true);

            p_laser_list_.push_back(p_laserRed14);
            }
            break;

        case SDL_BUTTON_RIGHT:
            {
            Mix_PlayChannel(-1, laser_sound, 0);

            LaserObject* p_laserRed12 = new LaserObject();

            p_laserRed12->LoadImg("Image/Player/Lasers/bullet2.png", screen);

            p_laserRed12->SetRect(this->rect_.x + 26.7, this->rect_.y + 5);//vi tri cap nhat theo may bay

            p_laserRed12->set_is_move(true);//cho phép bắn

            p_laser_list_.push_back(p_laserRed12);
            }
            break;
        }
    }
}

void PlayerObject::HandleLaser(SDL_Renderer* des)//bắn đạn
{
    for (int i=0; i < p_laser_list_.size(); i++ )
    {
        if( p_laser_list_[i] -> get_is_move())//nếu di chuyển
        {
            p_laser_list_[i]->Render(des);
            p_laser_list_[i]->HandleMove(0,0);
        }
        else
        {
            //bắn ra ngoài hủy
            delete p_laser_list_[i];
            p_laser_list_.erase(p_laser_list_.begin()+i);
        }
    }
}

void PlayerObject::HandleMove()
{
    rect_.x = x_val_;
	rect_.y = y_val_;
}

void PlayerObject::RemoveLaser(const int& idx)//khởi tạo lại đạn khi va chạm ở viên đạn thứ bao nhiêu idx
{
    int n = p_laser_list_.size();
    if(n > 0 && idx < n)
    {
        for(int i = 0 ; i < p_laser_list_.size(); i++)
        {
            LaserObject* p_laser = p_laser_list_.at(idx);
            p_laser_list_.erase(p_laser_list_.begin() + idx);
            if(p_laser != NULL)
            {
                delete p_laser;
                p_laser = NULL;
            }
        }
    }
}

void PlayerObject::Reset()
{
    x_val_ = 440;
    y_val_ = 600;
    life = 3;
    p_laser_list_.erase(p_laser_list_.begin(), p_laser_list_.begin() + p_laser_list_.size());
}
