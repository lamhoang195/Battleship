#ifndef BOSS_OBJECT_H
#define BOSS_OBJECT_H

#include "CommonFunction.h"
#include "BaseObject.h"
#include "TextObject.h"
#include "BossBullet.h"
#include <vector>

#define NUM_FRAME_BOSS 6
#define WIDTH_BOSS 296
#define HEIGHT_BOSS 361


class BossObject : public BaseObject
{
public:
    BossObject();
    ~BossObject();

    //void set_clip_boss();
    //int get_frame_width_boss() const {return frame_width_boss_;}
    //int get_frame_height_boss() const {return frame_height_boss_;}

    void set_x_val_boss(const float& xVal) {x_val_boss_= xVal;}
    void set_y_val_boss(const float& yVal) {y_val_boss_ = yVal;}
    int get_x_val_boss() const {return x_val_boss_;}
    int get_y_val_boss() const {return y_val_boss_;}


    void GenerateBulletBoss(SDL_Renderer* ren);//khởi tạo đạn boss

    void MakeBulletBoss(SDL_Renderer* des, const int& x_limit, const int& y_limit);//bắn đạn ra boss

    void set_boss_bullet_list(std::vector <BossBullet*> boss_bullet_list)
    {
        p_boss_bullet_list_ = boss_bullet_list;
    }

    std::vector <BossBullet*> get_boss_bullet_list() const {return p_boss_bullet_list_;}

    void ResetBoss(const int& yborder);//chạy lại threat

    void ResetBulletBoss(BossBullet* p_boss_bullet);//chạy lại đạn ở vị trí vs threat

    void RemoveBulletboss(const int& idx);//chay lai dan threats

    void ShowBoss(SDL_Renderer* screen);

    void HandleMove(const int& x_border, const int& y_border);

    //virtual bool LoadImg(std::string path, SDL_Renderer* screen);

private:
    //int frame_width_boss_;//kich thuoc 1 frame
    //int frame_height_boss_;
    //int frame_boss_;
    //SDL_Rect clip_boss_[6];

    int x_val_boss_;
    int y_val_boss_;
    bool is_move = 1;
    std::vector <BossBullet*> p_boss_bullet_list_;
};

#endif // BOSS_OBJECT_H
