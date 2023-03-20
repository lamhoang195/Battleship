#include "PlayerObject.h"


PlayerObject::PlayerObject()
{
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = WIDTH_PLAYER_OBJECT;
    rect_.h = HEIGHT_PLAYER_OBJECT;

    x_val_ = 552.5;
    y_val_ = 620;


}

PlayerObject::~PlayerObject()
{
    ;
}

void PlayerObject::HanderInputAction(SDL_Event events, SDL_Renderer *screen)
{
    switch (events.type)
	{
	case SDL_KEYDOWN:
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
			if (x_val_ + WIDTH_PLAYER_OBJECT/4 >= 50)
				x_val_ -= WIDTH_PLAYER_OBJECT/4;
				break;

        case SDLK_SPACE:
            {
            LaserObject* p_laserBlue01= new LaserObject();

            p_laserBlue01->LoadImg("Image/Player/Lasers/laserRed16.png", screen);

            p_laserBlue01->SetRect(this->rect_.x + 45.5, this->rect_.y - 15 );

            p_laserBlue01->set_is_move(true);

            p_laser_list_.push_back(p_laserBlue01);

            }
            break;
            }
    }
}

void PlayerObject::HandleLaser(SDL_Renderer *des)
{
    for (unsigned int i=0; i< p_laser_list_.size(); i++ )
    {
        if( p_laser_list_[i] ->get_is_move())
        {
            p_laser_list_[i]->Render(des);
            p_laser_list_[i]->HandleMove(0,0);
        }
        else
        {
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





