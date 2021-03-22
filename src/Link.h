#ifndef PACMAN_H
#define PACMAN_H

#include "Utils.h"
#include "Entity.h"


class Link : public Entity {
public:
	Link();
	~Link();
	void init(int x, int y);
	void render();
	Classes getClassName() { return LINK; };

protected:
	Directions getNextDirection();
	
};

#endif