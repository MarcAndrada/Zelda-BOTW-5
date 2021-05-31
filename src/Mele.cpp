#include "Mele.h"
#include "singletons.h"

Mele::Mele() : Entity() {

}

Mele ::~Mele() {

}

void Mele::init(int x, int y) {
	sprite_id = sResManager->getSpriteID("Assets/Mele.png");
	sprite_rect = C_Rectangle{ 0,0,32, 32 };
	mpRect.x = x;
	mpRect.y = y;
	mpXtoGo = x;
	mpYtoGo = y;
	mpSpeed = 60;
	HP = 3;
	TimeDamaged = 1500;
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

	TimePassedDamaged += global_delta_time;

	/* --!
	* Revisa si hay un input introducido
	* Si es asi llama a la funcion de attack
	*/
}

void Mele::render() {

	Entity::render();

}

void Mele::SetTargetPos(int X, int Y){
	player_pos_X = X;
	player_pos_Y = Y;
}

void Mele::TakeHit(){

	if (TimePassedDamaged >= TimeDamaged) {
		HP--;
		sSoundManager->playSound("assets/Audios/EnemyHitted.wav");

		if (HP <= 0) {
			setAlive(false);
		}
		TimePassedDamaged = 0;
	}
}



Directions Mele::getNextDirection()
{
	Directions dir = NONE;

	if (player_pos_X < mpRect.x){
		dir = LEFT;	
	}
	else if (player_pos_X > mpRect.x){
		dir = RIGHT;
	}
	else if (player_pos_Y < mpRect.y){
		dir = UP;
	}
	else if (player_pos_Y > mpRect.y){
		dir = DOWN;
	}

	return dir;
}
