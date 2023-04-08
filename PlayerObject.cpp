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
}

PlayerObject::~PlayerObject()
{
    ;
}

void PlayerObject::HanderInputAction(SDL_Event events, SDL_Renderer *screen)
{
    if(events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
			if (y_val_ - HEIGHT_PLAYER_OBJECT/4 >= 10)
				y_val_ = y_val_ - HEIGHT_PLAYER_OBJECT/4;
			break;

		case SDLK_DOWN:
			if ( y_val_ + HEIGHT_PLAYER_OBJECT/4 <= SCREEN_HEIGHT - HEIGHT_PLAYER_OBJECT)
				y_val_ += HEIGHT_PLAYER_OBJECT/4;
				break;

		case SDLK_RIGHT:
			if (x_val_ + WIDTH_PLAYER_OBJECT/3 <= SCREEN_WIDTH - WIDTH_PLAYER_OBJECT)
                x_val_ += WIDTH_PLAYER_OBJECT/3;
				break;

		case SDLK_LEFT:
			if (x_val_ + WIDTH_PLAYER_OBJECT/3 >= 50)
				x_val_ -= WIDTH_PLAYER_OBJECT/3;
				break;
		}
	}
    else if(events.type == SDL_MOUSEBUTTONDOWN)
    {
        switch (events.button.button)
        {
        case SDL_BUTTON_LEFT:
            {
            LaserObject* p_laserRed14= new LaserObject();

            p_laserRed14->LoadImg("Image/Player/Lasers/laserBlue14.png", screen);

            p_laserRed14->SetRect(this->rect_.x + 53.5, this->rect_.y - 20);//vi tri cap nhat theo may bay

            p_laserRed14->set_is_move(true);

            p_laser_list_.push_back(p_laserRed14);

            }
            break;

        case SDL_BUTTON_RIGHT:
            {
            LaserObject* p_laserRed12= new LaserObject();

            p_laserRed12->LoadImg("Image/Player/Lasers/laserBlue12.png", screen);

            p_laserRed12->SetRect(this->rect_.x + 53.5, this->rect_.y - 20);//vi tri cap nhat theo may bay

            p_laserRed12->set_is_move(true);//cho phép bắn

            p_laser_list_.push_back(p_laserRed12);
            }
            break;
        }
    }
}

void PlayerObject::HandleLaser(SDL_Renderer* des)
{
    for (int i=0; i < p_laser_list_.size(); i++ )
    {
        if( p_laser_list_[i] -> get_is_move())
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

void PlayerObject::RemoveLaser(const int& idx)
{
    if(p_laser_list_.size() > 0 && idx < p_laser_list_.size())
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
