#include "Door.h"
#include "singletons.h"

Door::Door() : Entity() {

}

Door ::~Door() {
}

void Door::init(int x, int y) {
	sprite_id = sResManager->getSpriteID("Assets/link.png");
	sprite_rect = C_Rectangle{ 0,0,32, 32 };
	mpRect.x = x;
	mpRect.y = y;
	mpXtoGo = x;
	mpYtoGo = y;
}

void Door::update() {
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

void Door::render() {

	Entity::render();

}