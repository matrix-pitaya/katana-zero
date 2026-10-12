#pragma once
#include"scene.h"
#include<graphics.h>
class SceneManger;
class GameSceneEight :public Scene
{
	friend class SceneManager;
public:
	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnRender() override;
	void OnInput(const ExMessage& msg) override;
	void OnExit() override;
	void DrawBackground();
	void DrawRemainHp();

private:
	GameSceneEight() = default;
	~GameSceneEight() = default;
};