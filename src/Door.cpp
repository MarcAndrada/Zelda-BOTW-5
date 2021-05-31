#include "Door.h"
#include "singletons.h"

Door::Door() : Entity() {

}

Door ::~Door() {
}

void Door::init(int x, int y) {
	sprite_id = sResManager->getSpriteID("Assets/OpenDoor.png");
	sprite_rect = C_Rectangle{ 0,0,32, 32 };
	
	mpRect.x = x;
	mpRect.y = y;
	mpRect.h = 16;
	mpRect.w = 16;
	mpXtoGo = x;
	mpYtoGo = y;
	Open = false;
}

void Door::update() {

	sprite_x = mpRect.x;
	sprite_y = mpRect.y;

	if (Open)
	{
		sprite_id = sResManager->getSpriteID("Assets/OpenDoor.png");
	}
	else {
		sprite_id = sResManager->getSpriteID("Assets/ClosedDoor.png");

	}
}

void Door::render() {

	Entity::render();

}

bool Door::IsOpen()
{
	return Open;
}

void Door::OpenDoor(){
	Open = true;
}
