#ifndef BOSS_BULLET_H
#define BOSS_BULLET_H

#include "BaseObject.h"
#include <vector>

#define WIDTH_BOSS 113
#define HEIGHT_BOSS 60

class BossBullet : public BaseObject
{
public:
	BossBullet();
	~BossBullet();

	void HandleBulletBoss(const int &x_border, const int &y_border);//vị trí đạn

	void set_is_move(const bool &isMove) {is_move_ = isMove;}
	bool get_is_move() const {return is_move_;};
    void set_boss_bullet_type(int type) {bullet_boss_type_ = type;} ;
    int get_boss_bullet_type() {return bullet_boss_type_;};

private:
	bool is_move_ = 1;
	int bullet_boss_type_= 0;
};


#endif // BOSS_BULLET_H
