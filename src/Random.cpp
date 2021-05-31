#include "Random.h"
#include "singletons.h"

Random::Random(){

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
	mpSpeed = 95;
	HP = 2;
	TimeDamaged = 1500;
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
	TimePassedDamaged += global_delta_time;

}

void Random::render() {

	Entity::render();

}

void Random::TakeHit() {

	if (TimePassedDamaged >= TimeDamaged) {
		HP--;
		sSoundManager->playSound("assets/Audios/EnemyHitted.wav");

		if (HP <= 0) {
			setAlive(false);
		}
		TimePassedDamaged = 0;
	}
}



Directions Random::getNextDirection()
{
	Directions dir = (Directions)(rand() % 4 + 1);
	return dir;
}

