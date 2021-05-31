#pragma once

#ifndef FILEKEY_H
#define FILEKEY_H

#include "Utils.h"
#include "Entity.h"


class Key : public Entity {
public:
	Key();
	~Key();
	void init(int x, int y);
	void update();
	void render();
	Classes getClassName() { return KEY; };
protected:

};

#endif
