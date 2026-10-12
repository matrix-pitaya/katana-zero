#include"fire_bullet.h"
#include"resources_manager.h"
#include"collision_manager.h"
FireBullet::FireBullet(const Vector2& position, bool move_left)
{
	animation.set_loop(true);
	animation.set_interval(0.1f);
	animation.set_anchor_mode(Animation::AnchorMode::Centered);
	animation.add_frame(ResourcesManager::Instance()->FindAtlas(move_left ? "fire_bullet_left" : "fire_bullet_right"));

	animationExplode.set_loop(false);
	animationExplode.set_interval(0.05f);
	animationExplode.set_anchor_mode(Animation::AnchorMode::Centered);
	animationExplode.add_frame(ResourcesManager::Instance()->FindAtlas("fire_bullet_attacked"));
	animationExplode.set_on_finished([&]() {isValid = false; });
	
	this->position = position;
	this->velocity.x = move_left ? -MOVE_SPEED : MOVE_SPEED;

	collisionBox = CollisionManager::Instance()->CreateCollisionBox();
	collisionBox->SetEnabled(true);
	collisionBox->SetDstLayer(CollisionLayer::Player);
	collisionBox->SetSrcLayer(CollisionLayer::Enemy);
	collisionBox->SetSize({ 80,10 });
	collisionBox->SetOnCollide([&]()
		{
			stage = Stage::Explode;
			collisionBox->SetEnabled(false);
			CameraManager::Instance()->GetCamera()->Shake(5.0f, 0.5f);
		});
}
FireBullet::~FireBullet()
{
	CollisionManager::Instance()->DestroyCollisionBox(collisionBox);
}
void FireBullet::OnUpdata(float delta)
{
	if (stage == Stage::Idle)
	{
		position.x += velocity.x * delta;
		collisionBox->SetPosition(position);
	}
	
	currentAnimation = (stage == Stage::Idle ? &animation : &animationExplode);
	currentAnimation->SetPosition(position);
	currentAnimation->OnUpdata(delta);

	if (position.x >= getwidth() || position.x <= 0 || position.y <= 0 || position.y >= getheight())
	{
		isValid = false;
	}
}
void FireBullet::OnRender()
{
	currentAnimation->OnRender();
}
bool FireBullet::CheckValid()
{
	return isValid;
}