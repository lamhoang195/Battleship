#pragma once

#ifndef LASER_OBJECT_H
#define LASER_OBJECT_H

#include "BaseObject.h"
#include "CommonFunction.h"

#define WIGTH_LASER_OBJECT 13
#define HEIGHT_LASER_OBJECT 54


class LaserObject : public BaseObject
{
public:
    LaserObject();
    ~LaserObject();

    void set_x_val(const int &xVal)
    {
        x_val_ = xVal;
    }
    void set_y_val(const int &yVal)
    {
        y_val_ = yVal;
    }
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}

    void set_is_move(const bool &isMove) {is_move_ = isMove;}
    bool get_is_move() const {return is_move_;}

    void HandleMove(const int &x_border, const int &y_border);

private:
    int x_val_;//lưu 1 lượng giá trị thay đổi
    int y_val_;
    bool is_move_;//trạng thái trong cửa sổ là 1 ngoài cửa là 0 xóa đi
};


#endif // LASER_OBJECT_H
