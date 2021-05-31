#include "SceneWin.h"
#include "singletons.h"

SceneWin::SceneWin()
{
}

SceneWin::~SceneWin()
{
}

void SceneWin::preLoad()
{
}

void SceneWin::unLoad()
{
}

void SceneWin::init(){
	youWin_img_id = sResManager->getSpriteID("Assets/WinScene.png");
	youWin_img_rect = C_Rectangle{ 0,0,sResManager->getSpriteWidth(youWin_img_id), sResManager->getSpriteHeight(youWin_img_id) };
	TimePassedWin = 0;
}

void SceneWin::updateBegin()
{
}

void SceneWin::update(){
	TimePassedWin += global_delta_time;

	if (TimePassedWin >= TimeWin)
	{
		sInput->closeWindow();
	}

}

void SceneWin::updateEnd()
{
}

void SceneWin::renderBegin()
{
}

void SceneWin::render(){
	sRenderer->drawSprite(youWin_img_id, 0, 0, youWin_img_rect);

}

void SceneWin::renderEnd()
{
}

void SceneWin::renderGUI()
{
}
