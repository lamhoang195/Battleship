#ifndef EXPLOSION_OBJECT_H
#define EXPLOSION_OBJECT_H

#include "BaseObject.h"
#include "CommonFunction.h"

#define NUM_FRAME_EXP 5

//const int EXP_WIDTH = 118;
//const int EXP_HEIGHT = 118;

class ExplosionObject : public BaseObject
{
public:
    ExplosionObject();
    ~ExplosionObject();

    void set_clip();
    void set_frame(const int& frame) {frame_ = frame;}
    int get_frame_width() const {return frame_width_;}
    int get_frame_height() const {return frame_height_;}
    void Show(SDL_Renderer* screen);
    virtual bool LoadImg(std::string path, SDL_Renderer* screen);

private:
    int frame_width_;//kich thuoc 1 frame
    int frame_height_;
    int frame_;
    SDL_Rect clip_[5];
};

#endif // EXPLOSION_OBJECT_H
