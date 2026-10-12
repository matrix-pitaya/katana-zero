#pragma once
#include"state_node.h"
#include"timer.h"

class Dragon;
class EnemyDragonSatNode : public StateNode
{
public:
	EnemyDragonSatNode(Dragon* dragon);

	void OnEnter() override = 0;
	void OnUpdata(float delta) override = 0;
	void OnExit() override = 0;

protected:
	Dragon* dragon;
};

class EnemyDragonAimSate :public EnemyDragonSatNode
{
public:
	EnemyDragonAimSate(Dragon* dragon);
	~EnemyDragonAimSate();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	Timer timer;
};

class EnemyDragonAimInAirSate :public EnemyDragonSatNode
{
public:
	EnemyDragonAimInAirSate(Dragon* dragon);
	~EnemyDragonAimInAirSate();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	Timer timer;
};

class EnemyDragonAttackState :public EnemyDragonSatNode
{
public:
	EnemyDragonAttackState(Dragon* dragon);
	~EnemyDragonAttackState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	Timer timer;
};

class EnemyDragonDashState :public EnemyDragonSatNode
{
public:
	EnemyDragonDashState(Dragon* dragon);
	~EnemyDragonDashState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	Timer timer;
};

class EnemyDragonDeadState :public EnemyDragonSatNode
{
public:
	EnemyDragonDeadState(Dragon* dragon);
	~EnemyDragonDeadState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	Timer timer;
};

class EnemyDragonFallState :public EnemyDragonSatNode
{
public:
	EnemyDragonFallState(Dragon* dragon);
	~EnemyDragonFallState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
};

class EnemyDragonFireState :public EnemyDragonSatNode
{
public:
	EnemyDragonFireState(Dragon* dragon);
	~EnemyDragonFireState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	Timer timer;
};

class EnemyDragonIdleState :public EnemyDragonSatNode
{
public:
	EnemyDragonIdleState(Dragon* dragon);
	~EnemyDragonIdleState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	Timer timer;
};

class EnemyDragonJumpState :public EnemyDragonSatNode
{
public:
	EnemyDragonJumpState(Dragon* dragon);
	~EnemyDragonJumpState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
};

class EnemyDragonRollState :public EnemyDragonSatNode
{
public:
	EnemyDragonRollState(Dragon* dragon);
	~EnemyDragonRollState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	Timer timer;
};

class EnmeyDragonRunState :public EnemyDragonSatNode
{
public:
	EnmeyDragonRunState(Dragon* dragon);
	~EnmeyDragonRunState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	const float MIN_DIS = 350.0f;
};

class EnemyDragonShootFireBullet :public EnemyDragonSatNode
{
public:
	EnemyDragonShootFireBullet(Dragon* dragon);
	~EnemyDragonShootFireBullet();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	Timer timerSwitch;
	Timer timerShoot;
};