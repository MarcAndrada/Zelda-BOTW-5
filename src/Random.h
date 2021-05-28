#ifndef RANDOM_H
#define RANDOM_H

#include "Utils.h"
#include "Entity.h"


class Random : public Entity {
public:
	Random();
	~Random();
	void init(int x, int y);
	void update();
	void render();
	Classes getClassName() { return RANDOM; };
protected:


};

#endif

