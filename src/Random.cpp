#include "Random.h"
#include "singletons.h"

Random::Random(){
	init();
}

Random::~Random(){

}

void Random::init(int x, int y) {
	sprite_id = sResManager->getSpriteID("Assets/Random.png");
	sprite_rect = C_Rectangle{ 0,0,32, 32 };
	mpRect.x = x;
	mpRect.y = y;
	mpXtoGo = x;
	mpYtoGo = y;
}

void Random::update() {
	updateControls();
	if (!checkCollisionsWithMap()) {
		move();
	}
	else {
		mpMoving = false;
	}

	sprite_x = mpRect.x;
	sprite_y = mpRect.y;

}

void Random::render() {

	Entity::render();

}

Directions Random::getNextDirection()
{
	Directions dir = (Directions)(rand() % 4 + 1);
	return dir;
}