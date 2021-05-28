#ifndef GEMS_H
#define GEMS_H

#include "Utils.h"
#include "Entity.h"


class Gems : public Entity {
public:
	Gems();
	~Gems();
	void init(int x, int y);
	void update();
	void render();
	Classes getClassName() { return GEMS; };

protected:


};

#endif