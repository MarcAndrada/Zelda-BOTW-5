#include "Link.h"
#include "singletons.h"

Link::Link() : Entity() {

}

Link ::~Link(){
}

void Link::init(int x, int y){
	sprite_id = sResManager->getSpriteID("Assets/link.png");
	sprite_rect = C_Rectangle{ 0,0,32, 32 };
	mpRect.x = x;
	mpRect.y = y;
	mpXtoGo = x;
	mpYtoGo = y;
}

void Link::update(){
	updateControls();
	if (!checkCollisionsWithMap()) {
		move();
	}
	else {
		mpMoving = false;
	}

	sprite_x = mpRect.x;
	sprite_y = mpRect.y;

	/* --!
	* Revisa si hay un input introducido  
	* Si es asi llama a la funcion de attack
	*/
	if (GetDirectionAttack() != ANONE) {
		Attack();
	}

	if (Attacking)
	{
		Attack_time += global_delta_time;
		if (Attack_time > Attack_Duration)
		{
			Attack_time = 0;
			//Parar animacion de ataque
			Attacking = false;
		}
	}
}

void Link::render(){
	
	Entity::render();
	
}

Directions Link::getNextDirection()
{
	Directions dir = NONE;

	if (sInput->isKeyPressed(Input::KEY_A)) {
		dir = LEFT;
		std::cout << "A" << std::endl;
	}
	else if (sInput->isKeyPressed(Input::KEY_D)) {
		dir = RIGHT;
		std::cout << "D" << std::endl;
	}
	else if (sInput->isKeyPressed(Input::KEY_W)) {
		dir = UP;
		std::cout << "W" << std::endl;
	}
	else if (sInput->isKeyPressed(Input::KEY_S)) {
		dir = DOWN;
		std::cout << "S" << std::endl;
	}

	return dir;
}


AttackDirecctions Link::GetDirectionAttack()
{
	/* --!
	* Segun el input que se introduzca Cambiara entre una direccion u otra
	* retorna la direccion especificada
	*/
	AttackDirecctions CurrentADir = ANONE;

	if (sInput->isKeyPressed(Input::ARROW_LEFT)) {
		CurrentADir = ALEFT;
		std::cout << "LEFT_ARR" << std::endl;

	}
	else if (sInput->isKeyPressed(Input::ARROW_RIGHT)) {
		CurrentADir = ARIGHT;
		std::cout << "RIGHT_ARR" << std::endl;

	}
	else if (sInput->isKeyPressed(Input::ARROW_UP)) {
		CurrentADir = AUP;
		std::cout << "UP_ARR" << std::endl;
	}
	else if (sInput->isKeyPressed(Input::ARROW_DOWN)) {
		CurrentADir = ADOWN;
		std::cout << "DOWN_ARR" << std::endl;
	}

	return CurrentADir;
}

void Link::Attack()
{
	
	if (!Attacking)
	{
		/* --!
		* crea un rectangulo dependiendo de la direccion de ataque
		* Activa un booleano
		* Al rato desactiva el booleano
		*/
		AttackDirecctions CurrentADir = GetDirectionAttack();
		switch (CurrentADir)
		{
		case AUP:
			AttackHitbox = C_Rectangle{ mpRect.y - 1 * TILE_SIZE, mpRect.x,TILE_SIZE,TILE_SIZE };
			break;
		case ADOWN:
			AttackHitbox = C_Rectangle{ mpRect.y + 1 * TILE_SIZE, mpRect.x,TILE_SIZE,TILE_SIZE };
			break;
		case ALEFT:
			AttackHitbox = C_Rectangle{ mpRect.y , mpRect.x - 1 * TILE_SIZE,TILE_SIZE,TILE_SIZE };
			break;
		case ARIGHT:
			AttackHitbox = C_Rectangle{ mpRect.y , mpRect.x + 1 * TILE_SIZE,TILE_SIZE,TILE_SIZE };
			break;
		default:
			break;
		}
		Attacking = true;
		//Hacer animacion de ataque
	}	

	//hacer que 0.5 s despues deje de atacar (Attacking = false;)
}

