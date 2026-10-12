#pragma once
#include"scene.h"
#include"animation.h"
#include<graphics.h>
class SceneManager;
class SelectScene: public Scene
{
	friend class SceneManager;
public:
	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnRender() override;
	void OnInput(const ExMessage& msg) override;
	void OnExit() override;

	void DrawBackground();
	void DrawForeground();
	void DrawRemote();
	void DrawAV();
	void DrawSelectGame();
	void DrawSelectVideo();
	void DrawBlurredScreen();
	void DrawTrophy();

private:
	SelectScene();
	~SelectScene() = default;

private:
	bool isLeftDown = false;
	bool isRightDown = false;
	bool isReadyDown = false;
	Animation animationBlurredScreen;
	bool isHandoff = false;
	Timer timerHandoff;
};