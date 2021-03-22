#ifndef PACMAN_H
#define PACMAN_H

#include "Utils.h"
#include "Entity.h"


class Pacman : public Entity {
public:
	 Pacman ();
	~ Pacman ();

	void render();
	Classes getClassName() { return LINK; };

protected:
	Directions getNextDirection();
	
};

#endif