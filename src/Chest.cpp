#include "Chest.h"
#include "singletons.h"

Chest::Chest(){

}

Chest::~Chest(){

}

void Chest::init(int x, int y){
	sprite_id = sResManager->getSpriteID("Assets/Chest.png");
	sprite_rect = C_Rectangle{ 0,0,32, 32 };
	mpRect.x = x;
	mpRect.y = y;
	mpXtoGo = x;
	mpYtoGo = y; 
}

void Chest::update(){
	sprite_x = mpRect.x;
	sprite_y = mpRect.y;
}

void Chest::render(){
	Entity::render();
}
