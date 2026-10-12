#pragma once
#include"animation.h"
#include"collision_box.h"
class FireBullet
{
public:
	FireBullet(const Vector2& position, bool move_left);
	~FireBullet();

	void OnUpdata(float delta);
	void OnRender();

	bool CheckValid();
private:
	enum class Stage
	{
		Idle,
		Explode
	};
private:
	const float MOVE_SPEED = 1050.0f;

private:
	Vector2 position;
	Vector2 velocity;
	Animation animation;
	Animation animationExplode;
	Animation* currentAnimation = nullptr;
	bool isValid = true;
	CollisionBox* collisionBox = nullptr;
	Stage stage = Stage::Idle;
};