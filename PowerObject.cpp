#include "PowerObject.h"

PowerObject::PowerObject()
{
    number_health_ = 0;
}

PowerObject::~PowerObject()
{

}

void PowerObject::add_pos(const int& xpos)
{
    pos_list_.push_back(xpos);
}

void PowerObject::ShowP(SDL_Renderer* res)
{
    for(int i =0; i < pos_list_.size(); i++)
    {
        rect_.x = pos_list_.at(i);
        rect_.y = 0;
        Render(res);
    }
}

void PowerObject::InitP(SDL_Renderer* screen)
{
    LoadImg("Image/Player/health.png", screen);
    number_health_ = 3;
    if(pos_list_.size() > 0)
    {
        pos_list_.clear();
    }
    add_pos(20);
    add_pos(50);
    add_pos(80);
}

void PowerObject::Decrease()
{
    number_health_--;
    pos_list_.pop_back();
}
