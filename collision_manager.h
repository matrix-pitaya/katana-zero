#pragma once
#include"collision_box.h"
#include<vector>
#include<graphics.h>
using namespace std;
class CollisionManager
{
public:
	static CollisionManager* Instance();

	CollisionBox* CreateCollisionBox();
	void DestroyCollisionBox(CollisionBox* collisionBox);

	void ProcessCollide();
	void OnRender();
	void OnInput(const ExMessage& msg);

private:
	static CollisionManager* instance;

	vector<CollisionBox*> collisionBoxList;
private:
	CollisionManager() = default;
	~CollisionManager() = default;

	bool isDebug = false;
};