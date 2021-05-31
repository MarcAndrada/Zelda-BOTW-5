#include "Key.h"
#include "singletons.h"

Key::Key(){

}

Key::~Key(){

}

void Key::init(int x, int y){
	sprite_id = sResManager->getSpriteID("Assets/Key.png");
	sprite_rect = C_Rectangle{ 0,0,32, 32 };
	mpRect.x = x;
	mpRect.y = y;
	mpXtoGo = x;
	mpYtoGo = y;
}

void Key::update(){
	sprite_x = mpRect.x;
	sprite_y = mpRect.y;
}

void Key::render(){
	Entity::render();
}

