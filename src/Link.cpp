#include "Link.h"
#include "singletons.h"

Link::Link() : Entity() {
	Link::init(0,0);
}

Link ::~Link(){
}

void Link::init(int x, int y){
	sprite_id = sResManager->getSpriteID("Assets/link.png");
	sprite_rect = C_Rectangle{ 0,0,25, 30 };
	sprite_x = 100;
	sprite_y = 100;
	mpXtoGo = x;
	mpYtoGo = y;

}

void Link::render(){
	
	Entity::render();
	
}
Directions Link::getNextDirection()
{
	Directions dir = NONE;

	if (sInput->isKeyPressed(Input::KEY_A)) {
		dir = LEFT;
		std::cout << "AAAA" << std::endl;
	}
	else if (sInput->isKeyPressed(Input::KEY_D)) {
		dir = RIGHT;
		std::cout << "DDDD" << std::endl;
	}
	else if (sInput->isKeyPressed(Input::KEY_W)) {
		dir = UP;
		std::cout << "WWWW" << std::endl;
	}
	else if (sInput->isKeyPressed(Input::KEY_S)) {
		dir = DOWN;
		std::cout << "SSSSS" << std::endl;
	}

	return dir;
}

