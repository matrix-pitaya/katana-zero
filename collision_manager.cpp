#include"collision_manager.h"
#include"camera_manager.h"
#include<graphics.h>
CollisionManager* CollisionManager::instance = nullptr;

CollisionManager* CollisionManager::Instance()
{
	if (!instance)
	{
		instance = new CollisionManager();
	}
	return instance;
}

CollisionBox* CollisionManager::CreateCollisionBox()
{
	CollisionBox* collisionBox = new CollisionBox();
	collisionBoxList.push_back(collisionBox);
	return collisionBox;
}

void CollisionManager::DestroyCollisionBox(CollisionBox* collisionBox)
{
	collisionBoxList.erase(remove(collisionBoxList.begin(), collisionBoxList.end(), collisionBox), collisionBoxList.end());
	delete collisionBox;
	collisionBox = nullptr;
}

void CollisionManager::ProcessCollide()
{
	for (CollisionBox*& srcCollisionBox : collisionBoxList)
	{
		if (!srcCollisionBox->enabled || srcCollisionBox->dstLayer == CollisionLayer::None)
		{
			continue;
		}
		for (CollisionBox*& dstCollisionBox : collisionBoxList)
		{
			if (!dstCollisionBox->enabled || srcCollisionBox == dstCollisionBox || srcCollisionBox->dstLayer != dstCollisionBox->srcLayer)
			{
				continue;
			}
			bool isCollideX = ( max(srcCollisionBox->position.x + srcCollisionBox->size.x / 2, dstCollisionBox->position.x + dstCollisionBox->size.x / 2)
								- min(srcCollisionBox->position.x - srcCollisionBox->size.x / 2, dstCollisionBox->position.x - dstCollisionBox->size.x / 2)
								<= srcCollisionBox->size.x + dstCollisionBox->size.x);
			bool isCollideY = (max(srcCollisionBox->position.y + srcCollisionBox->size.y / 2, dstCollisionBox->position.y + dstCollisionBox->size.y / 2)
								- min(srcCollisionBox->position.y - srcCollisionBox->size.y / 2, dstCollisionBox->position.y - dstCollisionBox->size.y / 2)
								<= srcCollisionBox->size.y + dstCollisionBox->size.y);
			if (isCollideX && isCollideY && dstCollisionBox->onCollide)
			{
				dstCollisionBox->onCollide();
			}
		}
	}
}

void CollisionManager::OnRender()
{
	if (isDebug)
	{
		for (CollisionBox*& collisionBox : collisionBoxList)
		{
			setlinecolor(collisionBox->enabled ? RGB(255, 195, 195) : RGB(115, 115, 175));
			rectangle((int)(collisionBox->position.x - collisionBox->size.x / 2 - CameraManager::Instance()->GetCamera()->GetPosition().x),
				(int)(collisionBox->position.y - collisionBox->size.y / 2 - CameraManager::Instance()->GetCamera()->GetPosition().y),
				(int)(collisionBox->position.x + collisionBox->size.x / 2 - CameraManager::Instance()->GetCamera()->GetPosition().x),
				(int)(collisionBox->position.y + collisionBox->size.y / 2 - CameraManager::Instance()->GetCamera()->GetPosition().y));
		}
	}
}

void CollisionManager::OnInput(const ExMessage& msg)
{
	switch (msg.message)
	{
	
	case WM_KEYUP:
		switch (msg.vkcode)
		{
			case 'Q':
			case 'q':
				isDebug = !isDebug;
				break;
		}
		break;
	}
}