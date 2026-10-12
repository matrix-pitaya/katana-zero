#pragma once
#include"scene.h"
#include"timer.h"
#include"animation.h"
#include<graphics.h>

#define SCENE_SPEED_PROGRESS (1.5f)
#define SCENE_SPEED_BACKGROUND (400)
#define SCENE_SPEED_KATANA_ZERO (450)
#define SCENE_SPEED_OTHERS (700)

class SceneManager;
class MenuScene :public Scene
{
	friend class SceneManager;
public:
	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnRender() override;
	void OnInput(const ExMessage& msg) override;
	void OnExit() override;

	void DrawBackground();
	void DrawBackgroundIron();
	void Draw_ZERO_Bottom();
	void Draw_ZER_Up();
	void Draw_O_Up();
	void Draw_KATANA();
	void DrawGrass();
	void DrawPlant();
	void DrawBlackBackground();
	void DrawEnter();

private:
	MenuScene();
	~MenuScene() = default;

private:
	Timer blinkTimer;
	Timer blinkDurationTimer;
	Timer blinkChangeTimer;

	bool isVisable = true;
	bool isBlinking = false;
	bool isEnterVisable = true;

	Animation animationPlant;

	int grassMoveLine = 0;
	Timer grassLineMoveTimer;

	bool isOuting = false;
	float progress = 0;
	
	float katanaZeroMovePositionY = 0;
	float othersMovePositionY = 0;
	float backgroundMoveY = 0;

	float blackBackgroundY = getwidth();
};