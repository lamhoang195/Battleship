#ifndef POWER_OBJECT_H
#define POWER_OBJECT_H

#include "BaseObject.h"
#include <vector>

class PowerObject : public BaseObject
{
public:
    PowerObject();
    ~PowerObject();

    void set_number(const int& num) {number_health_ = num;}
    void add_pos(const int& xpos);
    void ShowP(SDL_Renderer* res);
    void InitP(SDL_Renderer* screen);
    void InitCrease();//tang health
    void Decrease();//giam health

private:
    int number_health_;
    std::vector <int> pos_list_;
};


#endif // POWER_OBJECT_H
