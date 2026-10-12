#include"enemy_hornet_state_nodes.h"
#include"character_manager.h"
#include"resources_manager.h"
#include"enemy_hornet.h"
#include"player.h"
#include"vector2.h"
#include"scene_manager.h"
#include<math.h>

EnemyHorentStateNode::EnemyHorentStateNode(EnemyHornet* hornet) : hornet(hornet) {}

EnemyHorentAimState::EnemyHorentAimState(EnemyHornet* hornet): EnemyHorentStateNode(hornet)
{
	timer.SetOneShot(true);
	timer.SetWaitTime(0.5f);
	timer.SetOnTimeout([&]()
		{
			this->hornet->SetGravityEnabled(true);
			this->hornet->SwitchState("dash_in_air");
		});
}
EnemyHorentAimState::~EnemyHorentAimState() = default;
void EnemyHorentAimState::OnEnter()
{
	hornet->SetAnimation("aim");
	hornet->SetGravityEnabled(false);
	hornet->SetVelocity({ 0,0 });
	timer.Restart();
}
void EnemyHorentAimState::OnUpdata(float delta)
{
	timer.OnUpdata(delta);
	if (hornet->GetHp() <= 0)
	{
		hornet->SwitchState("dead");
	}
}
void EnemyHorentAimState::OnExit()
{

}

EnemyHorentDashAirState::EnemyHorentDashAirState(EnemyHornet* hornet) : EnemyHorentStateNode(hornet) {}
EnemyHorentDashAirState::~EnemyHorentDashAirState() = default;
void EnemyHorentDashAirState::OnEnter()
{
	hornet->SetAnimation("dash_in_air");
	Player* player = static_cast<Player*>(CharacterManager::Instance()->GetPlayer());
	hornet->SetIsFacingLeft(hornet->GetPosition().x > player->GetPosition().x);
	const Vector2& pos_player = player->GetPosition();
	Vector2 targetPosition = { (player->GetPosition().x),(player->GetFloorY()) };
	hornet->SetVelocity((targetPosition - hornet->GetPosition()).normalize() * DASH_SPEED);
	hornet->SetDashingInAir(true);
	hornet->SetGravityEnabled(false);
	hornet->OnDash();
	Utility::PlayAudio(_T("enemy_hornet_dash"), false);
}
void EnemyHorentDashAirState::OnUpdata(float delta)
{
	EnemyHornet* enemy_hornet = (EnemyHornet*)CharacterManager::Instance()->GetEnemy();
	if (enemy_hornet->GetHp() <= 0)
	{
		enemy_hornet->SwitchState("dead");
	}
	else if (enemy_hornet->IsOnFloor())
	{
		enemy_hornet->SwitchState("idle");
	}
	
}
void EnemyHorentDashAirState::OnExit()
{
	EnemyHornet* enemy_hornet = (EnemyHornet*)CharacterManager::Instance()->GetEnemy();
	enemy_hornet->SetGravityEnabled(true);
	enemy_hornet->SetDashingInAir(false);
}

EnemyHorentDashOnFloorState::EnemyHorentDashOnFloorState(EnemyHornet* hornet) : EnemyHorentStateNode(hornet)
{
	timer.SetOneShot(true);
	timer.SetWaitTime(0.5f);
	timer.SetOnTimeout([&]()
		{
			this->hornet->SetDashingOnFloor(false);
		});
}
EnemyHorentDashOnFloorState::~EnemyHorentDashOnFloorState() = default;
void EnemyHorentDashOnFloorState::OnEnter()
{
	hornet->SetAnimation("dash_on_floor");
	hornet->SetDashingOnFloor(true);
	hornet->SetVelocity({ hornet->GetIsFacingLeft() ? -DASH_SPEED : DASH_SPEED ,0 });
	hornet->OnDash();
	Utility::PlayAudio(_T("enemy_hornet_dash"), false);
	timer.Restart();
}
void EnemyHorentDashOnFloorState::OnUpdata(float delta)
{
	if (hornet->GetHp() <= 0)
	{
		hornet->SwitchState("dead");
	}
	else if (!hornet->GetDashingOnFloor())
	{
		if (hornet->GetFloorY())
		{
			hornet->SwitchState("idle");
		}
	}
	timer.OnUpdata(delta);
}
void EnemyHorentDashOnFloorState::OnExit()
{

}

EnemyHorentDeadState::EnemyHorentDeadState(EnemyHornet* hornet) : EnemyHorentStateNode(hornet) {}
EnemyHorentDeadState::~EnemyHorentDeadState() = default;
void EnemyHorentDeadState::OnEnter()
{
	MessageBox(GetHWnd(), _T("很好,这样能行。"), _T("挑战成功!"), MB_OK);
	SceneManager::Instance()->SetIsPass(SceneType::GameSix);
	SceneManager::Instance()->SetIsGameOver(true);
}
void EnemyHorentDeadState::OnUpdata(float delta) 
{

}
void EnemyHorentDeadState::OnExit()
{

}

EnemyHorentFallState::EnemyHorentFallState(EnemyHornet* hornet) : EnemyHorentStateNode(hornet) {}
EnemyHorentFallState::~EnemyHorentFallState() = default;
void EnemyHorentFallState::OnEnter()
{
	hornet->SetAnimation("fall");
}
void EnemyHorentFallState::OnUpdata(float delta)
{
	if (hornet->GetHp() <= 0)
	{
		hornet->SwitchState("dead");
	}
	else if (hornet->IsOnFloor())
	{
		hornet->SwitchState("idle");
	}
}
void EnemyHorentFallState::OnExit()
{

}

EnemyHorentIdleState::EnemyHorentIdleState(EnemyHornet* hornet) : EnemyHorentStateNode(hornet)
{
	timer.SetOneShot(true);
	timer.SetOnTimeout([&]()
		{
			int randNum = Utility::RandomRange(0, 100);
			if (this->hornet->GetHp() > 8)
			{
				if (randNum <= 25)
				{
					this->hornet->SwitchState("jump");
				}
				else if (randNum <= 50)
				{
					this->hornet->SwitchState("run");
				}
				else if (randNum <= 80)
				{
					this->hornet->SwitchState("squat");
				}
				else if (randNum <= 90)
				{
					this->hornet->SwitchState("throw_silk");
				}
				else
				{
					this->hornet->SwitchState("ThrowSword");
				}
			}
			else
			{
				if (randNum <= 25)
				{
					this->hornet->SwitchState("throw_barb");
				}
				else if (randNum <= 45)
				{
					this->hornet->SwitchState("jump");
				}
				else if (randNum <= 65)
				{
					this->hornet->SwitchState("throw_silk");
				}
				else if (randNum <= 80)
				{
					this->hornet->SwitchState("squat");
				}
				else if (randNum <= 90)
				{
					this->hornet->SwitchState("ThrowSword");
				}
				else
				{
					this->hornet->SwitchState("run");
				}
			}
		});
}
EnemyHorentIdleState::~EnemyHorentIdleState() = default;
void EnemyHorentIdleState::OnEnter()
{
	hornet->SetAnimation("idle");
	hornet->SetVelocity({ 0,0 });

	float waitTime = 0;
	if (hornet->GetHp() > 8)
	{
		waitTime = Utility::RandomRange(0, 2) * 0.25f; //0.0s-0.5s
	}
	else
	{
		waitTime = Utility::RandomRange(0, 1) * 0.25f; //0.0s-0.25s
	}
	timer.SetWaitTime(waitTime);
	timer.Restart();
}
void EnemyHorentIdleState::OnUpdata(float delta)
{
	if (hornet->GetHp() <= 0)
	{
		hornet->SwitchState("dead");
	}
	timer.OnUpdata(delta);
}
void EnemyHorentIdleState::OnExit()
{
	hornet->SetIsFacingLeft(hornet->GetPosition().x > CharacterManager::Instance()->GetPlayer()->GetPosition().x);
}

EnemyHorentJumpState::EnemyHorentJumpState(EnemyHornet* hornet) : EnemyHorentStateNode(hornet) {}
EnemyHorentJumpState::~EnemyHorentJumpState() = default;
void EnemyHorentJumpState::OnEnter()
{
	hornet->SetAnimation("jump");
	hornet->SetVelocity({ 0,-JUMP_SPEED });
}
void EnemyHorentJumpState::OnUpdata(float delta)
{
	if (hornet->GetHp() <= 0)
	{
		hornet->SwitchState("dead");
	}
	else if (hornet->get_velocity().y > 0)
	{
		int randNum = Utility::RandomRange(0, 100);
		if (hornet->GetHp() > 8)
		{
			if (randNum <= 50)
			{
				hornet->SwitchState("aim");
			}
			else if (randNum <= 80)
			{
				hornet->SwitchState("fall");
			}
			else
			{
				hornet->SwitchState("throw_silk");
			}
		}
		else
		{
			if (randNum <= 50)
			{
				hornet->SwitchState("throw_silk");
			}
			else if (randNum <= 80)
			{
				hornet->SwitchState("fall");
			}
			else
			{
				hornet->SwitchState("aim");
			}
		}
	}
}
void EnemyHorentJumpState::OnExit()
{

}

EnemyHorentRunState::EnemyHorentRunState(EnemyHornet* hornet) : EnemyHorentStateNode(hornet) {}
EnemyHorentRunState::~EnemyHorentRunState() = default;
void EnemyHorentRunState::OnEnter()
{
	hornet->SetAnimation("run");
	Utility::PlayAudio(_T("enemy_hornet_run"), true);
}
void EnemyHorentRunState::OnUpdata(float delta)
{
	const Vector2& hornetPosition = hornet->GetPosition();
	const Vector2& playerPosition = CharacterManager::Instance()->GetPlayer()->GetPosition();
	hornet->SetVelocity({ hornetPosition.x > playerPosition.x ? -RUN_SPEED : RUN_SPEED, 0 });
	if (hornet->GetHp() <= 0)
	{
		hornet->SwitchState("dead");
	}
	else if (abs(hornetPosition.x - playerPosition.x) <= MIN_DIS)
	{
		int randNum = Utility::RandomRange(0, 100);
		if (hornet->GetHp() > 8)
		{
			if (randNum <= 75)
			{
				hornet->SwitchState("squat");
			}
			else
			{
				hornet->SwitchState("throw_silk");
			}
		}
		else
		{
			if (randNum <= 75)
			{
				hornet->SwitchState("throw_silk");
			}
			else
			{
				hornet->SwitchState("squat");
			}
		}
	}
}
void EnemyHorentRunState::OnExit()
{
	hornet->SetVelocity({ 0,0 });
	Utility::StopAudio(_T("enemy_hornet_run"));
}

EnemyHorentSquatState::EnemyHorentSquatState(EnemyHornet* hornet) : EnemyHorentStateNode(hornet)
{
	timer.SetOneShot(true);
	timer.SetWaitTime(0.5f);
	timer.SetOnTimeout([&]()
		{
			this->hornet->SwitchState("dash_on_floor");
		});
}
EnemyHorentSquatState::~EnemyHorentSquatState() = default;
void EnemyHorentSquatState::OnEnter()
{
	hornet->SetAnimation("squat");
	hornet->SetIsFacingLeft(hornet->GetPosition().x > CharacterManager::Instance()->GetPlayer()->GetPosition().x);
	timer.Restart();
}
void EnemyHorentSquatState::OnUpdata(float delta)
{
	if (hornet->GetHp() <= 0)
	{
		hornet->SwitchState("dead");
	}
	timer.OnUpdata(delta);
}
void EnemyHorentSquatState::OnExit()
{

}

EnemyHorentThrowBarbState::EnemyHorentThrowBarbState(EnemyHornet* hornet) : EnemyHorentStateNode(hornet)
{
	timer.SetOneShot(true);
	timer.SetWaitTime(0.8f);
	timer.SetOnTimeout([&]()
		{
			this->hornet->ThrowBarbs();
			this->hornet->SwitchState("idle");
		});
}
EnemyHorentThrowBarbState::~EnemyHorentThrowBarbState() = default;
void EnemyHorentThrowBarbState::OnEnter()
{
	hornet->SetAnimation("throw_barb");
	timer.Restart();
	Utility::PlayAudio(_T("enemy_hornet_throw_barbs"), false);
}
void EnemyHorentThrowBarbState::OnUpdata(float delta)
{
	if (hornet->GetHp() <= 0)
	{
		hornet->SwitchState("dead");
	}
	timer.OnUpdata(delta);
}
void EnemyHorentThrowBarbState::OnExit()
{

}

EnemyHorentThrowSilkState::EnemyHorentThrowSilkState(EnemyHornet* hornet) : EnemyHorentStateNode(hornet)
{
	timer.SetOneShot(true);
	timer.SetWaitTime(0.9f);
	timer.SetOnTimeout([&]()
		{
			this->hornet->SetThrowingSilk(false);
			this->hornet->SetGravityEnabled(true);
			if (!this->hornet->IsOnFloor() && this->hornet->GetHp() > 5 && Utility::RandomRange(0, 100) <= 25)
			{
				this->hornet->SwitchState("aim");
			}
			else if (this->hornet->IsOnFloor() && this->hornet->GetHp() > 5 && Utility::RandomRange(0, 100) <= 25)
			{
				this->hornet->SwitchState("squat");
			}
			else if (!this->hornet->IsOnFloor())
			{
				this->hornet->SwitchState("fall");
			}
			else
			{
				this->hornet->SwitchState("idle");
			}
		});
}
EnemyHorentThrowSilkState::~EnemyHorentThrowSilkState() = default;
void EnemyHorentThrowSilkState::OnEnter()
{
	hornet->SetAnimation("throw_silk");
	hornet->GetSilkCollionBox()->SetEnabled(true);
	hornet->SetThrowingSilk(true);
	hornet->SetGravityEnabled(false);
	hornet->SetVelocity({ 0,0 });
	hornet->OnThrowSilk();
	timer.Restart();
	Utility::PlayAudio(_T("enemy_hornet_throw_silk"), false);
}
void EnemyHorentThrowSilkState::OnUpdata(float delta)
{
	if (hornet->GetHp() <= 0)
	{
		hornet->SwitchState("dead");
	}
	timer.OnUpdata(delta);
}
void EnemyHorentThrowSilkState::OnExit()
{
	hornet->GetSilkCollionBox()->SetEnabled(false);
}

EnemyHorentThrowSwordState::EnemyHorentThrowSwordState(EnemyHornet* hornet) : EnemyHorentStateNode(hornet)
{
	timerThrow.SetOneShot(true);
	timerThrow.SetWaitTime(0.65f);
	timerThrow.SetOnTimeout([&]()
		{
			this->hornet->ThrowSword();
			Utility::PlayAudio(_T("enemy_throw_sword"), false);
		});

	timerSwitch.SetOneShot(true);
	timerSwitch.SetWaitTime(1.0f);
	timerSwitch.SetOnTimeout([&]()
		{
			int randNum = Utility::RandomRange(0, 100);
			if (this->hornet->GetHp() > 8)
			{
				if (randNum <= 50)
				{
					this->hornet->SwitchState("squat");
				}
				else if (randNum <= 80)
				{
					this->hornet->SwitchState("jump");
				}
				else
				{
					this->hornet->SwitchState("idle");
				}
			}
			else
			{
				if (randNum <= 50)
				{
					this->hornet->SwitchState("jump");
				}
				else if (randNum <= 80)
				{
					this->hornet->SwitchState("throw_silk");
				}
				else
				{
					this->hornet->SwitchState("idle");
				}
			}
		});
}
EnemyHorentThrowSwordState::~EnemyHorentThrowSwordState() = default;
void EnemyHorentThrowSwordState::OnEnter()
{
	hornet->SetAnimation("ThrowSword");
	timerThrow.Restart();
	timerSwitch.Restart();
}
void EnemyHorentThrowSwordState::OnUpdata(float delta)
{
	if (hornet->GetHp() <= 0)
	{
		hornet->SwitchState("dead");
	}
	timerThrow.OnUpdata(delta);
	timerSwitch.OnUpdata(delta);
}
void EnemyHorentThrowSwordState::OnExit()
{

}