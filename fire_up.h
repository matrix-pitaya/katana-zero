#pragma once
#include"vector2.h"
#include"collision_box.h"
#include"animation.h"
class FireUp
{
public:
	FireUp();
	~FireUp();

	void OnUpdata(float delta);
	void OnRender();

	void SetPosition(const Vector2& position);

	bool CheckValid();
private:
	enum class Stage
	{
		Idle,
		Aim,
		Fall,
		Break,
		Attacked
	};
private:
	int diffPeriod = 0;
	bool isValid = true;
	float totalDeltaTime = 0;

	Timer idleTimer;
	Timer aimTimer;

	Vector2 velocity;
	Vector2 basePosition;
	Vector2 currentPosition;

	Animation idleAnimation;
	Animation breakAnimation;
	Animation attackedAnimation;
	Animation* currentFireAnimation = nullptr;

	Stage stage = Stage::Idle;
	CollisionBox* collisionBox = nullptr;
private:
	const float GRAVITY = 980 * 2;	
private:
	void OnBreak();
	void OnAttacked();
};