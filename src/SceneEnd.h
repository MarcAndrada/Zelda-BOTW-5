#pragma once

#ifndef SCENE_END_H
#define SCENE_END_H

#include "includes.h"
#include "Scene.h"

class SceneEnd : public Scene
{
public:

	SceneEnd();
	~SceneEnd();

	virtual void preLoad();
	virtual void unLoad();

private:

	virtual void init();

	virtual void updateBegin();
	virtual void update();
	virtual void updateEnd();

	virtual void renderBegin();
	virtual void render();
	virtual void renderEnd();

	virtual void renderGUI();


	int youLose_img_id;
	C_Rectangle youLose_img_rect;

	int TimePassedEnd;
	int TimeEnd = 5000;
};


#endif
