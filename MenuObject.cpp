#include "MenuObject.h"

int MenuObject::ShowMenu(SDL_Renderer* screen,TTF_Font* font,BaseObject gBackground)
{
    bool x = gBackground.LoadImg("Image/Background/background1.png", screen);
    gBackground.Render(screen, NULL);

    std::string s1 = "Enter To Play";
    std::string s2 = "E To Exit";

    const int menuItems = 2;
    SDL_Rect pos_arr[menuItems];

    pos_arr[0].x=200;
    pos_arr[0].y=200;

    pos_arr[1].x=200;
    pos_arr[1].y=260;

    TextObject text_menu[menuItems];

    text_menu[0].SetColor(TextObject::WHITE_TEXT);
    text_menu[0].SetText(s1);
    text_menu[0].LoadFromRenderText(font, screen);


    text_menu[1].SetColor(TextObject::WHITE_TEXT);
    text_menu[1].SetText(s2);
    text_menu[1].LoadFromRenderText(font, screen);

    bool selected[menuItems] = {0,0};
    SDL_Event menu_e;

    int xm = 0;
    int ym = 0;

    while(true)
    {
        for(int i = 0; i < menuItems; i++)
        {
            text_menu[i].RenderText(screen, pos_arr[i].x, pos_arr[i].y);
        }
        while(SDL_PollEvent(&menu_e))
        {
            switch(menu_e.type)
            {
            case SDL_QUIT:
                return 1;
            break;
            case SDL_KEYDOWN:
            {
                if(menu_e.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 1;
                }
                if(menu_e.key.keysym.sym == SDLK_RETURN)
                {
                    return 0;
                }
            }
            default:
                break;
            }
        }
    SDL_RenderPresent(screen);
    }
    return 1;
}
