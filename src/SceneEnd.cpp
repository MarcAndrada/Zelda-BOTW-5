#include "SceneEnd.h"
#include "singletons.h"

SceneEnd::SceneEnd(){

}

SceneEnd::~SceneEnd(){
}

void SceneEnd::preLoad(){

}

void SceneEnd::unLoad(){

}

void SceneEnd::init() {
	youLose_img_id = sResManager->getSpriteID("Assets/LoseScene.png");
	youLose_img_rect = C_Rectangle{ 0,0,sResManager->getSpriteWidth(youLose_img_id), sResManager->getSpriteHeight(youLose_img_id) };
	TimePassedEnd = 0;
}

void SceneEnd::updateBegin(){

}

void SceneEnd::update() {
	TimePassedEnd += global_delta_time;

	if (TimePassedEnd >= TimeEnd)
	{
		sInput->closeWindow();
	}

}

void SceneEnd::updateEnd(){

}

void SceneEnd::renderBegin(){

}

void SceneEnd::render(){
	sRenderer->drawSprite(youLose_img_id, 0, 0, youLose_img_rect);
}

void SceneEnd::renderEnd(){

}

void SceneEnd::renderGUI(){

}
