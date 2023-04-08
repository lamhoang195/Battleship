#pragma once

#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "commonFunction.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();

    //cai dat kich thuoc cho rect
    void SetRect(const int& x, const int& y)
    {
        rect_.x = x, rect_.y = y;
    }

    //lấy ra kích thước rect
    SDL_Rect GetRect() const{return rect_;}

    //lấy ra p_object_
    SDL_Texture* GetObject() const {return p_object_;}//lấy ra k làm gì cả

    //load ảnh lên p_object sau đó sử dụng vào màn hình
    virtual bool LoadImg(std::string path, SDL_Renderer* screen);

    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);//load ảnh lên nền

    void Free();

protected:
    //biến chuyên sd lưu trữ các ảnh
    SDL_Texture* p_object_;

    //biến chuyên lưu kích thước tấm ảnh đó
    SDL_Rect rect_;
};

#endif // BASE_OBJECT_H
