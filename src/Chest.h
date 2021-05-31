#pragma once

#ifndef CHEST_H
#define CHEST_H

#include "Utils.h"
#include "Entity.h"


class Chest : public Entity {
public:
	Chest();
	~Chest();
	void init(int x, int y);
	void update();
	void render();
	Classes getClassName() { return CHEST; };

protected:

};

#endif
