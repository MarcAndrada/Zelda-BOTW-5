#include "Link.h"
#include "singletons.h"

Link::Link() : Entity() {

}

Link ::~Link(){
}

void Link::init(int x, int y){
	sprite_id = sResManager->getSpriteID("Assets/link.png");
	AttackHitBoxSprite_Id = sResManager->getSpriteID("Assets/DamageZone.png");
	sprite_rect = C_Rectangle{ 0,0,32, 32 };
	mpRect.x = x;
	mpRect.y = y;
	mpXtoGo = x;
	mpYtoGo = y;
	HP = 9;
	mpSpeed = 125;
	KeyOwned = false;
	TimeDamaged = 2000;

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
	if (GetDirectionAttack() != ANONE && !Attacking) {
		Attacking = true;
		AttackDir = GetDirectionAttack();
		//sonido de ataque
		sSoundManager->playSound("assets/Audios/LinkAttack.wav");
	}

	switch (AttackDir)
	{
	case AUP:
		AttackHitbox = C_Rectangle{ mpRect.x,mpRect.y - 1 * TILE_SIZE,TILE_SIZE,TILE_SIZE };
		AttackHitBoxSprite_Y = mpRect.y - 1 * TILE_SIZE;
		AttackHitBoxSprite_X = mpRect.x;
		break;
	case ADOWN:
		AttackHitbox = C_Rectangle{  mpRect.x,mpRect.y + 1 * TILE_SIZE,TILE_SIZE,TILE_SIZE };
		AttackHitBoxSprite_Y = mpRect.y + 1 * TILE_SIZE;
		AttackHitBoxSprite_X = mpRect.x;
		break;
	case ALEFT:
		AttackHitbox = C_Rectangle{ mpRect.x - 1 * TILE_SIZE,mpRect.y ,TILE_SIZE,TILE_SIZE };

		AttackHitBoxSprite_Y = mpRect.y;
		AttackHitBoxSprite_X = mpRect.x - 1 * TILE_SIZE;
		break;
	case ARIGHT:
		AttackHitbox = C_Rectangle{  mpRect.x + 1 * TILE_SIZE,mpRect.y ,TILE_SIZE,TILE_SIZE };
		AttackHitBoxSprite_Y = mpRect.y;
		AttackHitBoxSprite_X = mpRect.x + 1 * TILE_SIZE;
		break;
	default:
		break;
	}
	
	if (Attacking)
	{
		sprite_id = sResManager->getSpriteID("Assets/LinkAttack.png");
		Attack_time += global_delta_time;

		

		if (Attack_time > Attack_Duration)
		{
			Attack_time = 0;
			//Parar animacion de ataque
			Attacking = false;
		}
	}
	else
	{
		sprite_id = sResManager->getSpriteID("Assets/link.png");

	}

	TimePassedDamaged += global_delta_time;
	

}

void Link::render(){
	
	Entity::render();
	if (Attacking)
	{
		sRenderer->drawSprite(AttackHitBoxSprite_Id, AttackHitBoxSprite_X, AttackHitBoxSprite_Y, AttackHitbox);
	}
}

void Link::AddGem(){
	GemsOwned++;
}

void Link::AddKey(){
	KeyOwned = true;
}

int Link::GetGems()
{
	return GemsOwned;
}

int Link::GetHP()
{
	return HP;
}

void Link::SetGems(int CurrentGems){
	GemsOwned = CurrentGems;
}

void Link::SetHP(int currentHP){
	HP = currentHP;
}


int Link::EnemyHitted(Entity* ent)
{
	C_Rectangle rectEntity = ent->getRect();
	C_Rectangle rectHitbox = C_Rectangle{ AttackHitbox.x, AttackHitbox.y, AttackHitbox.w , AttackHitbox.h };
	if (C_RectangleCollision(rectHitbox, rectEntity) && Attacking)
	{
		return ent->getClassName();
	}
	else
	{
		return NOTHING;
	}
}

void Link::TakeHit(){
	if (TimePassedDamaged >= TimeDamaged) {
		HP--;
		sSoundManager->playSound("assets/Audios/minecraftdmg.wav");

		if (HP <= 0) {
			setAlive(false);
		}
		TimePassedDamaged = 0;
	}


}

void Link::RestartPlayerPos(int altura, int anchura){
	int tiledx = mpXtoGo / TILE_SIZE;
	int tiledy = mpYtoGo / TILE_SIZE;
	if (tiledx == 0 || tiledx == 1 || tiledx == 2){
		mpRect.x = (anchura - 2) * TILE_SIZE;
		mpXtoGo = (anchura - 2) * TILE_SIZE;
	}
	else if (tiledx == anchura || tiledx == (anchura -1) || tiledx == (anchura - 2)){
		mpRect.x = 2 * TILE_SIZE;
		mpXtoGo = 2 * TILE_SIZE;
	}

	if (tiledy == 0 || tiledy == 1 || tiledy == 2){
		mpRect.y = (altura - 2) * TILE_SIZE;
		mpYtoGo = (altura - 2) * TILE_SIZE;
	}
	else if (tiledy == altura || tiledy == (altura - 1) || tiledy == (anchura - 2)){
		mpRect.y = 2 * TILE_SIZE;
		mpYtoGo = 2 * TILE_SIZE;
	}

}

Directions Link::getNextDirection()
{
	Directions dir = NONE;

	if (sInput->isKeyDown(Input::KEY_A)) {
		dir = LEFT;
	}
	else if (sInput->isKeyDown(Input::KEY_D)) {
		dir = RIGHT;
	}
	else if (sInput->isKeyDown(Input::KEY_W)) {
		dir = UP;
	}
	else if (sInput->isKeyDown(Input::KEY_S)) {
		dir = DOWN;
	}

	return dir;
}

AttackDirecctions Link::GetDirectionAttack()
{
	/* --!
	* Segun el input que se introduzca Cambiara entre una direccion u otra
	* retorna la direccion especificada
	*/
	AttackDirecctions CurrentADir;

	if (sInput->isKeyPressed(Input::ARROW_LEFT)) {
		CurrentADir = ALEFT;

	}
	else if (sInput->isKeyPressed(Input::ARROW_RIGHT)) {
		CurrentADir = ARIGHT;

	}
	else if (sInput->isKeyPressed(Input::ARROW_UP)) {
		CurrentADir = AUP;
	}
	else if (sInput->isKeyPressed(Input::ARROW_DOWN)) {
		CurrentADir = ADOWN;
	}
	else
	{
		CurrentADir = ANONE;
	}

	return CurrentADir;
}

