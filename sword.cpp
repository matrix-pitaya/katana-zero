#include"sword.h"
#include"vector2.h"
#include"resources_manager.h"
#include"collision_manager.h"
Sword::Sword(const Vector2& position, bool move_left)
{
	animation.set_loop(true);
	animation.set_interval(0.1f);
	animation.set_anchor_mode(Animation::AnchorMode::Centered);
	animation.add_frame(ResourcesManager::Instance()->FindAtlas(move_left ? "sword_left" : "sword_right"));

	this->position = position;
	this->velocity.x = move_left ? -MOVE_SPEED : MOVE_SPEED;

	collisionBox = CollisionManager::Instance()->CreateCollisionBox();
	collisionBox->SetEnabled(true);
	collisionBox->SetDstLayer(CollisionLayer::Player);
	collisionBox->SetSrcLayer(CollisionLayer::None);
	collisionBox->SetSize({ 195,10 });
}
Sword::~Sword()
{
	CollisionManager::Instance()->DestroyCollisionBox(collisionBox);
}

void Sword::OnUpdata(float delta)
{
	position.x += velocity.x * delta;
	collisionBox->SetPosition(position);
	animation.SetPosition(position);
	animation.OnUpdata(delta);
	if (position.x >= getwidth() || position.x <= 0 || position.y <= 0 || position.y >= getheight())
	{
		isValid = false;
	}
}
void Sword::OnRender()
{
	animation.OnRender();
}

bool Sword::CheckValid()
{
	return isValid;
}
