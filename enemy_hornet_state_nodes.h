#pragma once
#include"state_node.h"
#include"timer.h"

class EnemyHornet;
class EnemyHorentStateNode : public StateNode
{
public:
	EnemyHorentStateNode(EnemyHornet* hornet);

	void OnEnter() override = 0;
	void OnUpdata(float delta) override = 0;
	void OnExit() override = 0;
protected:
	EnemyHornet* hornet;
};

class EnemyHorentAimState :public EnemyHorentStateNode
{
public:
	EnemyHorentAimState(EnemyHornet* hornet);
	~EnemyHorentAimState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	Timer timer;
};

class EnemyHorentDashAirState :public EnemyHorentStateNode
{
public:
	EnemyHorentDashAirState(EnemyHornet* hornet);
	~EnemyHorentDashAirState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	const float DASH_SPEED = 1500.0f;
};

class EnemyHorentDashOnFloorState :public EnemyHorentStateNode
{
public:
	EnemyHorentDashOnFloorState(EnemyHornet* hornet);
	~EnemyHorentDashOnFloorState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	const float DASH_SPEED = 1000.0f;
private:
	Timer timer;
};

class EnemyHorentDeadState :public EnemyHorentStateNode
{
public:
	EnemyHorentDeadState(EnemyHornet* hornet);
	~EnemyHorentDeadState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
};

class EnemyHorentFallState :public EnemyHorentStateNode
{
public:
	EnemyHorentFallState(EnemyHornet* hornet);
	~EnemyHorentFallState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
};

class EnemyHorentIdleState :public EnemyHorentStateNode
{
public:
	EnemyHorentIdleState(EnemyHornet* hornet);
	~EnemyHorentIdleState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	Timer timer;
};

class EnemyHorentJumpState :public EnemyHorentStateNode
{
public:
	EnemyHorentJumpState(EnemyHornet* hornet);
	~EnemyHorentJumpState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	const float JUMP_SPEED = 1000.0f;
};

class EnemyHorentRunState :public EnemyHorentStateNode
{
public:
	EnemyHorentRunState(EnemyHornet* hornet);
	~EnemyHorentRunState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	const float RUN_SPEED = 500.0f;
	const float MIN_DIS = 350.0f;
};

class EnemyHorentSquatState :public EnemyHorentStateNode
{
public:
	EnemyHorentSquatState(EnemyHornet* hornet);
	~EnemyHorentSquatState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	Timer timer;
};

class EnemyHorentThrowBarbState :public EnemyHorentStateNode
{
public:
	EnemyHorentThrowBarbState(EnemyHornet* hornet);
	~EnemyHorentThrowBarbState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	Timer timer;
};

class EnemyHorentThrowSilkState :public EnemyHorentStateNode
{
public:
	EnemyHorentThrowSilkState(EnemyHornet* hornet);
	~EnemyHorentThrowSilkState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	Timer timer;
};

class EnemyHorentThrowSwordState :public EnemyHorentStateNode
{
public:
	EnemyHorentThrowSwordState(EnemyHornet* hornet);
	~EnemyHorentThrowSwordState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	Timer timerThrow;
	Timer timerSwitch;
};