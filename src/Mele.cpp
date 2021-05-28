#include "Mele.h"
#include "singletons.h"

Mele::Mele() : Entity() {
	init();
}

Mele ::~Mele() {

}

void Mele::init(int x, int y, int playerPosX, int playerPosY) {
	sprite_id = sResManager->getSpriteID("Assets/Mele.png");
	sprite_rect = C_Rectangle{ 0,0,32, 32 };
	mpRect.x = x;
	mpRect.y = y;
	mpXtoGo = x;
	mpYtoGo = y;
	player_pos_X = playerPosX;
	player_pos_Y = playerPosY;

}

void Mele::update() {
	updateControls();
	if (!checkCollisionsWithMap()) {
		move();
	}
	else {
		mpMoving = false;
	}

	sprite_x = mpRect.x;
	sprite_y = mpRect.y;

	/* --!
	* Revisa si hay un input introducido
	* Si es asi llama a la funcion de attack
	*/
}

void Mele::render() {

	Entity::render();

}

Directions Mele::getNextDirection()
{
	Directions dir = NONE;

	if (player_pos_X < mpRect.x)
	{
		dir = LEFT;	
	}
	else if (player_pos_Y < mpRect.y)
	{
		dir = UP;
	}else if (player_pos_X > mpRect.x)
	{
		dir = RIGHT;
	}
	else if (player_pos_Y > mpRect.y)
	{
		dir = DOWN;
	}

	return dir;
}
