#pragma once
#include"state_node.h"
#include"timer.h"

class Player;
class PlayerStateNode : public StateNode
{
public:
	PlayerStateNode(Player* player);

	void OnEnter() override  = 0;
	void OnUpdata(float delta) override = 0;
	void OnExit() override = 0;

protected:
	Player* player;
};

class PlayerAttackState : public PlayerStateNode
{
public:
	PlayerAttackState(Player* player);
	~PlayerAttackState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	Timer timer;
};

class PlayerDeadState :public PlayerStateNode
{
public:
	PlayerDeadState(Player* player);
	~PlayerDeadState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	Timer timer;
};

class PlayerFallState : public PlayerStateNode
{
public:
	PlayerFallState(Player* player);
	~PlayerFallState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
};

class PlayerIdleState :public PlayerStateNode
{
public:
	PlayerIdleState(Player* player);
	~PlayerIdleState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
};

class PlayerJumpState :public PlayerStateNode
{
public:
	PlayerJumpState(Player* player);
	~PlayerJumpState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
};

class PlayerRollState :public PlayerStateNode
{
public:
	PlayerRollState(Player* player);
	~PlayerRollState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
private:
	Timer timer;
};

class PlayerRunState :public PlayerStateNode
{
public:
	PlayerRunState(Player* player);
	~PlayerRunState();

	void OnEnter() override;
	void OnUpdata(float delta) override;
	void OnExit() override;
};