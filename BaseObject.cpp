#include "BaseObject.h"

BaseObject::BaseObject()
{
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

//hàm hủy
BaseObject::~BaseObject()
{
    Free();
}

void BaseObject::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
    SDL_SetTextureAlphaMod(p_object_, alpha);
}

void BaseObject::flicking(Uint8& alpha)
{
    if( alpha <= 255 && alpha > 0 )
    {
        alpha -= 15;

    }
    else if (alpha ==0)
    {
        alpha = 255;
    }
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    SDL_Texture* new_texture = NULL;//biến kết quả
    SDL_Surface* load_surface = IMG_Load(path.c_str());//đọc ảnh
    if(load_surface != NULL)
    {
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if(new_texture != NULL)
        {
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;
        }

        //xóa load_surface vì tt đã chuyển qua new_texture
        SDL_FreeSurface(load_surface);
    }

    width_frame=rect_.w;
    height_frame=rect_.h;
    p_object_ = new_texture;

    return p_object_ != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)//thong so anh
{
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};

    SDL_RenderCopy(des, p_object_, clip, &renderquad);//đẩy toàn bộ thông số p_object_ lên trên des
}

//giải phóng các đối tượng
void BaseObject::Free()
{
    if(p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_);// hủy p_object_
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}

void BaseObject::MoveBackGround(SDL_Renderer* screen, const SDL_Rect* clip /*- NULL*/)
{
    SDL_Rect renderquad1={rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopy(screen,p_object_, clip, &renderquad1);
    SDL_Rect renderquad2={rect_.x, rect_.y - SCREEN_HEIGHT, rect_.w, rect_.h};
    SDL_RenderCopy(screen,p_object_, clip, &renderquad2);
    rect_.y += 1;
    if(rect_.y >= SCREEN_HEIGHT)
    {
        rect_.y = 0;
    }
}




