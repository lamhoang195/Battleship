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
    void HandleInputAction(SDL_Event events);

    void set_x_val(const float& xVal) {x_val_ = xVal;}
    void set_y_val(const float& yVal) {y_val_ = yVal;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}

    void GenerateBullet(SDL_Renderer* ren);

    void MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit);//ban dan ra

    void set_bullet_list(std::vector <EnemyBullet*> bullet_list)
    {
        p_bullet_list_ = bullet_list;
    }

    std::vector <EnemyBullet*> get_bullet_list() const {return p_bullet_list_;}

    void ResetThreats(const int& yborder);

    void ResetBullet(EnemyBullet* p_bullet);

private:
    int x_val_;
    int y_val_;
    bool is_move = 1;
    std::vector <EnemyBullet*> p_bullet_list_;
};

#endif // THREATS_OBJECT_H
