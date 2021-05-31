#pragma once

#ifndef SCENE_WIN_H
#define SCENE_WIN_H

#include "includes.h"
#include "Scene.h"

class SceneWin : public Scene
{
public:

	SceneWin();
	~SceneWin();

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


	int youWin_img_id;
	C_Rectangle youWin_img_rect;

	int TimePassedWin;
	int TimeWin = 5000;
};


#endif
