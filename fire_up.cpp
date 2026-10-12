#include"fire_up.h"
#include"character_manager.h"
#include"collision_manager.h"
#include"resources_manager.h"
FireUp::FireUp()
{
	diffPeriod = Utility::RandomRange(0, 6);

	collisionBox = CollisionManager::Instance()->CreateCollisionBox();
	collisionBox->SetEnabled(true);
	collisionBox->SetDstLayer(CollisionLayer::Player);
	collisionBox->SetSrcLayer(CollisionLayer::Enemy);
	collisionBox->SetSize({ 30,30 });
	collisionBox->SetOnCollide([&]() {OnAttacked(); CameraManager::Instance()->GetCamera()->Shake(5.0f, 0.5f); });

	idleAnimation.add_frame(ResourcesManager::Instance()->FindAtlas("OnFireUp"));
	idleAnimation.set_loop(true);
	idleAnimation.set_interval(0.15f);
	idleAnimation.set_anchor_mode(Animation::AnchorMode::BottomCentered);

	breakAnimation.add_frame(ResourcesManager::Instance()->FindAtlas("fire_up_break"));
	breakAnimation.set_loop(false);
	breakAnimation.set_interval(0.025f);
	breakAnimation.set_anchor_mode(Animation::AnchorMode::Centered);
	breakAnimation.set_on_finished([&]() {isValid = false; });

	attackedAnimation.add_frame(ResourcesManager::Instance()->FindAtlas("fire_bullet_attacked"));
	attackedAnimation.set_loop(false);
	attackedAnimation.set_interval(0.025f);
	attackedAnimation.set_anchor_mode(Animation::AnchorMode::Centered);
	attackedAnimation.set_on_finished([&]() {isValid = false; });

	idleTimer.SetOneShot(true);
	idleTimer.SetWaitTime(static_cast<float>(Utility::RandomRange(3, 10)));
	idleTimer.SetOnTimeout([&]()
		{
			if (stage == Stage::Idle)
			{
				stage = Stage::Aim;
				basePosition = currentPosition;
			}
		});

	aimTimer.SetOneShot(true);
	aimTimer.SetWaitTime(0.75f);
	aimTimer.SetOnTimeout([&]()
		{
			if (stage == Stage::Aim)
			{
				stage = Stage::Fall;
			}
		});
}
FireUp::~FireUp()
{
	CollisionManager::Instance()->DestroyCollisionBox(collisionBox);
}
void FireUp::OnUpdata(float delta)
{
	if (stage == Stage::Idle)
	{
		idleTimer.OnUpdata(delta);
	}
	if (stage == Stage::Aim)
	{
		aimTimer.OnUpdata(delta);
	}
	totalDeltaTime += delta;
	switch (stage)
	{
	case Stage::Idle:
		currentPosition.y = basePosition.y + sin(totalDeltaTime * 2 + diffPeriod) * 30;
		currentFireAnimation = &idleAnimation;
		break;
	case Stage::Aim:
		currentPosition.x = basePosition.x + Utility::RandomRange(-10, 10);
		currentFireAnimation = &idleAnimation;
		break;
	case Stage::Fall:
		velocity.y += GRAVITY * delta;
		currentPosition.y += velocity.y * delta;
		if (currentPosition.y >= (CharacterManager::Instance()->GetPlayer()->GetFloorY()) - 35)
		{
			OnBreak();
		}
		currentFireAnimation = &idleAnimation;
		break;
	case Stage::Break:
		currentFireAnimation = &breakAnimation;
		break;
	case Stage::Attacked:
		currentFireAnimation = &attackedAnimation;
		break;
	}

	if (currentPosition.x >= getwidth() || currentPosition.x <= 0 || currentPosition.y <= 0 || currentPosition.y >= getheight())
	{
		isValid = false;
	}

	collisionBox->SetPosition(currentPosition);

	currentFireAnimation->SetPosition(currentPosition);
	currentFireAnimation->OnUpdata(delta);
}
void FireUp::OnRender()
{
	currentFireAnimation->OnRender();
}
void FireUp::SetPosition(const Vector2& position)
{
	currentPosition = position;
	basePosition = position;
}
bool FireUp::CheckValid()
{
	return isValid;
}
void FireUp::OnBreak()
{
	stage = Stage::Break;
	collisionBox->SetEnabled(false);
}
void FireUp::OnAttacked()
{
	stage = Stage::Attacked;
	collisionBox->SetEnabled(false);
}
