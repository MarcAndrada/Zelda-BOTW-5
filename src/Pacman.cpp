#include "Pacman.h"
#include "singletons.h"

Pacman::Pacman() : Entity() {
	PUTime = 0;
}

Pacman ::~Pacman(){
}

void Pacman::render(){
	if (Entity::mpAlive){
		if (state) {
			ofSetColor(61, 114, 190);
			PUTime += global_delta_time;
			if (PUTime > 4500){
				state = false;
				PUTime = 0;
				mpSpeed = 150;
			}
		}else {
			ofSetColor(255, 255, 0);
		}	
		Entity::render();
	}
}
Directions Pacman::getNextDirection()
{
	Directions dir = NONE;

	if (sInput->isKeyPressed(Input::KEY_A)) {
		dir = LEFT;
	}
	else if (sInput->isKeyPressed(Input::KEY_D)) {
		dir = RIGHT;
	}
	else if (sInput->isKeyPressed(Input::KEY_W)) {
		dir = UP;
	}
	else if (sInput->isKeyPressed(Input::KEY_S)) {
		dir = DOWN;
	}

	return dir;
}

