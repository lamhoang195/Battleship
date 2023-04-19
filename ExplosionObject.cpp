#include "ExplosionObject.h"
#include <bits/stdc++.h>

ExplosionObject::ExplosionObject()
{
    frame_width_ = 0;
    frame_height_ = 0;
    frame_ = 0;
}

ExplosionObject::~ExplosionObject()
{

}

bool ExplosionObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);
    if(ret)
    {
        frame_width_ = rect_.x/NUM_FRAME_EXP;
        frame_height_ = rect_.h;
    }
    return ret;
}


void ExplosionObject::set_clip()
{
    clip_[0].x = 0;
    clip_[0].y = 0;
    clip_[0].w = frame_width_;
    clip_[0].h = frame_height_;

    clip_[1].x = frame_width_;
    clip_[1].y = 0;
    clip_[1].w = frame_width_;
    clip_[1].h = frame_height_;

    clip_[2].x = frame_width_*2;
    clip_[2].y = 0;
    clip_[2].w = frame_width_;
    clip_[2].h = frame_height_;

    clip_[3].x = frame_width_*3;
    clip_[3].y = 0;
    clip_[3].w = frame_width_;
    clip_[3].h = frame_height_;

    clip_[4].x = frame_width_*4;
    clip_[4].y = 0;
    clip_[4].w = frame_width_;
    clip_[4].h = frame_height_;
}

void ExplosionObject::Show(SDL_Renderer* screen)
{
    if(frame_ >= 5)
    {
        frame_ = 0;
    }
    SDL_RenderCopy(screen, p_object_, &clip_[frame_], &rect_);
}

