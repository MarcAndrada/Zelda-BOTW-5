#include "Entity.h"
#include "singletons.h"

Entity::Entity(){
	mpRect = C_Rectangle{ 0,0,TILE_SIZE,TILE_SIZE };
	mMapWidth = 0;
	mMapHeight = 0;

	mpMoving = false;
	mpSpeed =  150;
	mpDirection = NONE;
	
	mpXtoGo = 0;
	mpYtoGo = 0;

	mpAlive = true;
	currentSpeed = 0;
}

Entity ::~Entity(){

}

void Entity::init(int x, int y){
	mpRect.x = x;
	mpRect.y = y;

	mpXtoGo = x;
	mpYtoGo = y;


}

void Entity::update(){
	updateControls();
	if (!checkCollisionsWithMap()){
		move(); 
	}else{
		mpMoving = false;
	}
}

void Entity::render(){
	sRenderer->drawSprite(sprite_id, sprite_x, sprite_y, sprite_rect);

}

void Entity::setCollisionsMap(std::vector<std::vector<bool>>* colmap, int w, int h){
	mpColMap = colmap;
	mMapWidth = w;
	mMapHeight = h;
	
}

int Entity::collidesWithEntity(Entity* ent){
	C_Rectangle rectEntity = ent->getRect();
	if (C_RectangleCollision(mpRect, rectEntity)){
		return ent->getClassName();
	}else{
		return NOTHING;
	}
	
}


void Entity::setAlive(bool alive){
	mpAlive = alive;
}


Directions Entity::getNextDirection(){
	return NONE;
}

void Entity::updateControls(){
	if (!mpMoving) {
		mpDirection = NONE;
		mpXtoGo = mpRect.x;
		mpYtoGo = mpRect.y;
		
		mpDirection = getNextDirection();

		switch (mpDirection) {
		default:
			break;
		case UP:
			mpYtoGo -= TILE_SIZE;
			break;
		case DOWN:
			mpYtoGo += TILE_SIZE;
			break;
		case LEFT:
			mpXtoGo -= TILE_SIZE;
			break;
		case RIGHT:
			mpXtoGo += TILE_SIZE;
			break;
		}

		
	} 
}

void Entity::move(){
	int xx = mpRect.x;
	int yy = mpRect.y;

	mpMoving = true;

	if (xx < mpXtoGo) {
		xx = xx + mpSpeed * global_delta_time / 1000;
	}
	else if (xx > mpXtoGo) {
		xx = xx - mpSpeed * global_delta_time / 1000;
	}

	if (yy < mpYtoGo) {
		yy = yy + mpSpeed * global_delta_time / 1000;
	}
	else if (yy > mpYtoGo) {
		yy = yy - mpSpeed * global_delta_time / 1000;
	}

	if ((mpRect.x < mpXtoGo && xx > mpXtoGo) ||
		(mpRect.x > mpXtoGo && xx < mpXtoGo)) {
		xx = mpXtoGo;
	}
	if ((mpRect.y < mpYtoGo && yy > mpYtoGo) ||
		(mpRect.y > mpYtoGo && yy < mpYtoGo)) {
		yy = mpYtoGo;
	}
	mpRect.x = xx;
	mpRect.y = yy;

	if (mpRect.x == mpXtoGo && mpRect.y == mpYtoGo) {
		mpMoving = false;
	}
}

bool Entity::checkCollisionsWithMap(){
	if (mpDirection == NONE) {
		return false;
	}
	int checkX = mpXtoGo / TILE_SIZE;
	int checkY = mpYtoGo / TILE_SIZE;

	if (checkY < 0 || checkY >= mMapHeight) {
		return true;
	}
	if (checkX < 0) {
		mpRect.x = (mMapWidth - 1) * TILE_SIZE;
		mpXtoGo = mpRect.x;
		return false;
	}else if (checkX >= mMapWidth) {
		mpRect.x = 0;
		mpXtoGo = mpRect.x;
		return false;
	}
	return (*mpColMap)[checkY][checkX];
	
}
