#include "CommonFunction.h"
#include "BaseObject.h"
#include "PlayerObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include <vector>


//khởi động thông số cửa sổ
bool initData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0)
        return false;

    //thiết lập tỉ lệ chất lượng
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    //tạo cửa sổ window
    g_window = SDL_CreateWindow("Game Battleship",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
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
            SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);//màu sắc render ra màn hinh

            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }
    }
    return success;
}

BaseObject g_background;
bool LoadBackground()
{
    bool ret = g_background.LoadImg("Image/Background/background1.png", g_screen);
    if(ret == false)
        return false;
    return true;
}

PlayerObject g_playerobject;
bool LoadPlayer()
{
    bool ret = g_playerobject.LoadImg("Image/Player/playerShip1_blue.png", g_screen);
    g_playerobject.SetRect(552.5,620);
    if(ret == false)
        return false;
    return true;
}

ThreatsObject g_threats;
bool LoadThreats()
{
    for(int i = 0; i < NUM_MAX_THREATS; i++)
    {
        g_threats.value = i;
        bool ret = g_threats.LoadImg("Image/Player/Enemies/enemyBlack4.png", g_screen);
        if(ret == false)
            return false;
        return true;
        int rand_x = rand()%400;
        if(rand_x > SCREEN_WIDTH)
        {
            rand_x = SCREEN_WIDTH*0.5;
        }
        g_threats.SetRect(rand_x, SCREEN_HEIGHT + i*400);
    }
}

void Clean()
{
    g_background.Free();
    g_playerobject.Free();
    g_threats.Free();

    SDL_DestroyRenderer(g_screen);//giải phóng g_screen
    g_screen = NULL;

    SDL_DestroyWindow(g_window);//giải phóng cửa sổ g_window
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}



int main(int argc, char* argv[])
{
    ImpTimer fps_timer;
    int bg_y = 0;
    if(initData() == false)
        return -1;

    if(LoadBackground() == false)
        return -1;

    if(LoadPlayer() == false)
        return -1;

    if(LoadThreats() == false)
        return -1;

    bool ret = g_playerobject.LoadImg("Image/Player/shipLoser1.png", g_screen);

    if(!ret)
    {
        return 0;
    }

    //chạy ảnh vô tận
    bool is_quit = false;

    g_threats.set_y_val(1);

    g_threats.GenerateBullet(g_screen);

    while(!is_quit)
    {
        fps_timer.start();
        while(SDL_PollEvent(&g_event) !=0)
        {
            if(g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            g_playerobject.HanderInputAction(g_event, g_screen);
        }
        bg_y += 2;

        //trước load ảnh sét lại màu cho màn hình
        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);

        SDL_RenderClear(g_screen);//xóa màn hình đi

        g_background.Render(g_screen, NULL);

        g_background.Render(g_screen, NULL);

        g_playerobject.HandleMove();

        g_playerobject.Render(g_screen, NULL);

        g_playerobject.HandleLaser(g_screen);

        //for(int j = 0; j < NUM_MAX_THREATS; j++)
        //{
        //    g_threats.value = j;
        g_threats.HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);

        g_threats.Render(g_screen, NULL);

        g_threats.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
        //}

        //threat va chạm player
        bool is_col = SDL_Common::check_overlap(g_playerobject.GetRect(), g_threats.GetRect());
        if(is_col)
        {
            if(MessageBox(NULL, "Game Over!", "Box", MB_OK) == IDOK)
            {
                Clean();
                SDL_Quit();
                return 1;
            }
        }

        //enemybullet va chạm với player
        std::vector <EnemyBullet*> enemybullet_list = g_threats.get_bullet_list();
        for(int i = 0; i < enemybullet_list.size(); i++)
        {
            EnemyBullet* p_enemybullet = enemybullet_list.at(i);
            if(p_enemybullet != NULL)
            {
                bool ret_col = SDL_Common::check_overlap(p_enemybullet->GetRect(), g_playerobject.GetRect());
                if(ret_col)
                {
                    if(MessageBox(NULL, "Game Over!", "Box", MB_OK) == IDOK)
                    {
                        Clean();
                        SDL_Quit();
                        return 1;
                    }
                }
            }
        }

        //player laser va chạm threats
        std::vector <LaserObject*> laser_list = g_playerobject.get_laser_list();
        for(int i = 0; i < laser_list.size(); i++)
        {
            LaserObject* p_laser = laser_list.at(i);
            if(p_laser != NULL)
            {
                bool ret_col = SDL_Common::check_overlap(p_laser->GetRect(), g_threats.GetRect());
                if(ret_col)
                {
                    g_playerobject.RemoveLaser(i);
                    g_threats.ResetThreats(SCREEN_WIDTH);
                }
            }
        }

        SDL_RenderPresent(g_screen);//đưa ảnh vào màn hình

        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND;

        if(real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            if(delay_time >= 0)
            {
                SDL_Delay(delay_time);
            }
        }
    }
    Clean();
    return 0;
}
