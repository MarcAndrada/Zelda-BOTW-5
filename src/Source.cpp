#include "singletons.h"
#include "Scene.h"

unsigned int global_delta_time;
Scene* currentScene = NULL;

void mainLoop() {
	const clock_t begin_time = clock();
	clock_t old_time = begin_time;
	clock_t new_time = begin_time;

	while (sRenderer->WindowIsOpen()){

		old_time = new_time;
		new_time = clock(); - begin_time;
		global_delta_time = int(new_time - old_time);


		sInput->UpdateEvents();

		//Scene Update and Draw
		currentScene = sDirector->getCurrentScene();
		if (currentScene != NULL)
		{
			currentScene->onLoad();
			currentScene->onUpdate();
			currentScene->onRender();
		}
		

		//pintar cosas

		//Acabar de pintar cosas
	}

}

int main(){
	initSingletons();
	mainLoop();
	system("pause");
	return 0;
}