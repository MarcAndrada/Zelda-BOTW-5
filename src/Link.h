#ifndef PACMAN_H
#define PACMAN_H

#include "Utils.h"
#include "Entity.h"

enum AttackDirecctions { ANONE, AUP, ADOWN, ALEFT, ARIGHT };

class Link : public Entity {
public:
	Link();
	~Link();
	void init(int x, int y);
	void update();
	void render();
	Classes getClassName() { return LINK; };

protected:
	Directions getNextDirection();
	AttackDirecctions GetDirectionAttack();
	void Attack();
	bool Attacking;
	C_Rectangle AttackHitbox;

	int Attack_Duration = 500;
	int Attack_time = 0;
};

#endif