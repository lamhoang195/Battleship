#pragma once

#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include "CommonFunction.h"
#include "BaseObject.h"
#include "LaserObject.h"
#include <vector>

#define WIDTH_PLAYER_OBJECT 99
#define HEIGHT_PLAYER_OBJECT 75

class PlayerObject : public BaseObject
{
public:
    PlayerObject();
    ~PlayerObject();

    void HanderInputAction(SDL_Event events, SDL_Renderer* screen);//sự kiện
    void HandleMove();

    void set_laser_list(std::vector<LaserObject*> laser_list)
    {
        p_laser_list_ = laser_list;
    }
    std::vector<LaserObject*> get_laser_list() const {return p_laser_list_;}

    void HandleLaser(SDL_Renderer *des);

private:
    std::vector<LaserObject*> p_laser_list_;
    float x_val_;
    float y_val_;

    Input input_type_;//biến lưu trạng thái

};

#endif // PLAYER_OBJECT_H
