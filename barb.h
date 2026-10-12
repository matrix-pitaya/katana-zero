#pragma once
#include"timer.h"
#include"vector2.h"
#include"animation.h"
#include"collision_box.h"
class Barb
{
public:
	Barb();
	~Barb();

	void OnUpdata(float delta);
	void OnRender();

	void SetPosition(const Vector2& position);
	bool CheckValid();

private:
	enum class Stage
	{
		Idle,
		Aim,
		Dash,
		Break
	};
private:
	const float DASH_SPEED = 1500.0f;
private:
	Timer idleTimer;
	Timer aimTimer;
	int diffPeriod = 0;
	bool isValid = true;
	float totalDeltaTime = 0;

	Vector2 velocity;
	Vector2 basePosition;
	Vector2 currentPosition;

	Animation animation_loose;
	Animation breakAnimation;
	Animation* currentAnimation = nullptr;

	Stage stage = Stage::Idle;
	CollisionBox* collisionBox = nullptr;

private:
	void OnBreak();
};