#include "LaserObject.h"

LaserObject::LaserObject()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
}

LaserObject::~LaserObject()
{

}

void LaserObject::HandleMove(const int &x_border, const int &y_border)
{
    rect_.y -= 7;
    if (rect_.y < y_border - rect_.h ){
        is_move_ = false;
    }
}
