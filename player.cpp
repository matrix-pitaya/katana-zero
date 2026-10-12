#include"player.h"
#include"scene_manager.h"
#include"resources_manager.h"
#include"player_state_nodes.h"
#include"camera_manager.h"
#include"bullet_time_manager.h"
using namespace std;
Player::Player()
{
	isFacingLeft = false;

	position = { 250,200 };

	logicHeight = 120;

	hitBox->SetSize({ 150,150 });
	hurtBox->SetSize({ 40,80 });

	hitBox->SetDstLayer(CollisionLayer::Enemy);
	hitBox->SetSrcLayer(CollisionLayer::None);

	hurtBox->SetDstLayer(CollisionLayer::None);
	hurtBox->SetSrcLayer(CollisionLayer::Player);

	hitBox->SetEnabled(false);
	hurtBox->SetOnCollide([&]() {DecreaseHp(); });

	timerRollCd.SetOneShot(true);
	timerRollCd.SetWaitTime(PLAYER_CD_ROLL);
	timerRollCd.SetOnTimeout([&]()
		{
			isRollCdComp = true;
		});

	TimerAttackCd.SetOneShot(true);
	TimerAttackCd.SetWaitTime(PLAYER_CD_ATTACK);
	TimerAttackCd.SetOnTimeout([&]()
		{
			IsAttackCdComp = true;
		});

	{
		AnimationGroup& animation_attack = animationPool["attack"];
		Animation& animation_attack_left = animation_attack.left;
		animation_attack_left.set_loop(false);
		animation_attack_left.set_interval(0.05f);
		animation_attack_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_attack_left.add_frame(ResourcesManager::Instance()->FindImage("player_attack_left"), 5);

		Animation& animation_attack_right = animation_attack.right;
		animation_attack_right.set_loop(false);
		animation_attack_right.set_interval(0.05f);
		animation_attack_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_attack_right.add_frame(ResourcesManager::Instance()->FindImage("player_attack_right"), 5);
	}
	{
		AnimationGroup& animation_dead = animationPool["dead"];
		Animation& animation_dead_left = animation_dead.left;
		animation_dead_left.set_loop(false);
		animation_dead_left.set_interval(0.1f);
		animation_dead_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_dead_left.add_frame(ResourcesManager::Instance()->FindImage("player_dead_left"), 6);

		Animation& animation_dead_right = animation_dead.right;
		animation_dead_right.set_loop(false);
		animation_dead_right.set_interval(0.1f);
		animation_dead_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_dead_right.add_frame(ResourcesManager::Instance()->FindImage("player_dead_right"), 6);
	}
	{
		AnimationGroup& animation_fall = animationPool["fall"];
		Animation& animation_fall_left = animation_fall.left;
		animation_fall_left.set_interval(0.15f);
		animation_fall_left.set_loop(true);
		animation_fall_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_fall_left.add_frame(ResourcesManager::Instance()->FindImage("player_fall_left"), 5);

		Animation& animation_fall_right = animation_fall.right;
		animation_fall_right.set_interval(0.15f);
		animation_fall_right.set_loop(true);
		animation_fall_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_fall_right.add_frame(ResourcesManager::Instance()->FindImage("player_fall_right"), 5);
	}
	{
		AnimationGroup& idleAnimation = animationPool["idle"];
		Animation& animation_idle_left = idleAnimation.left;
		animation_idle_left.set_interval(0.15f);
		animation_idle_left.set_loop(true);
		animation_idle_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_idle_left.add_frame(ResourcesManager::Instance()->FindImage("player_idle_left"), 5);

		Animation& animation_idle_right = idleAnimation.right;
		animation_idle_right.set_interval(0.15f);
		animation_idle_right.set_loop(true);
		animation_idle_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_idle_right.add_frame(ResourcesManager::Instance()->FindImage("player_idle_right"), 5);
	}
	{
		AnimationGroup& animation_jump = animationPool["jump"];
		Animation& animation_jump_left = animation_jump.left;
		animation_jump_left.set_interval(0.15f);
		animation_jump_left.set_loop(false);
		animation_jump_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_jump_left.add_frame(ResourcesManager::Instance()->FindImage("player_jump_left"), 5);

		Animation& animation_jump_right = animation_jump.right;
		animation_jump_right.set_interval(0.15f);
		animation_jump_right.set_loop(false);
		animation_jump_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_jump_right.add_frame(ResourcesManager::Instance()->FindImage("player_jump_right"), 5);
	}
	{
		AnimationGroup& animation_roll = animationPool["roll"];
		Animation& animation_roll_left = animation_roll.left;
		animation_roll_left.set_interval(0.05f);
		animation_roll_left.set_loop(false);
		animation_roll_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_roll_left.add_frame(ResourcesManager::Instance()->FindImage("player_roll_left"), 7);

		Animation& animation_roll_right = animation_roll.right;
		animation_roll_right.set_interval(0.05f);
		animation_roll_right.set_loop(false);
		animation_roll_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_roll_right.add_frame(ResourcesManager::Instance()->FindImage("player_roll_right"), 7);
	}
	{
		AnimationGroup& animation_run = animationPool["run"];
		Animation& animation_run_left = animation_run.left;
		animation_run_left.set_interval(0.075f);
		animation_run_left.set_loop(true);
		animation_run_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_run_left.add_frame(ResourcesManager::Instance()->FindImage("player_run_left"), 10);

		Animation& animation_run_right = animation_run.right;
		animation_run_right.set_interval(0.075f);
		animation_run_right.set_loop(true);
		animation_run_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_run_right.add_frame(ResourcesManager::Instance()->FindImage("player_run_right"), 10);
	}

	animationSlashUp.set_interval(0.07f);
	animationSlashUp.set_loop(false);
	animationSlashUp.set_anchor_mode(Animation::AnchorMode::Centered);
	animationSlashUp.add_frame(ResourcesManager::Instance()->FindImage("player_vfx_attack_up"), 5);

	animationSlashDown.set_interval(0.07f);
	animationSlashDown.set_loop(false);
	animationSlashDown.set_anchor_mode(Animation::AnchorMode::Centered);
	animationSlashDown.add_frame(ResourcesManager::Instance()->FindImage("player_vfx_attack_down"), 5);

	animationSlashLeft.set_interval(0.07f);
	animationSlashLeft.set_loop(false);
	animationSlashLeft.set_anchor_mode(Animation::AnchorMode::Centered);
	animationSlashLeft.add_frame(ResourcesManager::Instance()->FindImage("player_vfx_attack_left"), 5);

	animationSlashRight.set_interval(0.07f);
	animationSlashRight.set_loop(false);
	animationSlashRight.set_anchor_mode(Animation::AnchorMode::Centered);
	animationSlashRight.add_frame(ResourcesManager::Instance()->FindImage("player_vfx_attack_right"), 5);

	animationJumpVfx.set_interval(0.05f);
	animationJumpVfx.set_loop(false);
	animationJumpVfx.set_anchor_mode(Animation::AnchorMode::BottomCentered);
	animationJumpVfx.add_frame(ResourcesManager::Instance()->FindImage("player_vfx_jump"), 5);
	animationJumpVfx.set_on_finished([&]() {isJumpVfxVisable = false; });

	animationLandVfx.set_interval(0.1f);
	animationLandVfx.set_loop(false);
	animationLandVfx.set_anchor_mode(Animation::AnchorMode::BottomCentered);
	animationLandVfx.add_frame(ResourcesManager::Instance()->FindImage("player_vfx_land"), 2);
	animationLandVfx.set_on_finished([&]() {isLandVfxVisable = false; });

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

	stateMachine.RegisterState("attack", new PlayerAttackState(this));
	stateMachine.RegisterState("dead"  , new PlayerDeadState(this));
	stateMachine.RegisterState("fall"  , new PlayerFallState(this));
	stateMachine.RegisterState("idle"  , new PlayerIdleState(this));
	stateMachine.RegisterState("jump"  , new PlayerJumpState(this));
	stateMachine.RegisterState("roll"  , new PlayerRollState(this));
	stateMachine.RegisterState("run"   , new PlayerRunState(this));

	stateMachine.SetEntry("idle");
}
Player::~Player()
{
	stateMachine.DestroyState("attack");
	stateMachine.DestroyState("dead");
	stateMachine.DestroyState("fall");
	stateMachine.DestroyState("idle");
	stateMachine.DestroyState("jump");
	stateMachine.DestroyState("roll");
	stateMachine.DestroyState("run");

	Utility::StopAudio(_T("player_run"));
}
void Player::OnInput(const ExMessage& msg)
{
	if (hp <= 0)
	{
		return;
	}
	switch (msg.message)
	{
		case WM_KEYDOWN:
			switch (msg.vkcode)
			{
				case 'W':
				case'w':
					isJumpKeyDown = true;
					break;

				case 'A':
				case'a':
					isLeftKeyDown = true;
					break;

				case 'S':
				case's':
					isRollKeyDown = true;
					break;

				case 'D':
				case'd':
					isRightKeyDown = true;
					break;
			}
			break;
		case WM_KEYUP:
			switch (msg.vkcode)
			{
				case 'W':
				case'w':
					isJumpKeyDown = false;
					break;

				case 'A':
				case'a':
					isLeftKeyDown = false;
					break;

				case 'S':
				case's':
					isRollKeyDown = false;
					break;

				case 'D':
				case'd':
					isRightKeyDown = false;
					break;
			}
			break;
		case WM_LBUTTONDOWN:
			isAttackKeyDown = true;
			UpdataAttackDir(msg.x, msg.y);
			break;

		case WM_LBUTTONUP:
			isAttackKeyDown = false;
			break;

		case WM_RBUTTONDOWN:
			Utility::PlayAudio(_T("bullet_time"), false);
			BulletTimeManager::Instance()->SetStatus(BulletTimeManager::Status::Entering);
			break;

		case WM_RBUTTONUP:
			Utility::StopAudio(_T("bullet_time"));
			BulletTimeManager::Instance()->SetStatus(BulletTimeManager::Status::Exiting);
			break;
	}
}
void Player::OnUpdata(float delta)
{
	if (hp > 0 && !isRolling)
	{
		velocity.x = GetMoveDir() * PLAYER_RUN_SPEED;
	}
	if (GetMoveDir() != 0)
	{
		isFacingLeft = (GetMoveDir() < 0);
	}

	TimerAttackCd.OnUpdata(delta);
	timerRollCd.OnUpdata(delta);

	Character::OnUpdata(delta);

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
}
void Player::OnRender()
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
}
void Player::OnHurt()
{
	Utility::PlayAudio(_T("player_hurt"), false);
	Character::OnHurt();
}
void Player::Player::SetRolling(bool flag)
{
	isRolling = flag;
}
bool Player::GetRolling()
{
	return isRolling;
}
bool Player::CanRoll()
{
	return isRollCdComp && !isRolling && isRollKeyDown;
}
void Player::SetAttacking(bool flag)
{
	IsAttacking = flag;
}
bool Player::GetAttacking()
{
	return IsAttacking;
}
bool Player::CanAttack()
{
	return IsAttackCdComp && !IsAttacking && isAttackKeyDown;
}
bool Player::CanJump()
{
	return IsOnFloor() && isJumpKeyDown;
}
int Player::GetMoveDir()
{
	return isRightKeyDown - isLeftKeyDown;
}
Player::AttackDir Player::GetAttackDir()
{
	return attackDir;
}
void Player::OnJump()
{
	velocity.y -= PLAYER_JUMP_SPEED;
	isJumpVfxVisable = true;
	animationJumpVfx.SetPosition(position);
	animationJumpVfx.Reset();
}
void Player::OnLand()
{
	isLandVfxVisable = true;
	animationLandVfx.SetPosition(position);
	animationLandVfx.Reset();
}
void Player::OnAttack()
{
	IsAttackCdComp = false;
	TimerAttackCd.Restart();
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
void Player::OnRoll()
{
	isRollCdComp = false;
	timerRollCd.Restart();
	velocity.x = isFacingLeft ? -PLAYER_ROLL_SPEED : PLAYER_ROLL_SPEED;
}
void Player::UpdataAttackDir(int x, int y)
{
	const float PI = 3.141592654f;
	float angle = atan2(y - position.y, x - position.x);

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
void Player::UpdataHitBoxPosition()
{
	const Vector2& pos_center = GetLogicCenter();
	const Vector2& size_hit_box = hitBox->GetSize();
	Vector2 pos_hit_box;
	switch (GetAttackDir())
	{
	case Player::AttackDir::Up:
		pos_hit_box = { pos_center.x,pos_center.y - size_hit_box.y / 2 };
		break;
	case Player::AttackDir::Down:
		pos_hit_box = { pos_center.x,pos_center.y + size_hit_box.y / 2 };
		break;
	case Player::AttackDir::Left:
		pos_hit_box = { pos_center.x - size_hit_box.x / 2,pos_center.y };
		break;
	case Player::AttackDir::Right:
		pos_hit_box = { pos_center.x + size_hit_box.x / 2,pos_center.y };
		break;
	}
	hitBox->SetPosition(pos_hit_box);
}
void Player::OnRun()
{
	if (!isLandVfxVisable)
	{
		isRunVfxVisable = true;
		currentRunVfxAnimation = isFacingLeft ? &animationRunVfxLeft : &animationRunVfxRight;
		currentRunVfxAnimation->SetPosition(position);
		currentRunVfxAnimation->Reset();
	}
}