#ifndef ENEMY_BULLET_H_
#define ENEMY_BULLET_H_

#include "BaseObject.h"

#define ENEMY_BULLET_WIDTH 19;
#define ENEMY_BULLET_HEIGHT 19;

class EnemyBullet : public BaseObject
{
public:
	EnemyBullet();
	~EnemyBullet();

	void HandleBullet(const int &x_border, const int &y_border );//vị trí đạn

	void set_is_move(const bool &isMove) {is_move_ = isMove;}
	bool get_is_move() const {return is_move_;};
    void set_bullet_type(int type) {bullet_type_ = type;} ;
    int get_bullet_type() {return bullet_type_;};

private:
	bool is_move_ = 1;
	int bullet_type_= 0;
};
#endif // ENEMY_BULLET_H_
