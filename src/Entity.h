#ifndef ENTITY_H
#define ENTITY_H

#include "Utils.h"

enum Directions { NONE, UP, DOWN, LEFT, RIGHT };

class  Entity {
public:
	Entity();
	~Entity();

	virtual void init(int x, int y);
	virtual void update();
	virtual void render();
	void setCollisionsMap(std::vector<std::vector<bool>>* colmap, int w, int h);
	C_Rectangle getRect() { return mpRect; };
	int collidesWithEntity(Entity* ent);
	virtual Classes getClassName() { return ENTITY; };
	bool isAlive() { return mpAlive; }
	void setAlive(bool alive);
	int GetMapPosX();
	int GetMapPosY();
	virtual void TakeHit();
	virtual void SetTargetPos(int X, int Y);
	void SetNextMap(int nextMap);
	int GetNextMap();

protected:

	C_Rectangle mpRect;
	virtual Directions getNextDirection();
	void updateControls();
	void move();
	bool checkCollisionsWithMap();
	std::vector<std::vector<bool>>* mpColMap;
	int mMapWidth;
	int mMapHeight;
	bool mpMoving;
	int mpSpeed;
	int currentSpeed;
	int mpDirection;
	int mpXtoGo;
	int mpYtoGo;
	bool mpAlive;
	int HP;
	float TimePassedDamaged = 0;
	float TimeDamaged = 1000;


	int				sprite_id;
	C_Rectangle		sprite_rect;
	int				sprite_frame;
	int				sprite_frame_time;
	int sprite_x;
	int sprite_y;
	int NextMap;
	
};

#endif