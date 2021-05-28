#include "Door.h"
#include "singletons.h"

Door::Door() : Entity() {
	init();
}

Door ::~Door() {
}

void Door::init(int x, int y) {
	sprite_id = sResManager->getSpriteID("Assets/OpenDoor.png");
	ClosedDoor_sprite_id= sResManager->getSpriteID("Assets/ClossedDoor.png");
	sprite_rect = C_Rectangle{ 0,0,32, 32 };
	mpRect.x = x;
	mpRect.y = y;
	mpXtoGo = x;
	mpYtoGo = y;
	Open = false;
}

void Door::update() {

	sprite_x = mpRect.x;
	sprite_y = mpRect.y;

}

void Door::render() {

	if (Open)
	{
		sRenderer->drawSprite(sprite_id, sprite_x, sprite_y, sprite_rect);
	}else{
		sRenderer->drawSprite(ClosedDoor_sprite_id, sprite_x, sprite_y, sprite_rect);

	}

}



bool Door::IsOpen()
{
	return Open;
}

void Door::OpenDoor(){
	Open = true;
}
