#include"player_state_nodes.h"
#include"player.h"
#include"character_manager.h"
#include"scene_manager.h"
#include"bullet_time_manager.h"

PlayerStateNode::PlayerStateNode(Player* player) :player(player) {}

PlayerAttackState::PlayerAttackState(Player* player) : PlayerStateNode(player)
{
	timer.SetOneShot(true);
	timer.SetWaitTime(0.3f);
	timer.SetOnTimeout([&]()
		{
			this->player->SetAttacking(false);
		});
}
PlayerAttackState::~PlayerAttackState() = default;
void PlayerAttackState::OnEnter()
{
	player->SetAnimation("attack");
	player->UpdataHitBoxPosition();
	player->GetHitCollisionBox()->SetEnabled(true);
	player->SetAttacking(true);
	player->OnAttack();
	timer.Restart();

	switch (Utility::RandomRange(1, 3))
	{
		case 1:
			Utility::PlayAudio(_T("player_attack_1"), false);
			break;
		case 2:
			Utility::PlayAudio(_T("player_attack_2"), false);
			break;
		case 3:
			Utility::PlayAudio(_T("player_attack_3"), false);
			break;
	}
}
void PlayerAttackState::OnUpdata(float delta)
{
	timer.OnUpdata(delta);
	player->UpdataHitBoxPosition();
	if (player->GetHp() <= 0)
	{
		player->SwitchState("dead");
	}
	else if (!player->GetAttacking())
	{
		if (player->get_velocity().y > 0)
		{
			player->SwitchState("fall");
		}
		else if (player->IsOnFloor() && player->GetMoveDir() == 0)
		{
			player->SwitchState("idle");
		}
		else if (player->IsOnFloor() && player->GetMoveDir() != 0)
		{
			player->SwitchState("run");
		}
	}
}
void PlayerAttackState::OnExit()
{
	player->SetAttacking(false);
	player->GetHitCollisionBox()->SetEnabled(false);
}

PlayerDeadState::PlayerDeadState(Player* player) : PlayerStateNode(player)
{
	timer.SetOneShot(true);
	timer.SetWaitTime(2.0f);
	timer.SetOnTimeout([&]()
		{	
			MessageBox(GetHWnd(), _T("不对....\n这样不行。"), _T("挑战失败!"), MB_OK);
			SceneManager::Instance()->SetIsGameOver(true);
		});
}
PlayerDeadState::~PlayerDeadState() = default;
void PlayerDeadState::OnEnter()
{
	player->SetAnimation("dead");
	BulletTimeManager::Instance()->SetStatus(BulletTimeManager::Status::Exiting);
	Utility::PlayAudio(_T("player_dead"), false);
}
void PlayerDeadState::OnUpdata(float delta)
{
	timer.OnUpdata(delta);
}
void PlayerDeadState::OnExit()
{

}

PlayerFallState::PlayerFallState(Player* player) : PlayerStateNode(player) {}
PlayerFallState::~PlayerFallState() = default;
void PlayerFallState::OnEnter()
{
	player->SetAnimation("fall");
}
void PlayerFallState::OnUpdata(float delta)
{
	if (player->GetHp() <= 0)
	{
		player->SwitchState("dead");
	}
	else if (player->CanAttack())
	{
		player->SwitchState("attack");
	}
	else if (player->IsOnFloor())
	{
		player->SwitchState("idle");
		player->OnLand();
		Utility::PlayAudio(_T("player_land"), false);
	}
}
void PlayerFallState::OnExit()
{

}

PlayerIdleState::PlayerIdleState(Player* player) : PlayerStateNode(player) {}
PlayerIdleState::~PlayerIdleState() = default;
void PlayerIdleState::OnEnter()
{
	player->SetAnimation("idle");
}
void PlayerIdleState::OnUpdata(float delta)
{
	if (player->GetHp() <= 0)
	{
		player->SwitchState("dead");
	}
	else if (player->CanAttack())
	{
		player->SwitchState("attack");
	}
	else if (player->CanRoll())
	{
		player->SwitchState("roll");
	}
	else if (player->CanJump())
	{
		player->SwitchState("jump");
	}
	else if (player->IsOnFloor() && player->GetMoveDir() != 0)
	{
		player->SwitchState("run");
	}
	else if (player->get_velocity().y > 0)
	{
		player->SwitchState("fall");
	}
}
void PlayerIdleState::OnExit()
{

}

PlayerJumpState::PlayerJumpState(Player* player) : PlayerStateNode(player) {}
PlayerJumpState::~PlayerJumpState() = default;
void PlayerJumpState::OnEnter()
{
	player->SetAnimation("jump");
	player->OnJump();
	Utility::PlayAudio(_T("player_jump"), false);
}
void PlayerJumpState::OnUpdata(float delta)
{
	if (player->GetHp() <= 0)
	{
		player->SwitchState("dead");
	}
	else if (player->CanAttack())
	{
		player->SwitchState("attack");
	}
	else if (player->get_velocity().y > 0)
	{
		player->SwitchState("fall");
	}
}
void PlayerJumpState::OnExit()
{

}

PlayerRollState::PlayerRollState(Player* player) : PlayerStateNode(player)
{
	timer.SetOneShot(true);
	timer.SetWaitTime(0.35f);
	timer.SetOnTimeout([&]()
		{
			this->player->SetRolling(false);
		});
}
PlayerRollState::~PlayerRollState() = default;
void PlayerRollState::OnEnter()
{
	player->SetAnimation("roll");
	player->GetHurtCollisionBox()->SetEnabled(false);
	player->SetRolling(true);
	player->OnRoll();
	timer.Restart();
	Utility::PlayAudio(_T("player_roll"), false);
}
void PlayerRollState::OnUpdata(float delta)
{
	if (!player->GetRolling())
	{
		if (player->IsOnFloor() && player->GetMoveDir() != 0)
		{
			player->SwitchState("run");
		}
		else if (player->CanJump())
		{
			player->SwitchState("jump");
		}
		else
		{
			player->SwitchState("idle");
		}
	}
	timer.OnUpdata(delta);
}
void PlayerRollState::OnExit()
{
	player->SetRolling(false);
	player->GetHurtCollisionBox()->SetEnabled(true);
}

PlayerRunState::PlayerRunState(Player* player) :PlayerStateNode(player) {}
PlayerRunState::~PlayerRunState() = default;
void PlayerRunState::OnEnter()
{
	player->SetAnimation("run");
	player->OnRun();
	Utility::PlayAudio(_T("player_run"), true);
}
void PlayerRunState::OnUpdata(float delta)
{
	if (player->GetHp() <= 0)
	{
		player->SwitchState("dead");
	}
	else if (player->CanAttack())
	{
		player->SwitchState("attack");
	}
	else if (player->CanRoll())
	{
		player->SwitchState("roll");
	}
	else if (player->CanJump())
	{
		player->SwitchState("jump");
	}
	else if (player->IsOnFloor() && player->GetMoveDir() == 0)
	{
		player->SwitchState("idle");
	}
}
void PlayerRunState::OnExit()
{
	Utility::StopAudio(_T("player_run"));
}