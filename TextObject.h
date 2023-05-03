#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H

#include "CommonFunction.h"
#include "BaseObject.h"

class TextObject : public BaseObject
{
public:
    TextObject();
    ~TextObject();

    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
    };

    bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);//in ra font chu
    void Free();//giai phong

    void SetColor(Uint8 red, Uint8 green, Uint8 blue);//truyen truc tiep ma mau
    void SetColor(int type_);//mau co ban

    void RenderText(SDL_Renderer* screen,
                    int xp, int yp,
                    SDL_Rect* clip = NULL,
                    double angle = 0.0,
                    SDL_Point* center = NULL,
                    SDL_RendererFlip flip = SDL_FLIP_NONE);

    int GetWidth() const {return width_;}
    int GetHeight() const {return height_;}

    void SetText(const std::string& text) {str_val_ = text;}
    std::string GetText() const {return str_val_;}

private:
    std::string str_val_;
    SDL_Color text_color_;
    SDL_Texture* texture_;
    int width_;
    int height_;
};

#endif // TEXT_OBJECT_H
