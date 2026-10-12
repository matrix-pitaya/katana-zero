#pragma once
#include"character.h"
#include"timer.h"

#define PLAYER_CD_ROLL (0.75f)
#define PLAYER_CD_ATTACK (0.5f)
#define PLAYER_RUN_SPEED (300.0f)
#define PLAYER_JUMP_SPEED (780.0f)
#define PLAYER_ROLL_SPEED (800.0f)

class Player : public Character
{
public:
	enum class AttackDir
	{
		Up,Down,Left,Right
	};

public:
	Player();
	~Player();

	void OnInput(const ExMessage& msg) override;
	void OnUpdata(float delta)override;
	void OnRender()override;
	void OnHurt()override;

	void SetRolling(bool flag);
	bool GetRolling();
	bool CanRoll();
	void SetAttacking(bool flag);
	bool GetAttacking();
	bool CanAttack();
	bool CanJump();
	int GetMoveDir();
	AttackDir GetAttackDir();
	void OnJump();
	void OnLand();
	void OnAttack();
	void OnRoll();
	void OnRun();
	void UpdataHitBoxPosition();

private:
	Timer timerRollCd;
	bool isRolling = false;
	bool isRollCdComp = false;

	Timer TimerAttackCd;
	bool IsAttacking = false;
	bool IsAttackCdComp = false;

	bool isLeftKeyDown = false;
	bool isRightKeyDown = false;
	bool isJumpKeyDown = false;
	bool isRollKeyDown = false;
	bool isAttackKeyDown = false;

	Animation animationSlashUp;
	Animation animationSlashDown;
	Animation animationSlashLeft;
	Animation animationSlashRight;
	AttackDir attackDir = AttackDir::Right;
	Animation* currentSlashAnimation = nullptr;

	bool isJumpVfxVisable = false;
	Animation animationJumpVfx;

	bool isLandVfxVisable = false;
	Animation animationLandVfx;

	bool isRunVfxVisable = false;
	Animation animationRunVfxRight;
	Animation animationRunVfxLeft;
	Animation* currentRunVfxAnimation = nullptr;

private:
	void UpdataAttackDir(int x, int y);
};