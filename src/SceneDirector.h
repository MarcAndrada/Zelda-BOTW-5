#ifndef SCENE_DIRECTOR_H
#define SCENE_DIRECTOR_H

#include "includes.h"
#include "Scene.h"

class SceneDirector
{
	public:
		enum SceneEnum { MAIN_MENU, GAME, /*GAME_OVER, WIN,*/ LAST_NO_USE};

		SceneDirector();
		~SceneDirector();
		
		void changeScene(SceneEnum next_scene, bool load_on_return = true, bool history = true);
		void goBack(bool load_on_return = true);
		Scene* getCurrentScene() { return mCurrentScene; };

		static SceneDirector* getInstance();

	private:
		void initScenes();
		static SceneDirector* instance;

		Scene*				mCurrentScene;
		std::vector<Scene*> mScenes;
		std::stack<Scene*>	mSceneHistory;
};


#endif
