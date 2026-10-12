#pragma once
class BulletTimeManager
{
public:
	enum class Status
	{
		Entering,
		Exiting
	};
public:
	static BulletTimeManager* Instance();

	void PostProcess();
	void SetStatus(Status status);

	float OnUpdata(float delta);

private:
	static BulletTimeManager* instance;

	float progress = 0;
	Status status = Status::Exiting;

	const float SPEED_PROGRESS = 2.0f;
	const float DST_DELTA_FACTOR = 0.35f;
	const float DST_COLOR_FACTOR = 0.35f;

private:
	BulletTimeManager() = default;
	~BulletTimeManager() = default;
};