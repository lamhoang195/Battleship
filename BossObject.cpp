#include "BossObject.h"

BossObject::BossObject()
{

    rect_.x = 0;//vi tri dau threat xuat hien
    rect_.y = -HEIGHT_BOSS;
    rect_.w = WIDTH_BOSS;
    rect_.h = HEIGHT_BOSS;

    //frame_width_boss_ = 0;
    //frame_height_boss_ = 0;
    //frame_boss_ = 0;

    x_val_boss_ = 0;
    y_val_boss_ = 0;
}

BossObject::~BossObject()
{
    /*if(p_boss_bullet_list_.size() > 0)
    {
        for(int i = 0; i < p_boss_bullet_list_.size(); i++)
        {
            BossBullet* p_boss_bullet = p_boss_bullet_list_.at(i);
            if(p_boss_bullet != NULL)
            {
                delete p_boss_bullet;
                p_boss_bullet = NULL;
            }
        }
        p_boss_bullet_list_.clear();
    }
        */
}

/*void BossObject::set_clip_boss()
{
    if(frame_width_boss_ > 0 && frame_height_boss_ > 0)
    {
        clip_boss_[0].x = 0;
        clip_boss_[0].y = 0;
        clip_boss_[0].w = 296;
        clip_boss_[0].h = 394;

        clip_boss_[1].x = 296;
        clip_boss_[1].y = 0;
        clip_boss_[1].w = 296;
        clip_boss_[1].h = 394;

        clip_boss_[2].x = 296*2;
        clip_boss_[2].y = 0;
        clip_boss_[2].w = 296;
        clip_boss_[2].h = 394;

        clip_boss_[3].x = 296*3;
        clip_boss_[3].y = 0;
        clip_boss_[3].w = 296;
        clip_boss_[3].h = 394;

        clip_boss_[4].x = 296*4;
        clip_boss_[4].y = 0;
        clip_boss_[4].w = 296;
        clip_boss_[4].h = 394;

        clip_boss_[5].x = 296*5;
        clip_boss_[5].y = 0;
        clip_boss_[5].w = 296;
        clip_boss_[5].h = 394;
    }
}*/
/*
void BossObject::ShowBoss(SDL_Renderer* screen)
{
    if(frame_boss_ >= 6)
    {
        frame_boss_ = 0;
    }

    SDL_Rect* current_clip_ = &clip_boss_[frame_boss_];
    SDL_Rect render_quad1 = {rect_.x, rect_.y, rect_.w, rect_.h};
    if(current_clip_ != NULL)
    {
        render_quad1.w = current_clip_->w;
        render_quad1.h = current_clip_->h;
    }
    SDL_RenderCopy(screen, p_object_, current_clip_, &render_quad1);
}*/

void BossObject::GenerateBulletBoss(SDL_Renderer* screen)
{
    BossBullet* p_boss_bullet = new BossBullet();

    p_boss_bullet->LoadImg("Image/Player/bossbullet.png", screen);

    p_boss_bullet->SetRect(this->rect_.x + 10, this->rect_.y + 60);

    p_boss_bullet->set_is_move(true);

    p_boss_bullet_list_.push_back(p_boss_bullet);
}

void BossObject::MakeBulletBoss(SDL_Renderer* des, const int& x_limit, const int& y_limit)
{
    for(int i = 0; i < p_boss_bullet_list_.size(); i++)
    {
        BossBullet* p_boss_bullet = p_boss_bullet_list_.at(i);
        if(p_boss_bullet)
        {
            if(p_boss_bullet->get_is_move())
            {
                p_boss_bullet->Render(des);
                p_boss_bullet->HandleBulletBoss(SCREEN_WIDTH, SCREEN_HEIGHT);
            }
            else
            {
                p_boss_bullet->set_is_move(true);
                p_boss_bullet->SetRect(this->rect_.x + 10, this->rect_.y + 60);
            }
        }
    }
}

void BossObject::HandleMove(const int& x_border, const int& y_border)
{
    rect_.y += y_val_boss_;
    if(rect_.y > 720)
    {
        rect_.y = -HEIGHT_BOSS;
        int rand_x = rand() % 800;
        if(rand_x > SCREEN_WIDTH)
        {
            rand_x = SCREEN_WIDTH * 0.5;
        }
        rect_.x = rand_x;
    }
}

/*bool BossObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);
    if(ret)
    {
        frame_width_boss_ = rect_.w/NUM_FRAME_BOSS;
        frame_height_boss_ = rect_.h;
    }
    return ret;
}*/

void BossObject::ResetBoss(const int& yborder)
{
    rect_.y = yborder;
    int rand_x = rand() % 800;
    if(rand_x > SCREEN_WIDTH)
    {
        rand_x = SCREEN_WIDTH * 0.5;
    }
    rect_.x = rand_x;

    for(int i = 0; i < p_boss_bullet_list_.size(); i++)
    {
        BossBullet* p_boss_bullet = p_boss_bullet_list_.at(i);
        if(p_boss_bullet)
        {
            ResetBulletBoss(p_boss_bullet);
        }
    }
}

void BossObject::ResetBulletBoss(BossBullet* p_boss_bullet)
{
    p_boss_bullet->SetRect(this->rect_.x + 32, this->rect_.y + 80);
}

void BossObject::RemoveBulletboss(const int& idx)//khởi tạo lại đạn khi va chạm ở viên đạn thứ bao nhiêu idx
{
    for(int i = 0; i < p_boss_bullet_list_.size(); i++)
    {
        BossBullet* p_boss_bullet = p_boss_bullet_list_.at(i);
        if(p_boss_bullet)
        {
            ResetBulletBoss(p_boss_bullet);
        }
    }
}
