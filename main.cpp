#include <bits/stdc++.h>
#include "CommonFunction.h"
#include "BaseObject.h"
#include "PlayerObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "PowerObject.h"
#include "TextObject.h"
#include "BossObject.h"
#include "MenuObject.h"
#include <vector>
#include <ctime>

TTF_Font* font_time;
TTF_Font* font_menu;
Uint8 a = 255;
long long CurrentTime;
long long LastTime;

//khởi động thông số cửa sổ
bool init()
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
        if ( Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096) == -1 )
        {
            success = true;
        }
        //Doc file wav audio
        g_sound_bullet = Mix_LoadWAV("Mixer/sfx_shieldDown.wav");
        g_sound_laser_l = Mix_LoadWAV("Mixer/sfx_laser1.wav");
        g_sound_exp_player = Mix_LoadWAV("Mixer/shipExplosion.wav");
        g_sound_exp_threats = Mix_LoadWAV("Mixer/shipExplosion.wav");
        g_sound_menu = Mix_LoadWAV("Mixer/Menu.mp3");
        g_sound_menu1 = Mix_LoadWAV("Mixer/PlayForReal.mp3");

        if(g_sound_bullet == NULL || g_sound_exp_player == NULL || g_sound_exp_threats == NULL || g_sound_laser_l == NULL || g_sound_laser_r == NULL)
        {
            success = true;
        }

        if(TTF_Init() == -1)
        {
            success = false;
        }

        font_time = TTF_OpenFont("Font/kenvector_future.ttf", 20);
        font_menu = TTF_OpenFont("Font/kenvector_future.ttf", 30);
        if(font_time == NULL)
        {
            success = false;
        }
        if(font_menu == NULL)
        {
            success = false;
        }
    }
    return success;
}

BaseObject g_background;
BaseObject gameover;
PlayerObject g_playerobject;
BossObject g_boss;

ThreatsObject g_threats_1;
bool LoadThreats1()
{
    for(int i = 0; i < NUM_MAX_THREATS; i++)
    {
            bool ret = g_threats_1.LoadImg("Image/Player/Enemies/enemyBlack4.png", g_screen);
            if(ret == false)
                return false;
            return true;
            int rand_x = rand()%600;
            if(rand_x > SCREEN_WIDTH)
            {
                rand_x = SCREEN_WIDTH*0.5;
            }
            g_threats_1.SetRect(rand_x, SCREEN_HEIGHT);
    }
}

ThreatsObject g_threats_2;
bool LoadThreats2()
{
    for(int i = 0; i < NUM_MAX_THREATS; i++)
    {
            bool ret = g_threats_2.LoadImg("Image/Player/Enemies/enemyBlue4.png", g_screen);
            if(ret == false)
                return false;
            return true;
            int rand_x = rand()%800;
            if(rand_x > SCREEN_WIDTH)
            {
                rand_x = SCREEN_WIDTH*0.5;
            }
            g_threats_2.SetRect(rand_x, SCREEN_HEIGHT);
    }
}

ThreatsObject g_threats_3;
bool LoadThreats3()
{
    for(int i = 0; i < NUM_MAX_THREATS; i++)
    {
            bool ret = g_threats_3.LoadImg("Image/Player/Enemies/enemyRed4.png", g_screen);
            if(ret == false)
                return false;
            return true;
            int rand_x = rand()%1000;
            if(rand_x > SCREEN_WIDTH)
            {
                rand_x = SCREEN_WIDTH*0.5;
            }
            g_threats_3.SetRect(rand_x, SCREEN_HEIGHT);
    }
}



void Clean()
{
    g_background.Free();
    g_playerobject.Free();
    g_threats_1.Free();
    g_threats_2.Free();
    g_threats_3.Free();
    gameover.Free();

    SDL_DestroyRenderer(g_screen);//giải phóng g_screen
    g_screen = NULL;

    SDL_DestroyWindow(g_window);//giải phóng cửa sổ g_window
    g_window = NULL;

    Mix_FreeChunk(g_sound_bullet);
    g_sound_bullet = NULL;
    Mix_FreeChunk(g_sound_laser_l);
    g_sound_laser_l = NULL;
    Mix_FreeChunk(g_sound_laser_r);
    g_sound_laser_r = NULL;
    Mix_FreeChunk(g_sound_exp_player);
    g_sound_exp_player = NULL;
    Mix_FreeChunk(g_sound_menu);
    g_sound_menu = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{

    srand(time(nullptr));
    ImpTimer fps_timer;
    int bg_y = 0;
    if(init() == false)
        return -1;

    g_background.LoadImg("Image/Background/background5.jpg", g_screen);
    gameover.LoadImg("Image/Background/background1.png", g_screen);
    g_playerobject.LoadImg("Image/Player/shipLoser2.png", g_screen);
    g_boss.LoadImg("Image/Player/boss2.png", g_screen);
    g_boss.set_stats(g_screen);
    g_boss.set_x_pos(SCREEN_WIDTH/2 - (g_boss.get_width_frame())/2);
    g_boss.set_y_limit(25);
    g_boss.set_y_pos(-200);
    g_boss.set_health(500);


    if(LoadThreats1() == false)
        return -1;

    if(LoadThreats2() == false)
        return -1;

    if(LoadThreats3() == false)
        return -1;

    ExplosionObject exp_player;
    bool tRet = exp_player.LoadImg("Image/Player/explosion1.png", g_screen);
    if(!tRet) return -1;
    exp_player.set_clip();

    //Power
    PowerObject power_player;
    power_player.InitP(g_screen);

    int number_die = 0;
    int threats_2_die = 1;
    int threats_3_die = 2;

    g_threats_1.set_y_val(2);
    g_threats_1.GenerateBullet(g_screen, g_sound_bullet);
    Mix_PlayChannel(-1, g_sound_bullet, 0);

    g_threats_2.set_y_val(2);
    g_threats_2.GenerateBullet(g_screen, g_sound_bullet);

    g_threats_3.set_y_val(2);
    g_threats_3.GenerateBullet(g_screen, g_sound_bullet);

    //Time text
    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_TEXT);

    TextObject score_game;
    score_game.SetColor(TextObject::WHITE_TEXT);
    UINT score_value = 0;

    Mix_VolumeChunk(g_sound_menu, MIX_MAX_VOLUME/5);
    Mix_VolumeChunk(g_sound_exp_player, MIX_MAX_VOLUME/4);

    //bool imenu = true;
    bool is_quit = false;

    Mix_PlayChannel(-1, g_sound_menu, 0);

    int ret_menu = MenuObject::ShowMenu(g_screen, font_menu, g_background);
    if(ret_menu == 1)
    {
        is_quit = true;
    }

    bool GameOver = false;

    //chạy ảnh vô tận
    while(!is_quit)
    {
        fps_timer.start();
        if (!GameOver)
        {
            while(SDL_PollEvent(&g_event) != 0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    is_quit = true;
                }
                g_playerobject.HanderInputAction(g_event, g_screen, g_sound_laser_l);
            }
            //trước load ảnh sét lại màu cho màn hình
            SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);

            SDL_RenderClear(g_screen);//xóa màn hình đi

            SDL_ShowCursor(SDL_DISABLE);

            g_background.MoveBackGround(g_screen, NULL);

            power_player.ShowP(g_screen);

            g_playerobject.HandleMove();

            g_playerobject.Render(g_screen, NULL);

            g_playerobject.HandleLaser(g_screen);

            g_threats_1.HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);

            g_threats_1.Render(g_screen, NULL);

            g_threats_1.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT/2);

            int frame_exp_width = exp_player.get_frame_width();
            int frame_exp_height = exp_player.get_frame_height();

            //va cham voi may bay dich 1
            bool is_col_1 = SDL_Common::check_overlap(g_playerobject.GetRect(), g_threats_1.GetRect());
            if(is_col_1)
            {
                score_value++;
                for(int ex = 0; ex < 5; ex++)
                {
                    int x_pos = g_playerobject.GetRect().x + g_playerobject.GetRect().w*0.5 - 118*0.5;
                    int y_pos = g_playerobject.GetRect().y + g_playerobject.GetRect().h*0.5 - 118*0.5;
                    exp_player.set_frame(ex);
                    exp_player.SetRect(x_pos, y_pos);
                    exp_player.Show(g_screen);
                    SDL_RenderPresent(g_screen);
                }
                for(int ex = 0; ex < 5; ex++)
                {
                    int x_pos = g_threats_1.GetRect().x + g_threats_1.GetRect().w*0.5 - 118*0.5;
                    int y_pos = g_threats_1.GetRect().y + g_threats_1.GetRect().h*0.5 - 118*0.5;
                    exp_player.set_frame(ex);
                    exp_player.SetRect(x_pos, y_pos);
                    exp_player.Show(g_screen);
                    SDL_RenderPresent(g_screen);
                }
                Mix_PlayChannel(-1, g_sound_exp_player, 0);
                g_playerobject.got_hit();
                SDL_Delay(100);
                g_threats_1.ResetThreats(SCREEN_WIDTH);
                power_player.Decrease();
                SDL_RenderPresent(g_screen);
                if(g_playerobject.get_life() == 0)
                {
                    GameOver = true;
                }
            }

            //va cham voi dan cua may bay 1
            std::vector <EnemyBullet*> enemybullet_list_1 = g_threats_1.get_bullet_list();
            for(int i = 0; i < enemybullet_list_1.size(); i++)
            {
                EnemyBullet* p_enemybullet_1 = enemybullet_list_1.at(i);
                if(p_enemybullet_1 != NULL)
                {
                    bool ret_col= SDL_Common::check_overlap(p_enemybullet_1->GetRect(), g_playerobject.GetRect());
                    if(ret_col)
                    {
                        for(int ex = 0; ex < 5; ex++)
                        {
                            int x_pos = g_playerobject.GetRect().x + g_playerobject.GetRect().w*0.5 - 118*0.5;
                            int y_pos = g_playerobject.GetRect().y + g_playerobject.GetRect().h*0.5 - 118*0.5;
                            exp_player.set_frame(ex);
                            exp_player.SetRect(x_pos, y_pos);
                            exp_player.Show(g_screen);
                            SDL_Delay(50);
                            //SDL_RenderPresent(g_screen);
                        }
                        Mix_PlayChannel(-1, g_sound_exp_player, 0);
                        power_player.Decrease();
                        g_playerobject.got_hit();
                        g_threats_1.RemoveBullet(i);
                        SDL_RenderPresent(g_screen);
                        if(g_playerobject.get_life() == 0)
                        {
                            GameOver = true;
                        }
                    }
                }
                else{}
            }

            //may bay dich 1 va cham voi laser
            std::vector <LaserObject*> laser_list_1 = g_playerobject.get_laser_list();
            for(int i = 0; i < laser_list_1.size(); i++)
            {
                LaserObject* p_laser_1 = laser_list_1.at(i);
                if(p_laser_1 != NULL)
                {
                    bool ret_col = SDL_Common::check_overlap(p_laser_1->GetRect(), g_threats_1.GetRect());
                    if(ret_col)
                    {
                        score_value++;
                        for(int ex = 0; ex < 5; ex++)
                        {
                            int x_pos = p_laser_1->GetRect().x + p_laser_1->GetRect().w*0.5 - 118*0.5;
                            int y_pos = p_laser_1->GetRect().y + p_laser_1->GetRect().h*0.5 - 118*0.5;
                            exp_player.set_frame(ex);
                            exp_player.SetRect(x_pos, y_pos);
                            exp_player.Show(g_screen);
                            //SDL_RenderPresent(g_screen);
                        }
                        g_threats_1.ResetThreats(SCREEN_WIDTH);
                        g_playerobject.RemoveLaser(i);
                        Mix_PlayChannel(-1, g_sound_exp_player, 0);
                    }
                }
            }

            //va cham voi may bay 2
            bool is_col_2 = SDL_Common::check_overlap(g_playerobject.GetRect(), g_threats_2.GetRect());
            if(is_col_2)
            {
                for(int ex = 0; ex < 5; ex++)
                {
                    int x_pos = g_playerobject.GetRect().x + g_playerobject.GetRect().w*0.5 - 118*0.5;
                    int y_pos = g_playerobject.GetRect().y + g_playerobject.GetRect().h*0.5 - 118*0.5;
                    exp_player.set_frame(ex);
                    exp_player.SetRect(x_pos, y_pos);
                    exp_player.Show(g_screen);
                    SDL_RenderPresent(g_screen);
                }
                for(int ex = 0; ex < 5; ex++)
                {
                    int x_pos = g_threats_2.GetRect().x + g_threats_2.GetRect().w*0.5 - 118*0.5;
                    int y_pos = g_threats_2.GetRect().y + g_threats_2.GetRect().h*0.5 - 118*0.5;
                    exp_player.set_frame(ex);
                    exp_player.SetRect(x_pos, y_pos);
                    exp_player.Show(g_screen);
                    SDL_RenderPresent(g_screen);
                }
                //g_threats1.ResetThreats(SCREEN_WIDTH);
                Mix_PlayChannel(-1, g_sound_exp_player, 0);
                SDL_Delay(100);
                g_playerobject.got_hit();
                power_player.Decrease();
                g_threats_2.ResetThreats(SCREEN_WIDTH);
                SDL_RenderPresent(g_screen);
                if(g_playerobject.get_life() == 0)
                {
                    GameOver = true;
                }
            }

            //va cham voi dan cua may bay 2
            std::vector <EnemyBullet*> enemybullet_list_2 = g_threats_2.get_bullet_list();
            for(int i = 0; i < enemybullet_list_2.size(); i++)
            {
                EnemyBullet* p_enemybullet_2 = enemybullet_list_2.at(i);
                if(p_enemybullet_2 != NULL)
                {
                    bool ret_col = SDL_Common::check_overlap(p_enemybullet_2->GetRect(), g_playerobject.GetRect());
                    if(ret_col)
                    {
                        for(int ex = 0; ex < 5; ex++)
                        {
                            int x_pos = g_playerobject.GetRect().x + g_playerobject.GetRect().w*0.5 - 118*0.5;
                            int y_pos = g_playerobject.GetRect().y + g_playerobject.GetRect().h*0.5 - 118*0.5;
                            exp_player.set_frame(ex);
                            exp_player.SetRect(x_pos, y_pos);
                            exp_player.Show(g_screen);
                            SDL_Delay(50);
                            SDL_RenderPresent(g_screen);
                        }
                        Mix_PlayChannel(-1, g_sound_exp_player, 0);
                        power_player.Decrease();
                        g_playerobject.got_hit();
                        g_threats_2.RemoveBullet(i);
                        SDL_RenderPresent(g_screen);
                        if(g_playerobject.get_life() == 0)
                        {
                            GameOver = true;
                        }
                    }
                }
            }

            //may bay 2 va cham voi laser
            std::vector <LaserObject*> laser_list_2 = g_playerobject.get_laser_list();
            for(int i = 0; i < laser_list_2.size(); i++)
            {
                LaserObject* p_laser_2 = laser_list_2.at(i);
                if(p_laser_2 != NULL)
                {
                    bool ret_col = SDL_Common::check_overlap(p_laser_2->GetRect(), g_threats_2.GetRect());
                    if(ret_col)
                    {

                        for(int ex = 0; ex < 5; ex++)
                        {
                            int x_pos = p_laser_2->GetRect().x + p_laser_2->GetRect().w*0.5 - 118*0.5;
                            int y_pos = p_laser_2->GetRect().y + p_laser_2->GetRect().h*0.5 - 118*0.5;
                            exp_player.set_frame(ex);
                            exp_player.SetRect(x_pos, y_pos);
                            exp_player.Show(g_screen);
                            //SDL_RenderPresent(g_screen);
                        }
                        if(threats_2_die == 1)
                        {
                            threats_2_die--;
                            g_playerobject.RemoveLaser(i);
                        }
                        else if(threats_2_die == 0)
                        {
                            score_value++;
                            g_threats_2.ResetThreats(SCREEN_WIDTH);
                            threats_2_die = 1;
                            g_playerobject.RemoveLaser(i);
                        }
                        Mix_PlayChannel(-1, g_sound_exp_player, 0);
                    }
                }
            }

            //va cham voi may bay 3
            bool is_col_3 = SDL_Common::check_overlap(g_playerobject.GetRect(), g_threats_3.GetRect());
            if(is_col_3)
            {
                for(int ex = 0; ex < 5; ex++)
                {
                    int x_pos = g_playerobject.GetRect().x + g_playerobject.GetRect().w*0.5 - 118*0.5;
                    int y_pos = g_playerobject.GetRect().y + g_playerobject.GetRect().h*0.5 - 118*0.5;
                    exp_player.set_frame(ex);
                    exp_player.SetRect(x_pos, y_pos);
                    exp_player.Show(g_screen);
                    SDL_RenderPresent(g_screen);
                }
                for(int ex = 0; ex < 5; ex++)
                {
                    int x_pos = g_threats_3.GetRect().x + g_threats_3.GetRect().w*0.5 - 118*0.5;
                    int y_pos = g_threats_3.GetRect().y + g_threats_3.GetRect().h*0.5 - 118*0.5;
                    exp_player.set_frame(ex);
                    exp_player.SetRect(x_pos, y_pos);
                    exp_player.Show(g_screen);
                    SDL_RenderPresent(g_screen);
                }
                //g_threats1.ResetThreats(SCREEN_WIDTH);
                Mix_PlayChannel(-1, g_sound_exp_player, 0);
                SDL_Delay(100);
                g_playerobject.got_hit();
                power_player.Decrease();
                g_threats_3.ResetThreats(SCREEN_WIDTH);
                SDL_RenderPresent(g_screen);
                if(g_playerobject.get_life() == 0)
                {
                    GameOver = true;
                }
            }

            //va cham voi dan cua may bay 3
            std::vector <EnemyBullet*> enemybullet_list_3 = g_threats_3.get_bullet_list();
            for(int i = 0; i < enemybullet_list_3.size(); i++)
            {
                EnemyBullet* p_enemybullet_3 = enemybullet_list_3.at(i);
                if(p_enemybullet_3 != NULL)
                {
                    bool ret_col = SDL_Common::check_overlap(p_enemybullet_3->GetRect(), g_playerobject.GetRect());
                    if(ret_col)
                    {
                        for(int ex = 0; ex < 5; ex++)
                        {
                            int x_pos = g_playerobject.GetRect().x + g_playerobject.GetRect().w*0.5 - 118*0.5;
                            int y_pos = g_playerobject.GetRect().y + g_playerobject.GetRect().h*0.5 - 118*0.5;
                            exp_player.set_frame(ex);
                            exp_player.SetRect(x_pos, y_pos);
                            exp_player.Show(g_screen);
                            SDL_Delay(50);
                            SDL_RenderPresent(g_screen);
                        }
                        Mix_PlayChannel(-1, g_sound_exp_player, 0);
                        power_player.Decrease();
                        g_playerobject.got_hit();
                        g_threats_3.RemoveBullet(i);
                        SDL_RenderPresent(g_screen);
                        if(g_playerobject.get_life() == 0)
                        {
                            GameOver = true;
                        }
                    }
                }
            }

            //may bay 3 va cham voi laser
            std::vector <LaserObject*> laser_list_3 = g_playerobject.get_laser_list();
            for(int i = 0; i < laser_list_3.size(); i++)
            {
                LaserObject* p_laser_3 = laser_list_3.at(i);
                if(p_laser_3 != NULL)
                {
                    bool ret_col = SDL_Common::check_overlap(p_laser_3->GetRect(), g_threats_3.GetRect());
                    if(ret_col)
                    {
                        for(int ex = 0; ex < 5; ex++)
                        {
                            int x_pos = p_laser_3->GetRect().x + p_laser_3->GetRect().w*0.5 - 118*0.5;
                            int y_pos = p_laser_3->GetRect().y + p_laser_3->GetRect().h*0.5 - 118*0.5;
                            exp_player.set_frame(ex);
                            exp_player.SetRect(x_pos, y_pos);
                            exp_player.Show(g_screen);
                            //SDL_RenderPresent(g_screen);
                        }
                        if(threats_3_die == 1 || threats_3_die == 2)
                        {
                            threats_3_die--;
                            g_playerobject.RemoveLaser(i);
                        }
                        else if(threats_3_die == 0)
                        {
                            score_value++;
                            g_threats_3.ResetThreats(SCREEN_WIDTH);
                            threats_3_die = 2;
                            g_playerobject.RemoveLaser(i);
                        }
                        Mix_PlayChannel(-1, g_sound_exp_player, 0);
                    }
                }
            }

            //va cham voi dan cua boss
            std::vector <BossBullet*> bossbullet_list = g_boss.get_boss_bullet_list();
            for(int i = 0; i < bossbullet_list.size(); i++)
            {
                BossBullet* p_bossbullet = bossbullet_list.at(i);
                if(p_bossbullet != NULL)
                {
                    bool ret_col = SDL_Common::check_overlap(p_bossbullet->GetRect(), g_playerobject.GetRect());
                    if(ret_col&& CurrentTime>=LastTime+2000)
                    {
                        power_player.Decrease();
                        g_playerobject.got_hit();
                        g_playerobject.set_flick(true);
                        SDL_RenderPresent(g_screen);
                        if(g_playerobject.get_life() == 0)
                        {
                            a=255;
                            g_playerobject.set_flick(false);
                            GameOver = true;
                        }
                        LastTime=CurrentTime;
                    }
                    if (g_playerobject.get_flick()==true)
                    {
                        if (CurrentTime>=LastTime+2000)
                        {
                            g_playerobject.set_flick(false);
                            a=255;
                        }
                        else
                        {
                            g_playerobject.flicking(a);
                            g_playerobject.setAlpha(a);
                        }
                    }

                    if (g_playerobject.get_flick()==false)
                    {
                        g_playerobject.setAlpha(255);
                    }
                }
            }

            //dan play va cham voi boss
            std::vector <LaserObject*> laser_list_4 = g_playerobject.get_laser_list();
            for(int i = 0; i < laser_list_4.size(); i++)
            {
                LaserObject* p_laser_4 = laser_list_4.at(i);
                if(p_laser_4 != NULL)
                {
                    bool ret_col = SDL_Common::check_overlap(p_laser_4->GetRect(), g_boss.GetRect());
                    if(ret_col)
                    {
                        for(int ex = 0; ex < 5; ex++)
                        {
                            int x_pos = p_laser_4->GetRect().x + p_laser_4->GetRect().w*0.5 - 118*0.5;
                            int y_pos = p_laser_4->GetRect().y + p_laser_4->GetRect().h*0.5 - 118*0.5;
                            exp_player.set_frame(ex);
                            exp_player.SetRect(x_pos, y_pos);
                            exp_player.Show(g_screen);
                            //SDL_RenderPresent(g_screen);
                        }
                        g_boss.got_hit(2);
                        g_playerobject.RemoveLaser(i);
                        if(g_boss.get_health() <= 0)
                        {
                            if(MessageBox(NULL, "Game Win!", "Box", MB_OK) == IDOK)
                            {
                                Clean();
                                SDL_Quit();
                                return 1;
                            }
                        }
                    }
                }
            }


            //Show score
            std::string val_str_score = std::to_string(score_value);
            std::string strScore("Score: ");
            strScore += val_str_score;
            score_game.SetText(strScore);
            score_game.LoadFromRenderText(font_time, g_screen);
            score_game.RenderText(g_screen, SCREEN_WIDTH*0.5 -50, 5);

            if(score_value >= 5)
            {
                g_threats_2.HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);

                g_threats_2.Render(g_screen, NULL);

                g_threats_2.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
            }

            if(score_value >= 10)
            {
                g_threats_3.HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);

                g_threats_3.Render(g_screen, NULL);

                g_threats_3.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
            }

            if(score_value >= 1)
            {
                g_boss.MoveThreat();
                g_boss.Show(g_screen, NULL);
                if(g_boss.canspawnbullet() == true)
                {
                    g_boss.GenerateBullet(g_screen);
                }
                g_boss.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

            }

            //Show game time
            std::string str_time = "Time: ";
            Uint32 time_val = SDL_GetTicks() / 1000;

            std::string str_val = std::to_string(time_val);
            str_time += str_val;
            time_game.SetText(str_time);
            time_game.LoadFromRenderText(font_time, g_screen);
            time_game.RenderText(g_screen, SCREEN_WIDTH - 140, 5);
            SDL_RenderPresent(g_screen);//đưa ảnh vào màn hình

            int real_imp_time = fps_timer.get_ticks();
            int time_one_frame = 2500/FRAME_PER_SECOND;

            if(real_imp_time < time_one_frame)
            {
                int delay_time = time_one_frame - real_imp_time;
                if(delay_time >= 0)
                {
                    SDL_Delay(delay_time);
                }
            }
        }
        else
        {
            //Cho nhac tat di o day


            while(SDL_PollEvent(&g_event) !=0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    is_quit = true;
                }

            //Them gi do o day de handle viec reset game

            }
            SDL_SetRenderDrawColor( g_screen, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( g_screen );
            SDL_ShowCursor(SDL_ENABLE);  //Hien con tro chuot
            gameover.Render(g_screen, NULL);
            SDL_RenderPresent(g_screen);
        }
    }
    Clean();
    return 0;
}
