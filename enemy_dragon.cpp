#include"enemy_dragon.h"
#include"collision_manager.h"
#include"resources_manager.h"
#include"character_manager.h"
#include"enemy_dragon_state_nodes.h"
#include"util.h"
#include<iostream>
Dragon::Dragon()
{
	hp = 15;
	isFacingLeft = true;
	position = { 1050,200 };
	logicHeight = 120;

	hitBox->SetSize({ 40,60 });
	hurtBox->SetSize({ 90,130 });

	hitBox->SetDstLayer(CollisionLayer::Player);
	hitBox->SetSrcLayer(CollisionLayer::None);

	hurtBox->SetDstLayer(CollisionLayer::None);
	hurtBox->SetSrcLayer(CollisionLayer::Enemy);

	hurtBox->SetOnCollide([&]() {DecreaseHp(); });

	collisionBoxDash = CollisionManager::Instance()->CreateCollisionBox();
	collisionBoxDash->SetEnabled(false);
	collisionBoxDash->SetDstLayer(CollisionLayer::Player);
	collisionBoxDash->SetSrcLayer(CollisionLayer::None);
	collisionBoxDash->SetSize({ 200,120 });

	collisionBoxSlash = CollisionManager::Instance()->CreateCollisionBox();
	collisionBoxSlash->SetEnabled(false);
	collisionBoxSlash->SetDstLayer(CollisionLayer::Player);
	collisionBoxSlash->SetSrcLayer(CollisionLayer::None);
	collisionBoxSlash->SetSize({ 150,150 });

	{
		AnimationGroup& animation_aim = animationPool["aim"];
		Animation& animation_left = animation_aim.left;
		animation_left.set_loop(false);
		animation_left.set_interval(0.1f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_aim_left"));

		Animation& animation_right = animation_aim.right;
		animation_right.set_loop(false);
		animation_right.set_interval(0.1f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_aim_right"));
	}
	{
		AnimationGroup& animation_attack = animationPool["attack"];
		Animation& animation_left = animation_attack.left;
		animation_left.set_loop(false);
		animation_left.set_interval(0.05f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_attack_left"));

		Animation& animation_right = animation_attack.right;
		animation_right.set_loop(false);
		animation_right.set_interval(0.05f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_attack_right"));
	}
	{
		AnimationGroup& animation_dash = animationPool["dash"];
		Animation& animation_left = animation_dash.left;
		animation_left.set_loop(false);
		animation_left.set_interval(0.1f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_dash_left"));

		Animation& animation_right = animation_dash.right;
		animation_right.set_loop(false);
		animation_right.set_interval(0.1f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_dash_right"));
	}
	{
		AnimationGroup& animation_dead = animationPool["dead"];
		Animation& animation_left = animation_dead.left;
		animation_left.set_loop(false);
		animation_left.set_interval(0.1f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_dead_left"));

		Animation& animation_right = animation_dead.right;
		animation_right.set_loop(false);
		animation_right.set_interval(0.1f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_dead_right"));
	}
	{
		AnimationGroup& animation_fall = animationPool["fall"];
		Animation& animation_left = animation_fall.left;
		animation_left.set_loop(true);
		animation_left.set_interval(0.15f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_fall_left"));

		Animation& animation_right = animation_fall.right;
		animation_right.set_loop(true);
		animation_right.set_interval(0.15f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_fall_right"));
	}
	{
		AnimationGroup& animation_fire = animationPool["fire"];
		Animation& animation_left = animation_fire.left;
		animation_left.set_loop(false);
		animation_left.set_interval(0.1f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_fire_left"));

		Animation& animation_right = animation_fire.right;
		animation_right.set_loop(false);
		animation_right.set_interval(0.1f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_fire_right"));
	}
	{
		AnimationGroup& idleAnimation = animationPool["idle"];
		Animation& animation_left = idleAnimation.left;
		animation_left.set_loop(true);
		animation_left.set_interval(0.15f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_idle_left"));

		Animation& animation_right = idleAnimation.right;
		animation_right.set_loop(true);
		animation_right.set_interval(0.15f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_idle_right"));
	}
	{
		AnimationGroup& animation_jump = animationPool["jump"];
		Animation& animation_left = animation_jump.left;
		animation_left.set_loop(false);
		animation_left.set_interval(0.15f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_jump_left"));

		Animation& animation_right = animation_jump.right;
		animation_right.set_loop(false);
		animation_right.set_interval(0.15f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_jump_right"));
	}
	{
		AnimationGroup& animation_roll = animationPool["roll"];
		Animation& animation_left = animation_roll.left;
		animation_left.set_loop(false);
		animation_left.set_interval(0.05f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_roll_left"));

		Animation& animation_right = animation_roll.right;
		animation_right.set_loop(false);
		animation_right.set_interval(0.05f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_roll_right"));
	}
	{
		AnimationGroup& animation_run = animationPool["run"];
		Animation& animation_left = animation_run.left;
		animation_left.set_loop(true);
		animation_left.set_interval(0.075f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_run_left"));

		Animation& animation_right = animation_run.right;
		animation_right.set_loop(true);
		animation_right.set_interval(0.075f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_run_right"));
	}
	{
		AnimationGroup& animation_aim_in_air = animationPool["aim_in_air"];
		Animation& animation_left = animation_aim_in_air.left;
		animation_left.set_loop(false);
		animation_left.set_interval(0.075f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindImage("enemy_dragon_aim_in_air_left"), 1);

		Animation& animation_right = animation_aim_in_air.right;
		animation_right.set_loop(false);
		animation_right.set_interval(0.075f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindImage("enemy_dragon_aim_in_air_right"), 1);
	}
	animationLandVfx.set_interval(0.1f);
	animationLandVfx.set_loop(false);
	animationLandVfx.set_anchor_mode(Animation::AnchorMode::BottomCentered);
	animationLandVfx.add_frame(ResourcesManager::Instance()->FindImage("player_vfx_land"), 2);
	animationLandVfx.set_on_finished([&]() {isLandVfxVisable = false; });

	animationJumpVfx.set_interval(0.05f);
	animationJumpVfx.set_loop(false);
	animationJumpVfx.set_anchor_mode(Animation::AnchorMode::BottomCentered);
	animationJumpVfx.add_frame(ResourcesManager::Instance()->FindImage("player_vfx_jump"), 5);
	animationJumpVfx.set_on_finished([&]() {isJumpVfxVisable = false; });

	animationSlashUp.set_interval(0.07f);
	animationSlashUp.set_loop(false);
	animationSlashUp.set_anchor_mode(Animation::AnchorMode::Centered);
	animationSlashUp.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_vfx_slash_up"));

	animationSlashDown.set_interval(0.07f);
	animationSlashDown.set_loop(false);
	animationSlashDown.set_anchor_mode(Animation::AnchorMode::Centered);
	animationSlashDown.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_vfx_slash_down"));

	animationSlashLeft.set_interval(0.07f);
	animationSlashLeft.set_loop(false);
	animationSlashLeft.set_anchor_mode(Animation::AnchorMode::Centered);
	animationSlashLeft.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_vfx_slash_left"));

	animationSlashRight.set_interval(0.07f);
	animationSlashRight.set_loop(false);
	animationSlashRight.set_anchor_mode(Animation::AnchorMode::Centered);
	animationSlashRight.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_vfx_slash_right"));

	animationFireVfxLeft.set_loop(false);
	animationFireVfxLeft.set_interval(0.1f);
	animationFireVfxLeft.set_anchor_mode(Animation::AnchorMode::BottomCentered);
	animationFireVfxLeft.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_vfx_fire_left"));

	animationFireVfxRight.set_loop(false);
	animationFireVfxRight.set_interval(0.1f);
	animationFireVfxRight.set_anchor_mode(Animation::AnchorMode::BottomCentered);
	animationFireVfxRight.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_dragon_vfx_fire_right"));

	animationRunVfxRight.set_interval(0.05f);
	animationRunVfxRight.set_loop(false);
	animationRunVfxRight.set_anchor_mode(Animation::AnchorMode::BottomCentered);
	animationRunVfxRight.add_frame(ResourcesManager::Instance()->FindAtlas("player_run_vfx_right"));
	animationRunVfxRight.set_on_finished([&]() {isRunVfxVisable = false; });

	animationRunVfxLeft.set_interval(0.05f);
	animationRunVfxLeft.set_loop(false);
	animationRunVfxLeft.set_anchor_mode(Animation::AnchorMode::BottomCentered);
	animationRunVfxLeft.add_frame(ResourcesManager::Instance()->FindAtlas("player_run_vfx_left"));
	animationRunVfxLeft.set_on_finished([&]() {isRunVfxVisable = false; });

	stateMachine.RegisterState("aim", new EnemyDragonAimSate(this));
	stateMachine.RegisterState("aim_in_air", new EnemyDragonAimInAirSate(this));
	stateMachine.RegisterState("attack", new EnemyDragonAttackState(this));
	stateMachine.RegisterState("dash", new EnemyDragonDashState(this));
	stateMachine.RegisterState("dead", new EnemyDragonDeadState(this));
	stateMachine.RegisterState("fall", new EnemyDragonFallState(this));
	stateMachine.RegisterState("fire", new EnemyDragonFireState(this));
	stateMachine.RegisterState("idle", new EnemyDragonIdleState(this));
	stateMachine.RegisterState("jump", new EnemyDragonJumpState(this));
	stateMachine.RegisterState("roll", new EnemyDragonRollState(this));
	stateMachine.RegisterState("run", new EnmeyDragonRunState(this));
	stateMachine.RegisterState("shoot", new EnemyDragonShootFireBullet(this));

	stateMachine.SetEntry("fall");
}
Dragon::~Dragon()
{
	CollisionManager::Instance()->DestroyCollisionBox(collisionBoxDash);
	CollisionManager::Instance()->DestroyCollisionBox(collisionBoxSlash);

	stateMachine.DestroyState("aim");
	stateMachine.DestroyState("aim_in_air");
	stateMachine.DestroyState("attack");
	stateMachine.DestroyState("dash");
	stateMachine.DestroyState("dead");
	stateMachine.DestroyState("fall");
	stateMachine.DestroyState("fire");
	stateMachine.DestroyState("idle");
	stateMachine.DestroyState("jump");
	stateMachine.DestroyState("roll");
	stateMachine.DestroyState("run");
	stateMachine.DestroyState("shoot");

	for (FireUp*& fireUp : fireUpList)
	{
		delete fireUp;
		fireUp = nullptr;
	}
	
	for (FireBullet*& fireBullet : fireBulletList)
	{
		delete fireBullet;
		fireBullet = nullptr;
	}
	
}
void Dragon::OnUpdata(float delta)
{
	if (velocity.x != 0)
	{
		isFacingLeft = (velocity.x < 0);
	}

	Character::OnUpdata(delta);

	hitBox->SetPosition(GetLogicCenter());

	if (isJumpVfxVisable)
	{
		animationJumpVfx.OnUpdata(delta);
	}
	if (isLandVfxVisable)
	{
		animationLandVfx.OnUpdata(delta);
	}
	if (isRunVfxVisable)
	{
		currentRunVfxAnimation->OnUpdata(delta);
	}
	if (IsAttacking)
	{
		currentSlashAnimation->SetPosition(GetLogicCenter());
		currentSlashAnimation->OnUpdata(delta);
	}
	if (isFiring)
	{
		currentFireVfxAnimation->SetPosition(position);
		currentFireVfxAnimation->OnUpdata(delta);
	}

	for (FireUp*& fireUp : fireUpList)
	{
		if (fireUp)
		{
			fireUp->OnUpdata(delta);
		}
	}
	for (FireBullet*& fireBullet : fireBulletList)
	{
		if (fireBullet)
		{
			fireBullet->OnUpdata(delta);
		}
	}
	
	fireUpList.erase(remove_if(fireUpList.begin(), fireUpList.end(), [](FireUp*& fireUp)
		{
			bool canRemove = !fireUp->CheckValid();
			if (canRemove)
			{
				delete fireUp;
				fireUp = nullptr;
			}
			return canRemove;
		}
	), fireUpList.end());

	fireBulletList.erase(remove_if(fireBulletList.begin(), fireBulletList.end(), [](FireBullet*& fireBullet)
		{
			bool canRemove = !fireBullet->CheckValid();
			if (canRemove)
			{
				delete fireBullet;
				fireBullet = nullptr;
			}
			return canRemove;
		}
	), fireBulletList.end());
}
void Dragon::OnRender()
{
	if (isJumpVfxVisable)
	{
		animationJumpVfx.OnRender();
	}
	if (isLandVfxVisable)
	{
		animationLandVfx.OnRender();
	}
	if (isRunVfxVisable)
	{
		currentRunVfxAnimation->OnRender();
	}
	Character::OnRender();
	if (IsAttacking)
	{
		currentSlashAnimation->OnRender();
	}
	if (isFiring)
	{
		currentFireVfxAnimation->OnRender();
	}

	for (FireUp*& fireUp : fireUpList)
	{
		if (fireUp)
		{
			fireUp->OnRender();
		}
	}
	for (FireBullet*& fireBullet : fireBulletList)
	{
		if (fireBullet)
		{
			fireBullet->OnRender();
		}
	}
}
void Dragon::OnHurt()
{
	//ÁúÍõÊÜÉËÒôÐ§
	Character::OnHurt();
}
CollisionBox* Dragon::GetDashCollisionBox()
{
	return collisionBoxDash;
}
CollisionBox* Dragon::GetSlashCollisionBox()
{
	return collisionBoxSlash;
}
void Dragon::SetIsFacingLeft(bool flag)
{
	isFacingLeft = flag;
}
bool Dragon::GetIsFacingLeft()
{
	return isFacingLeft;
}
void Dragon::SetIsAttacking(bool flag)
{
	IsAttacking = flag;
}
bool Dragon::GetIsAttacking()
{
	return IsAttacking;
}
void Dragon::SetIsRolling(bool flag)
{
	isRolling = flag;
}
bool Dragon::GetIsRolling()
{
	return isRolling;
}
void Dragon::SetIsDashing(bool flag)
{
	isDashing = flag;
}
bool Dragon::GetIsDashing()
{
	return isDashing;
}
void Dragon::OnAttack()
{
	switch (attackDir)
	{
	case AttackDir::Up:
		currentSlashAnimation = &animationSlashUp;
		break;
	case AttackDir::Down:
		currentSlashAnimation = &animationSlashDown;
		break;
	case AttackDir::Left:
		currentSlashAnimation = &animationSlashLeft;
		break;
	case AttackDir::Right:
		currentSlashAnimation = &animationSlashRight;
		break;
	}
	currentSlashAnimation->SetPosition(GetLogicCenter());
	currentSlashAnimation->Reset();
}
void Dragon::OnDash()
{
	position.x += isFacingLeft ? -DRAGON_DASH_POSITION : DRAGON_DASH_POSITION;
}
void Dragon::OnRolling()
{
	velocity.x = isFacingLeft ? -DRAGON_ROLL_SPEED : DRAGON_ROLL_SPEED;
}
void Dragon::OnFireUp()
{
	int numNewFireUp = Utility::RandomRange(3, 6);
	if (fireUpList.size() >= 10)
	{
		numNewFireUp = 1;
	}
	int widthNewFireUp = getwidth() / numNewFireUp;
	for (int i = 0; i < numNewFireUp; i++)
	{
		FireUp* OnFireUp = new FireUp();
		int randX = Utility::RandomRange(i * widthNewFireUp, (i + 1) * widthNewFireUp);
		int randY = Utility::RandomRange(250, 500);
		OnFireUp->SetPosition({ static_cast<float>(randX),static_cast<float>(randY) });
		fireUpList.push_back(OnFireUp);
	}
}
void Dragon::UpdataSlashBoxPosition()
{
	const Vector2& centerPosition = GetLogicCenter();
	const Vector2& slashBoxSize = collisionBoxSlash->GetSize();
	Vector2 SlashBoxPosition;
	switch (GetAttackDir())
	{
	case Dragon::AttackDir::Up:
		SlashBoxPosition = { centerPosition.x,centerPosition.y - slashBoxSize.y / 2 };
		break;
	case Dragon::AttackDir::Down:
		SlashBoxPosition = { centerPosition.x,centerPosition.y + slashBoxSize.y / 2 };
		break;
	case Dragon::AttackDir::Left:
		SlashBoxPosition = { centerPosition.x - slashBoxSize.x / 2,centerPosition.y };
		break;
	case Dragon::AttackDir::Right:
		SlashBoxPosition = { centerPosition.x + slashBoxSize.x / 2,centerPosition.y };
		break;
	}
	collisionBoxSlash->SetPosition(SlashBoxPosition);
}
void Dragon::UpdataDashBoxPosition()
{
	collisionBoxDash->SetPosition(GetLogicCenter());
}
void Dragon::UpdataAttackDir()
{
	Vector2& playerPosition = CharacterManager::Instance()->GetPlayer()->GetPosition();

	const float PI = 3.141592654f;
	float angle = atan2(playerPosition.y - position.y, playerPosition.x - position.x);

	if (angle >= -PI / 4 && angle < PI / 4)
	{
		attackDir = AttackDir::Right;
	}
	else if (angle >= PI / 4 && angle < 3 * PI / 4)
	{
		attackDir = AttackDir::Down;
	}
	else if ((angle >= 3 * PI / 4 && angle <= PI) || (angle >= -PI && angle < -3 * PI / 4))
	{
		attackDir = AttackDir::Left;
	}
	else
	{
		attackDir = AttackDir::Up;
	}
}
void Dragon::OnJump()
{
	velocity.y -= DRAGON_JUMP_SPEED;
	isJumpVfxVisable = true;
	animationJumpVfx.Reset();
	animationJumpVfx.SetPosition(position);
}
void Dragon::OnFire()
{
	animationFireVfxLeft.Reset();
	animationFireVfxRight.Reset();
	currentFireVfxAnimation = isFacingLeft ? &animationFireVfxLeft : &animationFireVfxRight;
}
void Dragon::OnLand()
{
	isLandVfxVisable = true;
	animationLandVfx.Reset();
	animationLandVfx.SetPosition(position);
}
void Dragon::OnRun()
{
	velocity.x = isFacingLeft ? -DRAGON_RUN_SPEED : DRAGON_RUN_SPEED;
	if (!isLandVfxVisable)
	{
		isRunVfxVisable = true;
		currentRunVfxAnimation = isFacingLeft ? &animationRunVfxLeft : &animationRunVfxRight;
		currentRunVfxAnimation->SetPosition(position);
		currentRunVfxAnimation->Reset();
	}
}
void Dragon::SetIsFiring(bool flag)
{
	isFiring = flag;
}
bool Dragon::GetIsFiring()
{
	return isFiring;
}
void Dragon::SetIsAiming(bool flag)
{
	isAiming = flag;
}
bool Dragon::GetIsAiming()
{
	return isAiming;
}
Dragon::AttackDir Dragon::GetAttackDir()
{
	return attackDir;
}
void Dragon::ShootFire()
{
	fireBulletList.push_back(new FireBullet(GetLogicCenter(), isFacingLeft));
}