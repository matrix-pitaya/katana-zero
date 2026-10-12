#include"barb.h"
#include"util.h"
#include"resources_manager.h"
#include"collision_manager.h"
#include"character_manager.h"
#include"camera_manager.h"
Barb::Barb()
{
	diffPeriod = Utility::RandomRange(0, 6);

	animation_loose.set_interval(0.15f);
	animation_loose.set_loop(true);
	animation_loose.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_loose.add_frame(ResourcesManager::Instance()->FindAtlas("barb_loose"));

	breakAnimation.set_interval(0.1f);
	breakAnimation.set_anchor_mode(Animation::AnchorMode::Centered);
	breakAnimation.set_loop(false);
	breakAnimation.add_frame(ResourcesManager::Instance()->FindAtlas("barb_break"));
	breakAnimation.set_on_finished([&]() {isValid = false; });

	collisionBox = CollisionManager::Instance()->CreateCollisionBox();
	collisionBox->SetDstLayer(CollisionLayer::Player);
	collisionBox->SetSrcLayer(CollisionLayer::Enemy);
	collisionBox->SetSize({ 20,20 });
	collisionBox->SetOnCollide([&]() {OnBreak(); CameraManager::Instance()->GetCamera()->Shake(5.0f, 0.5f);  });

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
				stage = Stage::Dash;
				Vector2& pos_player = CharacterManager::Instance()->GetPlayer()->GetPosition();
				velocity = (pos_player - currentPosition).normalize() * DASH_SPEED;
			}
		});

}
Barb::~Barb()
{
	CollisionManager::Instance()->DestroyCollisionBox(collisionBox);
}

void Barb::OnUpdata(float delta)
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
		break;
	case Stage::Aim:
		currentPosition.x = basePosition.x + Utility::RandomRange(-10, 10);
		break;
	case Stage::Dash:
		currentPosition.x += velocity.x * delta;
		currentPosition.y += velocity.y * delta;
		if (currentPosition.y >= CharacterManager::Instance()->GetPlayer()->GetFloorY())
		{
			OnBreak();
		}
		break;
	}

	if (currentPosition.x <= 0 || currentPosition.x >= getwidth() || currentPosition.y <= 0 || currentPosition.y >= getheight())
	{
		isValid = false;
	}

	collisionBox->SetPosition(currentPosition);
	
	currentAnimation = (stage == Stage::Break ? &breakAnimation : &animation_loose);
	currentAnimation->SetPosition(currentPosition);
	currentAnimation->OnUpdata(delta);
}
void Barb::OnRender()
{
	currentAnimation->OnRender();
}

void Barb::SetPosition(const Vector2& position)
{
	currentPosition = position;
	basePosition = position;
}
bool Barb::CheckValid()
{
	return isValid;
}
void Barb::OnBreak()
{
	stage = Stage::Break;
	collisionBox->SetEnabled(false);
	Utility::PlayAudio(_T("barb_break"), false);
}