#pragma once
#include<functional>
using namespace std;
class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	void Restart()
	{
		passTime = 0;
		shotted = false;
	}
	void SetWaitTime(float val)
	{
		waitTime = val;
	}
	void SetOneShot(bool val)
	{
		oneShot = val;
	}
	void SetOnTimeout(function<void()> onTimeout)
	{
		this->onTimeout = onTimeout;
	}
	void Pause()
	{
		paused = true;
	}
	void Resume()
	{
		paused = false;
	}
	void OnUpdata(float delta)
	{
		if (paused)
		{
			return;
		}

		passTime += delta;
		if (passTime >= waitTime)
		{
			if ((!oneShot || (oneShot && !shotted)) && onTimeout)
			{
				onTimeout();
				shotted = true;
			}
			passTime -= waitTime;
		}
	}
private:
	float passTime = 0;
	float waitTime = 0;
	bool paused = false;
	bool oneShot = false;
	bool shotted = false;
	function<void()> onTimeout;
};