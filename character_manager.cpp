#include"character_manager.h"
#include"player.h"
#include"enemy_hornet.h"
#include"enemy_dragon.h"
#include"scene_manager.h"
CharacterManager* CharacterManager::instance = nullptr;

CharacterManager* CharacterManager::Instance()
{
	if (!instance)
	{
		instance = new CharacterManager();
	}
	return instance;
}
Character* CharacterManager::GetPlayer()
{
	return player;
}
Character* CharacterManager::GetEnemy()
{
	return enemy;
}
void CharacterManager::CreateCharacter()
{
	switch (SceneManager::Instance()->GetSceneType())
	{
	case SceneType::GameOne:
		player = new Player();
		break;
	case SceneType::GameTwo:
		player = new Player();
		break;
	case SceneType::GameThree:
		player = new Player();
		break;
	case SceneType::GameFour:
		player = new Player();
		break;
	case SceneType::GameFive:
		player = new Player();
		break;
	case SceneType::GameSix:
		player = new Player();
		enemy = new EnemyHornet();
		break;
	case SceneType::GameSeven:
		player = new Player();
		break;
	case SceneType::GameEight:
		player = new Player();
		enemy = new Dragon();
		break;
	case SceneType::GameNine:
		player = new Player();
		break;
	case SceneType::GameTen:
		player = new Player();
		break;
	case SceneType::GameEleven:
		player = new Player();
		break;
	case SceneType::GameTwelve:
		player = new Player();
		break;
	}
}
void CharacterManager::DestroyCharacter()
{
	if (player)
	{
		delete player;
		player = nullptr;
	}
	if (enemy)
	{
		delete enemy;
		enemy = nullptr;
	}
}
void CharacterManager::OnInput(const ExMessage& msg)
{
	if (player)
	{
		player->OnInput(msg);
	}
}
void CharacterManager::OnUpdata(float delta)
{
	if (player)
	{
		player->OnUpdata(delta);
	}
	if (enemy)
	{
		enemy->OnUpdata(delta);
	}
}
void CharacterManager::OnRender()
{
	if (enemy)
	{
		enemy->OnRender();
	}
	if (player)
	{
		BulletTimeManager::Instance()->PostProcess();
		player->OnRender();
	}
}