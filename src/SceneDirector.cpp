#include "SceneDirector.h"

//Incluir escenas del juego
#include"SceneMenu.h"
#include"SceneGame.h"



SceneDirector* SceneDirector::instance = NULL;

SceneDirector::SceneDirector(){
	if (instance != NULL)
	{
		return;
	}
	initScenes();
}

SceneDirector::~SceneDirector(){

}

void SceneDirector::changeScene(SceneEnum next_scene, bool load_on_return, bool history){
	if (load_on_return){
		mCurrentScene->unLoad();
	}
	mCurrentScene->setLoaded(!load_on_return);
	if (history){
		mSceneHistory.push(mCurrentScene);
	}

	mCurrentScene = mScenes[next_scene];
}

void SceneDirector::goBack(bool load_on_return){
	if (load_on_return) {
		mCurrentScene->unLoad();
	}
	if (mSceneHistory.empty()){
		return;
	}
	Scene* prevScene = mSceneHistory.top();
	if (prevScene != NULL){
		mSceneHistory.pop();
		mCurrentScene->setLoaded(!load_on_return);
		mCurrentScene = prevScene;
	}
}

bool SceneDirector::checkCurrentScene(char WantedScene)
{
	/* --!
	* Devuelve true o false dependiendo de si la escena coincide o no
	* 
	*/
	switch (WantedScene)
	{
	case 'N':
		if (mCurrentScene == mScenes[NEW_GAME]) {
			return true;
		}
		else {
			return false;
		}
		break;

	case 'R':
		if (mCurrentScene == mScenes[RESUME_GAME]){
			return true;
		}
		else{
			return false;
		}
		break;
	default:
		break;
	}


	return false;
}

SceneDirector* SceneDirector::getInstance() {
	if (instance == NULL){
		instance = new SceneDirector();
	}

	return instance;
}


void SceneDirector::initScenes(){
	mScenes.resize(SceneDirector::LAST_NO_USE);

	SceneMenu* scene_menu = new SceneMenu();

	mScenes[MAIN_MENU] = scene_menu;
	
	
	for (int i = 0; i == MAIN_MENU; i++){
		mScenes[i]->preLoad();
	}

	mCurrentScene = mScenes[MAIN_MENU];
	SceneGame* scene_game = new SceneGame();
	mScenes[RESUME_GAME] = scene_game;
	mScenes[NEW_GAME] = scene_game;

	for (int i = MAIN_MENU + 1; i < LAST_NO_USE; i++) {
		mScenes[i]->preLoad();
	}

}
