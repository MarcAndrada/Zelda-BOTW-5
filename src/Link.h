#ifndef LINK_H
#define LINK_H

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
	void AddGem();
	void AddKey();
	int GetGems();
	int GetHP();
	void SetGems(int CurrentGems);
	void SetHP(int currentHP);
	bool CheckKey() { return KeyOwned; }
	int EnemyHitted(Entity* ent);
	void TakeHit();
	void RestartPlayerPos(int altura, int anchura);
protected:
	Directions getNextDirection();
	AttackDirecctions GetDirectionAttack();

	bool				Attacking;
	C_Rectangle			AttackHitbox;
	int					Attack_Duration = 500;
	int					Attack_time = 0;
	int					GemsOwned;
	bool				KeyOwned;
	int					AttackHitBoxSprite_Id;
	int					AttackHitBoxSprite_X;
	int					AttackHitBoxSprite_Y;
	AttackDirecctions	AttackDir;
};

#endif