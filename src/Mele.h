#ifndef MELE_H
#define MELE_H

#include "Utils.h"
#include "Entity.h"


class Mele : public Entity {
public:
	Mele();
	~Mele();
	void init(int x, int y, int playerPosX, int playerPosY);
	void update();
	void render();
	Classes getClassName() { return MELE; };

protected:
	int player_pos_X;
	int player_pos_Y;
};

#endif
