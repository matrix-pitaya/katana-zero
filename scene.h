#pragma once
#include"scene_type.h"
#include<graphics.h>
class Scene
{
public:
	virtual void OnEnter() = 0;
	virtual void OnUpdata(float delta) = 0;
	virtual void OnRender() = 0;
	virtual void OnInput(const ExMessage& msg) = 0;
	virtual void OnExit() = 0;
};