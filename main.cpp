#include "CommonFunction.h"
#include "BaseObject.h"
#include "PlayerObject.h"

BaseObject g_background;
PlayerObject g_playerobject;

//khởi động thông số cho SDL
bool initData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0)
        return false;

    //thiết lập tỉ lệ chất lượng
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    //Tao cua so
    g_window = SDL_CreateWindow("Game Lam_Hoang",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN
                                );
    if(g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL)
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);//màu sắc render ra màn hinh

            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }
    }
    return success;
}

bool LoadBackground()
{

    bool ret = g_background.LoadImg("Image/Background/background.png", g_screen);
    if(ret == false)
        return false;
    return true;
}

bool LoadPlayer()
{
    bool ret = g_playerobject.LoadImg("Image/Player/playerShip1_blue.png", g_screen);
    g_playerobject.SetRect(552.5,620);
    if(ret == false)
        return false;
    return true;
}

void Clean()
{
    g_background.Free();
    g_playerobject.Free();

    SDL_DestroyRenderer(g_screen);//giải phóng g_screen
    g_screen = NULL;

    SDL_DestroyWindow(g_window);//giải phóng cửa sổ g_window
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if(initData() == false)
        return -1;

    if(LoadBackground() == false)
        return -1;

    if(LoadPlayer() == false)
        return -1;


    bool ret = g_playerobject.LoadImg("Image/Player/playerShip1_red.png", g_screen);

    if(!ret)
    {
        return 0;
    }

    //chạy ảnh vô tận
    bool is_quit = false;
    while(!is_quit)
    {
        while(SDL_PollEvent(&g_event) !=0)
        {
            if(g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            g_playerobject.HanderInputAction(g_event, g_screen);
        }
        //trước load ảnh sét lại màu cho màn hình
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);

        SDL_RenderClear(g_screen);//xóa màn hình đi

        g_background.Render(g_screen, NULL);

        g_playerobject.HandleMove();

        g_playerobject.HandleLaser(g_screen);

        g_playerobject.Render(g_screen, NULL);

        //đưa ảnh vào màn hình
        SDL_RenderPresent(g_screen);
    }

    Clean();
    return 0;
}
