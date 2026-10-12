#include"collision_box.h"
void CollisionBox::SetEnabled(bool flag)
{
	enabled = flag;
}
void CollisionBox::SetSrcLayer(CollisionLayer layer)
{
	srcLayer = layer;
}
void CollisionBox::SetDstLayer(CollisionLayer layer)
{
	dstLayer = layer;
}
void CollisionBox::SetOnCollide(function<void()> onCollide)
{
	this->onCollide = onCollide;
}
void CollisionBox::SetPosition(const Vector2& position)
{
	this->position.x = position.x;
	this->position.y = position.y;
}
void CollisionBox::SetSize(const Vector2& size)
{
	this->size.x = size.x;
	this->size.y = size.y;
}
Vector2& CollisionBox::GetSize()
{
	return size;
}