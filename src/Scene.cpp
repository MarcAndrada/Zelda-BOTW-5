#include "Scene.h"
#include "singletons.h"

Scene::Scene(){
	mSceneLoaded = false;
	mSceneEntered = false;
}

Scene::~Scene(){

}

void Scene::preLoad(){

}

void Scene::unLoad()
{
}

void Scene::onLoad(){
	if (!mSceneLoaded)
	{
		init();
		setLoaded(true);
	}/*else if (){

	}*/
}

void Scene::onUpdate(){
	if (!mSceneLoaded){
		return;
	}
	updateBegin();
	update();
	updateEnd();
}

void Scene::onRender(){
	sRenderer->WindowClear();

	renderBegin();
	render();
	renderEnd();
	renderGUI();
	sRenderer->WindowRefresh();

}

void Scene::setLoaded(bool load){
	mSceneLoaded = load;
}

void Scene::init(){

}

void Scene::enterScene()
{
}

void Scene::updateBegin(){

}

void Scene::update(){

}

void Scene::updateEnd(){

}

void Scene::renderBegin(){

}

void Scene::render(){

}

void Scene::renderEnd(){

}

void Scene::renderGUI(){

}
