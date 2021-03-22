#include "SceneGame.h"
#include "singletons.h"

SceneGame::SceneGame() : Scene(){
	init();
}

SceneGame::~SceneGame(){

}

void SceneGame::preLoad(){

}

void SceneGame::unLoad()
{
}

void SceneGame::init(){
	sprite_id = sResManager->getSpriteID("Assets/sanic.png");
	sprite_rect = C_Rectangle{ 0,0,78, 82 };
	sprite_frame = 0;
	sprite_frame_time = 0;
	sprite_x = 50;
	sprite_y = 50;
	/*rect1 = C_Rectangle{ 20,30,200,100 };
	rect2 = C_Rectangle{ 60,200,50,100 };*/
}

void SceneGame::updateBegin(){
	sprite_frame_time += global_delta_time;
	if (sprite_frame_time > 150)
	{
		sprite_frame_time = 0;
		sprite_frame++;
		if (sprite_frame >= 8 )
		{
			sprite_frame = 0;
		}
		sprite_rect.x = sprite_rect.w * sprite_frame;
	}
	
}

void SceneGame::update() {
	sprite_rect.y = 0;
	if (sInput->isKeyPressed(Input::KEY_A)) { std::cout << "A PRESSED" << std::endl; }
	if (sInput->isKeyDown(Input::KEY_A)) {
		std::cout << "A DOWN" << std::endl;
		sprite_rect.y = sprite_rect.h;
	}
	if (sInput->isKeyReleased(Input::KEY_A)) { std::cout << "A RELEASED" << std::endl; }
	if (sInput->isKeyPressed(Input::BACKSPACE)) {
		sDirector->goBack();
	}

	if (sInput->isKeyPressed(Input::ARROW_RIGHT)) {
		sprite_x += 10;
	}
	if (sInput->isKeyPressed(Input::ARROW_LEFT)) {
		sprite_x -= 10;
	}
	if (sInput->isKeyPressed(Input::ARROW_DOWN)) {
		sprite_y += 10;
	}
	if (sInput->isKeyPressed(Input::ARROW_UP)) {
		sprite_y -= 10;
	}
}

void SceneGame::updateEnd(){

}

void SceneGame::renderBegin(){

}

void SceneGame::render(){
	sRenderer->drawSprite(sprite_id, sprite_x, sprite_y, sprite_rect);
	//sRenderer->drawRectangle(rect2 , Color{ 0,255,0 });
}

void SceneGame::renderEnd(){

}

void SceneGame::renderGUI(){

}
