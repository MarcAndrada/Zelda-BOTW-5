#include "SceneMenu.h"
#include "singletons.h"


SceneMenu::SceneMenu() : Scene(){

}

SceneMenu::~SceneMenu(){

}

void SceneMenu::preLoad(){

}

void SceneMenu::unLoad()
{
}

void SceneMenu::init(){
	menu_img_id = sResManager->getSpriteID("Assets/menu.png");
	menu_img_rect = C_Rectangle{ 0,0,sResManager->getSpriteWidth(menu_img_id), sResManager->getSpriteHeight(menu_img_id) };
	mMenuOption = CONTINUE;

	
}

void SceneMenu::updateBegin(){
	
}

void SceneMenu::update(){
	if (sInput->isKeyPressed(Input::ARROW_DOWN)){
		mMenuOption++;
		if (mMenuOption > EXIT)
		{
			mMenuOption = EXIT;
		}
	}
	else if (sInput->isKeyPressed(Input::ARROW_UP)){
		mMenuOption--;
		if (mMenuOption < CONTINUE)
		{
			mMenuOption = CONTINUE;
		}
	}
	
	
	
		switch (mMenuOption)
		{
			default:
				break;
			case CONTINUE:
				mOptionSelector = C_Rectangle{ 850, 290, 71, 21 };
				if (sInput->isKeyPressed(Input::SPACE)) {
					sDirector->changeScene(SceneDirector::RESUME_GAME, false);
					sGame = sDirector->getGameScene();
				}
				break;
			case NEW_GAME:
				if (sInput->isKeyPressed(Input::SPACE)) {
					sDirector->changeScene(SceneDirector::NEW_GAME, false);
					sGame = sDirector->getGameScene();

				}
				mOptionSelector = C_Rectangle{ 840, 320, 80, 23 };
				break;
			case OPTIONS:
				mOptionSelector = C_Rectangle{ 860, 350, 60, 20 };
				if (sInput->isKeyPressed(Input::SPACE)) {
				}
				break;
			case EXIT:
				mOptionSelector = C_Rectangle{ 870, 380, 44, 27 };
				if (sInput->isKeyPressed(Input::SPACE)) {
					
					sInput->closeWindow();
				}
				break;
		} 

		if (sInput->isKeyPressed(Input::SPACE)){
			sSoundManager->playSound("assets/Audios/coin.wav");
		}
			
	
	
}

void SceneMenu::updateEnd(){

}

void SceneMenu::renderBegin(){

}

void SceneMenu::render(){
	sRenderer->drawSprite(menu_img_id, 0, 0, menu_img_rect);
	sRenderer->drawRectangle(mOptionSelector, Color{ 255,255,255 }, true);
}

void SceneMenu::renderEnd(){

}

void SceneMenu::renderGUI(){

}
