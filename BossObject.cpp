#include "BossObject.h"

BossObject::BossObject()
{

    x_pos = 0;
    y_pos = 0;
    x_speed = 0;
    y_speed = 0;

    angle = 0;
    angle_rotate_speed = 0;


    width_frame = 0;
    height_frame = 0;

    y_limit = 0;
    x_limit = 0;
    count = 0;
    reverse = 0;
    delay_shoot_time = 300;
    health = 0;

    CurrentTime = 0;
    LastTime = 0;
}

BossObject::~BossObject()
{

}

bool BossObject::LoadImg(string path, SDL_Renderer* screen)
{
    bool ret=BaseObject::LoadImg(path, screen);

    if(ret==true)
    {
        width_frame=rect_.w;
        height_frame=rect_.h;

    }
    return ret;
}

void BossObject::Show(SDL_Renderer* screen,const SDL_Rect* clip)
{
    SDL_Rect RenderQuad={x_pos, y_pos, width_frame, height_frame};
    SDL_RenderCopy(screen, p_object_,  clip, &RenderQuad);
}

void BossObject::MoveDead()
{
    y_pos += y_speed;
}

void BossObject::rotate_angle()
{
    if (reverse ==1 )
    {
        angle -= angle_rotate_speed;
    }
    else
    {
        angle += angle_rotate_speed;
    }
}

bool BossObject::canspawnbullet()
{
    CurrentTime = SDL_GetTicks();
    bool check_can_spawn = false;
    if(CurrentTime > LastTime + delay_shoot_time && y_pos >= y_limit)
    {
        LastTime = CurrentTime;
        check_can_spawn = true;
    }
    return check_can_spawn;
}

void BossObject::MoveThreat()
{
    y_pos += y_speed;
    if(y_pos >= y_limit)
    {
        y_pos = y_limit;
    }
    rect_.x = x_pos;
    rect_.y = y_pos;
}


void BossObject::GenerateBullet(SDL_Renderer* screen)
{
    if (health <= 500 && health > 400)
    {
        int random = RandomNumber(10, 30);
        for(int i = 0; i < 12; i++)
        {
            delay_shoot_time = 1000;
            BossBullet* p_bullet = new BossBullet();
            p_bullet->LoadImg("Image/Player/BulletThreat.png", screen);
            p_bullet->set_is_move(true);
            p_bullet->set_angle(30 + 10*i);
            p_bullet->set_x_speed(3);
            p_bullet->set_y_speed(3);
            p_bullet->set_pos(x_pos + width_frame/2 - (p_bullet->GetRect().w)/2, y_pos + height_frame/2);
            p_boss_bullet_list_.push_back(p_bullet);
        }
    }

    else if (health <= 400 && health > 300)
    {
        delay_shoot_time=100;
        BossBullet* p_bullet1 = new BossBullet();
        p_bullet1->LoadImg("Image/Player/BulletThreat.png", screen);
        p_bullet1->set_is_move(true);
        p_bullet1->set_angle(angle);
        p_bullet1->set_x_speed(3);
        p_bullet1->set_y_speed(3);
        p_bullet1->set_pos(x_pos + width_frame/2 - (p_bullet1->GetRect().w)/2, y_pos + height_frame/2);
        p_boss_bullet_list_.push_back(p_bullet1);

        BossBullet*p_bullet2 = new BossBullet();
        p_bullet2->LoadImg("Image/Player/BulletThreat.png", screen);
        p_bullet2->set_is_move(true);
        p_bullet2->set_angle(angle + 60);
        p_bullet2->set_x_speed(3);
        p_bullet2->set_y_speed(3);
        p_bullet2->set_pos(x_pos + width_frame/2 - (p_bullet1->GetRect().w)/2, y_pos + height_frame/2);
        p_boss_bullet_list_.push_back(p_bullet2);

        BossBullet*p_bullet3 = new BossBullet();
        p_bullet3->LoadImg("Image/Player/BulletThreat.png", screen);
        p_bullet3->set_is_move(true);
        p_bullet3->set_angle(angle + 120);
        p_bullet3->set_x_speed(3);
        p_bullet3->set_y_speed(3);
        p_bullet3->set_pos(x_pos + width_frame/2 - (p_bullet1->GetRect().w)/2, y_pos + height_frame/2);
        p_boss_bullet_list_.push_back(p_bullet3);

        BossBullet*p_bullet4=new BossBullet();
        p_bullet4->LoadImg("Image/Player/BulletThreat.png", screen);
        p_bullet4->set_is_move(true);
        p_bullet4->set_angle(angle + 180);
        p_bullet4->set_x_speed(3);
        p_bullet4->set_y_speed(3);
        p_bullet4->set_pos(x_pos + width_frame/2 - (p_bullet1->GetRect().w)/2, y_pos + height_frame/2);
        p_boss_bullet_list_.push_back(p_bullet4);

        BossBullet*p_bullet5 = new BossBullet();
        p_bullet5->LoadImg("Image/Player/BulletThreat.png",screen);
        p_bullet5->set_is_move(true);
        p_bullet5->set_angle(angle + 240);
        p_bullet5->set_x_speed(3);
        p_bullet5->set_y_speed(3);
        p_bullet5->set_pos(x_pos + width_frame/2-(p_bullet1->GetRect().w)/2, y_pos + height_frame/2);
        p_boss_bullet_list_.push_back(p_bullet5);

        BossBullet*p_bullet6 = new BossBullet();
        p_bullet6->LoadImg("Image/Player/BulletThreat.png", screen);
        p_bullet6->set_is_move(true);
        p_bullet6->set_angle(angle + 300);
        set_angle_rotate_speed(10);
        rotate_angle();
        p_bullet6->set_x_speed(3);
        p_bullet6->set_y_speed(3);
        p_bullet6->set_pos(x_pos + width_frame/2 - (p_bullet1->GetRect().w)/2, y_pos + height_frame/2);
        p_boss_bullet_list_.push_back(p_bullet6);
    }

    else if (health <= 300 && health > 200)
    {
        delay_shoot_time = 70;
        BossBullet*p_bullet = new BossBullet();
        p_bullet->LoadImg("Image/Player/BulletThreat.png", screen);
        p_bullet->set_is_move(true);
        p_bullet->set_angle(90);
        p_bullet->set_x_speed(5);
        p_bullet->set_y_speed(5);
        p_bullet->set_pos(RandomNumber(0, SCREEN_WIDTH), 0);
        p_boss_bullet_list_.push_back(p_bullet);
    }

    else if (health <= 200 && health > 100)
    {
        delay_shoot_time = 70;
        BossBullet*p_bullet = new BossBullet();
        p_bullet->LoadImg("Image/Player/BulletThreat.png", screen);
        p_bullet->set_is_move(true);
        p_bullet->set_angle(RandomNumber(10, 170));
        p_bullet->set_x_speed(3);
        p_bullet->set_y_speed(3);
        p_bullet->set_pos(x_pos + width_frame/2 - (p_bullet->GetRect().w)/2, y_pos + height_frame - 3*(p_bullet->GetRect().h)/2);
        p_boss_bullet_list_.push_back(p_bullet);
    }

    else if (health <= 100 && health > 0)
    {
        delay_shoot_time = 50;
        set_angle_rotate_speed(10);
        rotate_angle();
        BossBullet*p_bullet1 = new BossBullet();
        p_bullet1->LoadImg("Image/Player/BulletThreat.png", screen);
        p_bullet1->set_is_move(true);
        p_bullet1->set_angle(angle + 30);
        p_bullet1->set_x_speed(3);
        p_bullet1->set_y_speed(3);
        p_bullet1->set_pos(x_pos + width_frame/2 - (p_bullet1->GetRect().w)/2, y_pos + height_frame/2);
        p_boss_bullet_list_.push_back(p_bullet1);

        BossBullet*p_bullet2=new BossBullet();
        p_bullet2->LoadImg("Image/Player/BulletThreat.png",screen);
        p_bullet2->set_is_move(true);
        p_bullet2->set_angle(angle+150);
        p_bullet2->set_x_speed(3);
        p_bullet2->set_y_speed(3);
        p_bullet2->set_pos(x_pos+width_frame/2-(p_bullet1->GetRect().w)/2,y_pos+height_frame/2);
        p_boss_bullet_list_.push_back(p_bullet2);

        BossBullet*p_bullet3 = new BossBullet();
        p_bullet3->LoadImg("Image/Player/BulletThreat.png", screen);
        p_bullet3->set_is_move(true);
        p_bullet3->set_angle(angle + 270);
        p_bullet3->set_x_speed(3);
        p_bullet3->set_y_speed(3);
        p_bullet3->set_pos(x_pos + width_frame/2 - (p_bullet1->GetRect().w)/2, y_pos + height_frame/2);
        p_boss_bullet_list_.push_back(p_bullet3);
    }
}

void BossObject::MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit)
{
    for(int i = 0; i < p_boss_bullet_list_.size(); i++)
    {
        BossBullet* p_bullet = p_boss_bullet_list_.at(i);
        if(p_bullet)
        {
            if(p_bullet->get_is_move())
            {
                p_bullet->Render(des);
                p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
            }
            /*else
            {
                p_bullet->set_is_move(true);
                p_bullet->set_pos(x_pos+width_frame/2-(p_bullet->GetRect().w)/2,y_pos + height_frame/2);
            }*/
        }
    }
}

void BossObject::set_stats(SDL_Renderer* screen)
{
        LoadImg("Image/Player/boss0.png", screen);
        y_speed = 2;
}
