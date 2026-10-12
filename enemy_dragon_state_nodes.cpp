#include"enemy_dragon_state_nodes.h"
#include"character_manager.h"
#include"enemy_dragon.h"
#include"scene_manager.h"
#include<math.h>

EnemyDragonSatNode::EnemyDragonSatNode(Dragon* dragon) :dragon(dragon){}

EnemyDragonAimSate::EnemyDragonAimSate(Dragon* dragon): EnemyDragonSatNode(dragon)
{
	timer.SetOneShot(true);
	timer.SetWaitTime(0.5f);
	timer.SetOnTimeout([&]()
		{
			this->dragon->SwitchState("dash");
		});
}
EnemyDragonAimSate::~EnemyDragonAimSate() = default;
void EnemyDragonAimSate::OnEnter()
{
	dragon->SetAnimation("aim");
	dragon->SetGravityEnabled(false);
	dragon->SetVelocity({ 0,0 });
	timer.Restart();
}
void EnemyDragonAimSate::OnUpdata(float delta)
{
	timer.OnUpdata(delta);
	if (dragon->GetHp() <= 0)
	{
		dragon->SwitchState("dead");
	}
}
void EnemyDragonAimSate::OnExit()
{

}

EnemyDragonAimInAirSate::EnemyDragonAimInAirSate(Dragon* dragon) : EnemyDragonSatNode(dragon)
{
	timer.SetOneShot(true);
	timer.SetWaitTime(0.25f);
	timer.SetOnTimeout([&]()
		{
			this->dragon->SwitchState("dash");
		});
}
EnemyDragonAimInAirSate::~EnemyDragonAimInAirSate() = default;
void EnemyDragonAimInAirSate::OnEnter()
{
	dragon->SetAnimation("aim_in_air");
	dragon->SetGravityEnabled(false);
	dragon->SetVelocity({ 0,0 });
	timer.Restart();
}
void EnemyDragonAimInAirSate::OnUpdata(float delta)
{
	timer.OnUpdata(delta);
	if (dragon->GetHp() <= 0)
	{
		dragon->SwitchState("dead");
	}
}
void EnemyDragonAimInAirSate::OnExit()
{

}

EnemyDragonAttackState::EnemyDragonAttackState(Dragon* dragon) : EnemyDragonSatNode(dragon)
{
	timer.SetOneShot(true);
	timer.SetWaitTime(0.3f);
	timer.SetOnTimeout([&]()
		{
			this->dragon->SetIsAttacking(false);
			this->dragon->GetSlashCollisionBox()->SetEnabled(false);
		});
}
EnemyDragonAttackState::~EnemyDragonAttackState() = default;
void EnemyDragonAttackState::OnEnter()
{
	dragon->SetAnimation("attack"); 
	dragon->UpdataSlashBoxPosition();
	dragon->GetSlashCollisionBox()->SetEnabled(true);
	dragon->SetIsAttacking(true);
	dragon->UpdataAttackDir();
	dragon->OnAttack();
	dragon->SetVelocity({ 0,0 });
	dragon->SetGravityEnabled(false);
	timer.Restart();
}
void EnemyDragonAttackState::OnUpdata(float delta)
{
	timer.OnUpdata(delta);
	dragon->UpdataSlashBoxPosition();
	if (dragon->GetHp() <= 0)
	{
		dragon->SwitchState("dead");
	}
	else if (!dragon->GetIsAttacking())
	{
		if (dragon->IsOnFloor())
		{
			int rand_num = Utility::RandomRange(1, 3);
			switch (rand_num)
			{
				case 1:
					dragon->SwitchState("idle");
					break;
				case 2:
					dragon->SwitchState("run");
					break;
				case 3:
					dragon->SwitchState("shoot");
			}
		}
		else
		{
			dragon->SwitchState("fall");
		}
	}
}
void EnemyDragonAttackState::OnExit()
{
	dragon->SetGravityEnabled(true);
	dragon->SetIsAttacking(false);
	dragon->GetSlashCollisionBox()->SetEnabled(false);
}

EnemyDragonDashState::EnemyDragonDashState(Dragon* dragon) : EnemyDragonSatNode(dragon)
{
	timer.SetOneShot(true);
	timer.SetWaitTime(0.15f);
	timer.SetOnTimeout([&]()
		{
			this->dragon->SetIsDashing(false);
			this->dragon->GetDashCollisionBox()->SetEnabled(false);
		});
}
EnemyDragonDashState::~EnemyDragonDashState() = default;
void EnemyDragonDashState::OnEnter()
{
	dragon->SetAnimation("dash");
	dragon->SetVelocity({ 0,0 });
	dragon->UpdataDashBoxPosition();
	dragon->GetDashCollisionBox()->SetEnabled(true);
	dragon->SetIsDashing(true);
	dragon->OnDash();
	timer.Restart();
}
void EnemyDragonDashState::OnUpdata(float delta)
{
	timer.OnUpdata(delta);
	dragon->UpdataDashBoxPosition();
	if (dragon->GetHp() <= 0)
	{
		dragon->SwitchState("dead");
	}
	else if (!dragon->GetIsDashing())
	{
		if (dragon->IsOnFloor())
		{
			if (dragon->GetHp() <= 10)
			{
				int rand_num = Utility::RandomRange(0, 100);
				if (rand_num <= 25)
				{
					dragon->SwitchState("idle");
				}
				else if (rand_num <= 50)
				{
					dragon->SwitchState("run");
				}
				else if (rand_num <= 75)
				{
					dragon->SwitchState("fire");
				}
				else
				{
					dragon->SwitchState("shoot");
				}
			}
			else
			{
				dragon->SwitchState("idle");
			}
		}
		else
		{
			dragon->SwitchState("fall");
		}
	}
}
void EnemyDragonDashState::OnExit()
{
	dragon->GetDashCollisionBox()->SetEnabled(false);
	dragon->SetIsFacingLeft(dragon->GetPosition().x > CharacterManager::Instance()->GetPlayer()->GetPosition().x);
	dragon->SetGravityEnabled(true);
}

EnemyDragonDeadState::EnemyDragonDeadState(Dragon* dragon) : EnemyDragonSatNode(dragon)
{
	timer.SetOneShot(true);
	timer.SetWaitTime(2.0f);
	timer.SetOnTimeout([&]()
		{
			MessageBox(GetHWnd(), _T("很好,这样能行。"), _T("挑战成功!"), MB_OK);
			SceneManager::Instance()->SetIsPass(SceneType::GameEight);
			SceneManager::Instance()->SetIsGameOver(true);
		});
}
EnemyDragonDeadState::~EnemyDragonDeadState() = default;
void EnemyDragonDeadState::OnEnter()
{
	dragon->SetAnimation("dead");
	//龙王阵亡音效
}
void EnemyDragonDeadState::OnUpdata(float delta)
{
	timer.OnUpdata(delta);
}
void EnemyDragonDeadState::OnExit()
{

}

EnemyDragonFallState::EnemyDragonFallState(Dragon* dragon) : EnemyDragonSatNode(dragon) {}
EnemyDragonFallState::~EnemyDragonFallState() = default;
void EnemyDragonFallState::OnEnter()
{
	dragon->SetAnimation("fall");
}
void EnemyDragonFallState::OnUpdata(float delta)
{
	if (dragon->GetHp() <= 0)
	{
		dragon->SwitchState("dead");
	}
	else if (dragon->IsOnFloor())
	{
		dragon->SwitchState("idle");
	}
}
void EnemyDragonFallState::OnExit()
{

}

EnemyDragonFireState::EnemyDragonFireState(Dragon* dragon) : EnemyDragonSatNode(dragon)
{
	timer.SetOneShot(true);
	timer.SetWaitTime(0.8f);
	timer.SetOnTimeout([&]()
		{
			this->dragon->SetIsFiring(false);
			this->dragon->OnFireUp();
		});
}
EnemyDragonFireState::~EnemyDragonFireState() = default;
void EnemyDragonFireState::OnEnter()
{
	dragon->SetAnimation("fire");
	dragon->OnFire();
	dragon->SetVelocity({ 0,0 });
	dragon->SetIsFiring(true);
	timer.Restart();
}
void EnemyDragonFireState::OnUpdata(float delta)
{
	if (dragon->GetHp() <= 0)
	{
		dragon->SwitchState("dead");
	}
	else if (!dragon->GetIsFiring())
	{
		int rand_num = Utility::RandomRange(0, 100);
		if (rand_num <= 20)
		{
			dragon->SwitchState("idle");
		}
		else if (rand_num <= 30)
		{
			dragon->SwitchState("attack");
		}
		else if (rand_num <= 50)
		{
			dragon->SwitchState("aim");
		}
		else if (rand_num <= 70)
		{
			dragon->SwitchState("jump");
		}
		else if (rand_num <= 75)
		{
			dragon->SwitchState("run");
		}
		else
		{
			dragon->SwitchState("shoot");
		}

	}
	timer.OnUpdata(delta);
}
void EnemyDragonFireState::OnExit()
{
	dragon->SetIsFiring(false);
}

EnemyDragonIdleState::EnemyDragonIdleState(Dragon* dragon) : EnemyDragonSatNode(dragon)
{
	timer.SetOneShot(true);
	timer.SetOnTimeout([&]()
		{
			int rand_num = Utility::RandomRange(0, 100);
			if (this->dragon->GetHp() >= 10)
			{
				if (rand_num <= 20)
				{
					this->dragon->SwitchState("run");
				}
				else if (rand_num <= 40)
				{
					this->dragon->SwitchState("aim");
				}
				else if (rand_num <= 60)
				{
					this->dragon->SwitchState("jump");
				}
				else if (rand_num <= 70)
				{
					this->dragon->SwitchState("attack");
				}
				else if(rand_num <= 80)
				{
					this->dragon->SwitchState("roll");
				}
				else
				{
					this->dragon->SwitchState("shoot");
				}
			}
			else
			{
				if (rand_num <= 15)
				{
					this->dragon->SwitchState("fire");
				}
				else if (rand_num <= 30)
				{
					this->dragon->SwitchState("roll");
				}
				else if (rand_num <= 45)
				{
					this->dragon->SwitchState("jump");
				}
				else if (rand_num <= 65)
				{
					this->dragon->SwitchState("attack");
				}
				else if (rand_num <= 75)
				{
					this->dragon->SwitchState("aim");
				}
				else if (rand_num <= 85)
				{
					this->dragon->SwitchState("run");
				}
				else
				{
					this->dragon->SwitchState("shoot");
				}
			}
		});
}
EnemyDragonIdleState::~EnemyDragonIdleState() = default;
void EnemyDragonIdleState::OnEnter()
{
	dragon->SetAnimation("idle");
	dragon->SetVelocity({ 0,0 });
	float waitTime = 0;
	if (dragon->GetHp() <= 10)
	{
		waitTime = Utility::RandomRange(0, 3) * 0.25f; //0.0s-0.75s
	}
	else
	{
		waitTime = Utility::RandomRange(0, 2) * 0.25f; //0.0s-0.5s
	}
	timer.SetWaitTime(waitTime);
	timer.Restart();
}
void EnemyDragonIdleState::OnUpdata(float delta)
{
	if (dragon->GetHp() <= 0)
	{
		dragon->SwitchState("dead");
	}
	timer.OnUpdata(delta);
}
void EnemyDragonIdleState::OnExit()
{
	dragon->SetIsFacingLeft(dragon->GetPosition().x > CharacterManager::Instance()->GetPlayer()->GetPosition().x);
}

EnemyDragonJumpState::EnemyDragonJumpState(Dragon* dragon) : EnemyDragonSatNode(dragon) {}
EnemyDragonJumpState::~EnemyDragonJumpState() = default;
void EnemyDragonJumpState::OnEnter()
{
	dragon->SetAnimation("jump");
	dragon->OnJump();
}
void EnemyDragonJumpState::OnUpdata(float delta)
{
	if (dragon->GetHp() <= 0)
	{
		dragon->SwitchState("dead");
	}
	else if (dragon->get_velocity().y > 0)
	{
		int rand_num = Utility::RandomRange(0, 100);
		if (rand_num <= 30)
		{
			dragon->SwitchState("fall");
		}
		else if (rand_num <= 60)
		{
			dragon->SwitchState("attack");
		}
		else
		{
			dragon->SwitchState("aim_in_air");
		}
	}
}
void EnemyDragonJumpState::OnExit()
{

}

EnemyDragonRollState::EnemyDragonRollState(Dragon* dragon) : EnemyDragonSatNode(dragon)
{
	timer.SetOneShot(true);
	timer.SetWaitTime(0.35f);
	timer.SetOnTimeout([&]()
		{
			this->dragon->SetIsRolling(false);
			this->dragon->GetHurtCollisionBox()->SetEnabled(true);
			this->dragon->GetHitCollisionBox()->SetEnabled(true);
		});
}
EnemyDragonRollState::~EnemyDragonRollState() = default;
void EnemyDragonRollState::OnEnter()
{
	dragon->SetAnimation("roll");
	dragon->GetHitCollisionBox()->SetEnabled(false);
	dragon->GetHurtCollisionBox()->SetEnabled(false);
	dragon->SetIsRolling(true);
	dragon->OnRolling();
	timer.Restart();
}
void EnemyDragonRollState::OnUpdata(float delta)
{
	if (dragon->GetHp() <= 0)
	{
		dragon->SwitchState("dead");
	}
	else if (!dragon->GetIsRolling())
	{
		int rand_num = Utility::RandomRange(0, 100);
		if (dragon->GetHp() <= 10)
		{
			if (rand_num < 25)
			{
				dragon->SwitchState("fire");
			}
			else if (rand_num < 45)
			{
				dragon->SwitchState("roll");
			}
			else if (rand_num < 55)
			{
				dragon->SwitchState("idle");
			}
			else if (rand_num < 65)
			{
				dragon->SwitchState("attack");
			}
			else if(rand_num < 75)
			{
				dragon->SwitchState("jump");
			}
			else if (rand_num < 90)
			{
				dragon->SwitchState("aim");
			}
			else
			{
				dragon->SwitchState("run");
			}
		}
		else
		{
			if (rand_num < 25)
			{
				dragon->SwitchState("run");
			}
			else if (rand_num < 55)
			{
				dragon->SwitchState("idle");
			}
			else if (rand_num < 65)
			{
				dragon->SwitchState("aim");
			}
			else if (rand_num < 75)
			{
				dragon->SwitchState("jump");
			}
			else if (rand_num < 90)
			{
				dragon->SwitchState("roll");
			}
			else
			{
				dragon->SwitchState("attack");
			}
		}
	}
	timer.OnUpdata(delta);
}
void EnemyDragonRollState::OnExit()
{
	dragon->SetVelocity({ 0,0 });
	dragon->SetIsRolling(false);
	dragon->GetHurtCollisionBox()->SetEnabled(true);
	dragon->GetHitCollisionBox()->SetEnabled(true);
}

EnmeyDragonRunState::EnmeyDragonRunState(Dragon* dragon) : EnemyDragonSatNode(dragon) {}
EnmeyDragonRunState::~EnmeyDragonRunState() = default;
void EnmeyDragonRunState::OnEnter()
{
	dragon->SetAnimation("run");
	dragon->SetIsFacingLeft(dragon->GetPosition().x > CharacterManager::Instance()->GetPlayer()->GetPosition().x);
	dragon->OnRun();
}
void EnmeyDragonRunState::OnUpdata(float delta)
{
	const Vector2& dragonPosition = dragon->GetPosition();
	const Vector2& playerPosition = CharacterManager::Instance()->GetPlayer()->GetPosition();
	if (dragon->GetHp() <= 0)
	{
		dragon->SwitchState("dead");
	}
	else if (abs(dragonPosition.x - playerPosition.x) < MIN_DIS)
	{
		int rand_num = Utility::RandomRange(0, 100);
		if (dragon->GetHp() <= 10)
		{
			if (rand_num <= 40)
			{
				dragon->SwitchState("attack");
			}
			else if (rand_num <= 80)
			{
				dragon->SwitchState("aim");
			}
			else
			{
				dragon->SwitchState("roll");
			}
		}
		else
		{
			if (rand_num <= 40)
			{
				dragon->SwitchState("attack");
			}
			else if (rand_num <= 70)
			{
				dragon->SwitchState("aim");
			}
			else
			{
				dragon->SwitchState("roll");
			}
		}
	}
}
void EnmeyDragonRunState::OnExit()
{
	//停止播放,奔跑音效
}

EnemyDragonShootFireBullet::EnemyDragonShootFireBullet(Dragon* dragon) : EnemyDragonSatNode(dragon)
{
	timerShoot.SetOneShot(true);
	timerShoot.SetWaitTime(0.65f);
	timerShoot.SetOnTimeout([&]()
		{
			this->dragon->SetAnimation("attack");
			this->dragon->SetIsAttacking(true);
			this->dragon->SetIsAiming(false);
			this->dragon->UpdataAttackDir();
			this->dragon->OnAttack();
			this->dragon->ShootFire();
			timerSwitch.Restart();
			timerSwitch.Resume();
		});

	timerSwitch.SetOneShot(true);
	timerSwitch.SetWaitTime(0.3f);
	timerSwitch.SetOnTimeout([&]()
		{
			this->dragon->SetIsAttacking(false);
		});
}
EnemyDragonShootFireBullet::~EnemyDragonShootFireBullet() = default;
void EnemyDragonShootFireBullet::OnEnter()
{
	dragon->SetAnimation("aim");
	dragon->SetIsAiming(true);
	timerShoot.Restart();
	timerSwitch.Pause();
}
void EnemyDragonShootFireBullet::OnUpdata(float delta)
{
	timerShoot.OnUpdata(delta);
	timerSwitch.OnUpdata(delta);
	if (dragon->GetHp() <= 0)
	{
		dragon->SwitchState("dead");
	}
	else if ((!dragon->GetIsAiming()) && (!dragon->GetIsAttacking()))
	{
		int randNum = Utility::RandomRange(0, 100);
		if (dragon->GetHp() >= 10)
		{
			if (randNum < 20)
			{
				dragon->SwitchState("jump");
			}
			else if (randNum < 50)
			{
				dragon->SwitchState("shoot");
			}
			else if (randNum < 65)
			{
				dragon->SwitchState("roll");
			}
			else if (randNum < 85)
			{
				dragon->SwitchState("run");
			}
			else
			{
				dragon->SwitchState("attack");
			}
		}
		else
		{
			if (randNum < 25)
			{
				dragon->SwitchState("jump");
			}
			else if (randNum < 50)
			{
				dragon->SwitchState("shoot");
			}
			else if (randNum < 65)
			{
				dragon->SwitchState("roll");
			}
			else if (randNum < 75)
			{
				dragon->SwitchState("run");
			}
			else if (randNum < 85)
			{
				dragon->SwitchState("attack");
			}
			else
			{
				dragon->SwitchState("fire");
			}
		}
	}
}
void EnemyDragonShootFireBullet::OnExit()
{
	dragon->SetIsAttacking(false);
	dragon->SetIsAiming(false);
}