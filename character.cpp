#include"character.h"
#include"collision_box.h"
#include"collision_manager.h"
#include"camera_manager.h"
#include<iostream>
Character::Character()
{
	hitBox = CollisionManager::Instance()->CreateCollisionBox();
	hurtBox = CollisionManager::Instance()->CreateCollisionBox();

	invulnerableBlinkTimer.SetOneShot(false);
	invulnerableBlinkTimer.SetWaitTime(0.075f);
	invulnerableBlinkTimer.SetOnTimeout([&]() {isBlinkInvisable = !isBlinkInvisable; });

	invulnerableStatusTimer.SetOneShot(true);
	invulnerableStatusTimer.SetWaitTime(1.0f);
	invulnerableStatusTimer.SetOnTimeout([&]() {isInvulnerable = false; });
}
Character::~Character()
{
	CollisionManager::Instance()->DestroyCollisionBox(hitBox);
	CollisionManager::Instance()->DestroyCollisionBox(hurtBox);
}
void Character::OnInput(const ExMessage& msg)
{

}
void Character::OnUpdata(float delta)
{
	stateMachine.OnUpdata(delta);

	if (hp <= 0)
	{
		velocity.x = 0;
	}

	if (enableGravity)
	{
		velocity.y += GRAVITY * delta;
	}

	position.x += velocity.x * delta;
	position.y += velocity.y * delta;

	if (position.y >= FLOOR_Y)
	{
		position.y = FLOOR_Y;
		velocity.y = 0;
	}

	if (position.x <= 0)
	{
		position.x = 0;
	}
	if (position.x >= getwidth())
	{
		position.x = (float)getwidth();
	}

	hurtBox->SetPosition(GetLogicCenter());
	
	if (isInvulnerable)
	{
		invulnerableBlinkTimer.OnUpdata(delta);
		invulnerableStatusTimer.OnUpdata(delta);
	}

	if (!currentAnimation)
	{
		return;
	}
	(isFacingLeft ? currentAnimation->left : currentAnimation->right).SetPosition(position);
	(isFacingLeft ? currentAnimation->left : currentAnimation->right).OnUpdata(delta);
}
void Character::OnRender()
{
	if (!currentAnimation || (isInvulnerable && isBlinkInvisable))
	{
		return;
	}
	(isFacingLeft ? currentAnimation->left : currentAnimation->right).OnRender();
}
void Character::OnHurt()
{
	CameraManager::Instance()->GetCamera()->Shake(10.0f, 0.5f);
}
void Character::SwitchState(const string& id)
{
	stateMachine.SwitchTo(id);
}
void Character::SetAnimation(const string& id)
{
	currentAnimation = &animationPool[id];
	currentAnimation->left.Reset();
	currentAnimation->right.Reset();
}
void Character::DecreaseHp()
{
	if (isInvulnerable)
	{
		return;
	}
	hp -= 1;
	if (hp > 0)
	{
		MakeInvulnerable();
	}
	OnHurt();
}
int Character::GetHp()
{
	return hp;
}
void Character::SetPosition(const Vector2& position)
{
	this->position.x = position.x;
	this->position.y = position.y;
}
Vector2& Character::GetPosition()
{
	return position;
}
void Character::SetVelocity(const Vector2& velocity)
{
	this->velocity = velocity;
}
Vector2& Character::get_velocity()
{
	return velocity;
}
Vector2 Character::GetLogicCenter()
{
	return Vector2(position.x, position.y - logicHeight / 2);
}
void Character::SetGravityEnabled(bool flag)
{
	enableGravity = flag;
}
CollisionBox* Character::GetHitCollisionBox()
{
	return hitBox;
}
CollisionBox* Character::GetHurtCollisionBox()
{
	return hurtBox;
}
bool Character::IsOnFloor()
{
	return position.y >= FLOOR_Y;
}
float Character::GetFloorY()
{
	return FLOOR_Y;
}
void Character::MakeInvulnerable()
{
	isInvulnerable = true;
	invulnerableStatusTimer.Restart();
}