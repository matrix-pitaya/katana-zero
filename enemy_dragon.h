#pragma once
#include"character.h"
#include"fire_up.h"
#include"fire_bullet.h"
#include<vector>
using namespace std;

#define DRAGON_RUN_SPEED (300.0f)
#define DRAGON_JUMP_SPEED (780.0f)
#define DRAGON_ROLL_SPEED (800.0f)
#define DRAGON_DASH_POSITION (200.0f)

class Dragon :public Character
{
public:
	enum class AttackDir
	{
		Up, Down, Left, Right
	};

public:
	Dragon();
	~Dragon();

	void OnUpdata(float delta) override;
	void OnRender() override;
	void OnHurt() override;

	CollisionBox* GetDashCollisionBox();
	CollisionBox* GetSlashCollisionBox();
	void SetIsFacingLeft(bool flag);
	bool GetIsFacingLeft();
	void SetIsAttacking(bool flag);
	bool GetIsAttacking();
	void SetIsRolling(bool flag);
	bool GetIsRolling();
	void SetIsDashing(bool flag);
	bool GetIsDashing();
	void SetIsFiring(bool flag);
	bool GetIsFiring();
	void SetIsAiming(bool flag);
	bool GetIsAiming();

	void OnAttack();
	void OnDash();
	void OnRolling();
	void OnJump();
	void OnLand();
	void OnRun();
	void OnFire();
	void OnFireUp();
	void ShootFire();

	void UpdataAttackDir();
	AttackDir GetAttackDir();
	void UpdataSlashBoxPosition();
	void UpdataDashBoxPosition();
private:
	AttackDir attackDir = AttackDir::Left;

	bool IsAttacking = false;
	bool isRolling = false;
	bool isDashing = false;
	bool isFiring = false;
	bool isAiming = false;

	bool isLandVfxVisable = false;
	Animation animationLandVfx;
	bool isJumpVfxVisable = false;
	Animation animationJumpVfx;

	bool isRunVfxVisable = false;
	Animation animationRunVfxRight;
	Animation animationRunVfxLeft;
	Animation* currentRunVfxAnimation = nullptr;

	Animation animationSlashUp;
	Animation animationSlashDown;
	Animation animationSlashLeft;
	Animation animationSlashRight;
	Animation* currentSlashAnimation = nullptr;

	Animation animationFireVfxLeft;
	Animation animationFireVfxRight;
	Animation* currentFireVfxAnimation = nullptr;

	CollisionBox* collisionBoxDash = nullptr;
	CollisionBox* collisionBoxSlash = nullptr;

	vector<FireUp*> fireUpList;
	vector<FireBullet*> fireBulletList;
};