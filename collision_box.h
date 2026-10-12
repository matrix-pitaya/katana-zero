#pragma once
#include"vector2.h"
#include"collision_layer.h"
#include<functional>
using namespace std;
class CollisionManager;
class CollisionBox
{
	friend class CollisionManager;
public:
	void SetEnabled(bool flag);
	void SetSrcLayer(CollisionLayer layer);
	void SetDstLayer(CollisionLayer layer);
	void SetOnCollide(function<void()> onCollide);
	void SetPosition(const Vector2& position);
	void SetSize(const Vector2& size);
	Vector2& GetSize();

private:
	Vector2 position;
	Vector2 size;
	bool enabled = true;
	function<void()> onCollide;
	CollisionLayer srcLayer = CollisionLayer::None;
	CollisionLayer dstLayer = CollisionLayer::None;

private:
	CollisionBox() = default;
	~CollisionBox() = default;
};