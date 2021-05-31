#include "Gems.h"
#include "singletons.h"

Gems::Gems(){

}

Gems::~Gems(){

}

void Gems::init(int x, int y){
	sprite_id = sResManager->getSpriteID("Assets/Gem.png");
	sprite_rect = C_Rectangle{ 0,0,32, 32 };
	mpRect.x = x;
	mpRect.y = y;
	mpXtoGo =  x;
	mpYtoGo = y;

}

void Gems::update(){
	sprite_x = mpRect.x;
	sprite_y = mpRect.y;
}

void Gems::render(){
	Entity::render();

}
