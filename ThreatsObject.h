#ifndef THREATS_OBJECT_H
#define THREATS_OBJECT_H

#include "CommonFunction.h"
#include "BaseObject.h"
#include "EnemyBullet.h"
#include <vector>

#define WIDTH_BLACKK4 82
#define HEIGHT_BLACKK4 84

class ThreatsObject : public BaseObject
{
public:
    ThreatsObject();
    ~ThreatsObject();

    int value;
    operator+(int num) {
        ThreatsObject result;
        result.value = value + num;
    }

    void HandleMove(const int& x_border, const int& y_border);

    void set_x_val(const float& xVal) {x_val_ = xVal;}
    void set_y_val(const float& yVal) {y_val_ = yVal;}
    float get_x_val() const {return x_val_;}
    float get_y_val() const {return y_val_;}

    void GenerateBullet(SDL_Renderer* ren, Mix_Chunk* bullet_sound);//khởi tạo đạn

    void MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit);//bắn đạn ra

    void set_bullet_list(std::vector <EnemyBullet*> bullet_list)
    {
        p_bullet_list_ = bullet_list;
    }

    std::vector <EnemyBullet*> get_bullet_list() const {return p_bullet_list_;}

    void ResetThreats(const int& yborder);//chạy lại threat

    void ResetBullet(EnemyBullet* p_bullet);//chạy lại đạn ở vị trí vs threat

    void RemoveBullet(const int& idx);//chay lai dan threats

private:
    float x_val_;
    float y_val_;
    bool is_move = 1;
    std::vector <EnemyBullet*> p_bullet_list_;
};

#endif // THREATS_OBJECT_H
