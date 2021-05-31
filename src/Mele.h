#ifndef MELE_H
#define MELE_H

#include "Utils.h"
#include "Entity.h"


class Mele : public Entity {
public:
	Mele();
	~Mele();
	void init(int x, int y);
	void update();
	void render();
	Classes getClassName() { return MELE; };
	void SetTargetPos(int X , int Y);
	void TakeHit();
protected:
	Directions getNextDirection();
	int player_pos_X;
	int player_pos_Y;
};

#endif
