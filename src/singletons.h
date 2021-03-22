#ifndef SENGLETONS_H
#define SINGLETONS_H

#include "Renderer.h"
#include "Input.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "SceneDirector.h"

void initSingletons();

extern Renderer* sRenderer;
extern Input* sInput;
extern ResourceManager* sResManager;
extern SceneDirector* sDirector;
extern SoundManager* sSoundManager;

#endif