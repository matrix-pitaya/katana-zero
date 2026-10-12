#pragma once
#include"animation.h"
#include"collision_box.h"
class Sword
{
public:
	Sword(const Vector2& position, bool move_left);
	~Sword();

	void OnUpdata(float delta);
	void OnRender();

	bool CheckValid();

private:
	const float MOVE_SPEED = 1250.0f;

private:
	Vector2 position;
	Vector2 velocity;
	Animation animation;
	bool isValid = true;
	CollisionBox* collisionBox = nullptr;
};