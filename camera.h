#pragma once
#include"vector2.h"
#include"timer.h"
class CameraManager;
class Camera
{
	friend class CameraManager;
public:
	Vector2& GetPosition()
	{
		return position;
	}

	void Reset()
	{
		position.x = 0;
		position.y = 0;
	}
	void OnUpdata(float delta)
	{
		if (isShaking)
		{
			shakeTimer.OnUpdata(delta);
			position.x = (-50 + rand() % 100) / 50.0f * shakingStrength;
			position.y = (-50 + rand() % 100) / 50.0f * shakingStrength;
		}
		shakeTimer.OnUpdata(delta);
	}
	void Shake(float strength,float duration)
	{
		isShaking = true;
		shakingStrength = strength;
		shakeTimer.SetWaitTime(duration);
		shakeTimer.Restart();
	}
private:
	Vector2 position;
	Timer shakeTimer;
	bool isShaking = false;
	float shakingStrength = 0;

	Camera()
	{
		shakeTimer.SetOneShot(true);
		shakeTimer.SetOnTimeout([&]()
			{
				isShaking = false;
				Reset();
			});
	}
	~Camera() = default;
};