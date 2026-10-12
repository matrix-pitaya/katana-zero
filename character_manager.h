#pragma once
#include"character.h"
#include"scene_type.h"
#include"bullet_time_manager.h"
class CharacterManager
{
public:
	static CharacterManager* Instance();
	
	Character* GetPlayer();
	Character* GetEnemy();
	
	void OnInput(const ExMessage& msg);
	void OnUpdata(float delta);
	void OnRender();

	void CreateCharacter();
	void DestroyCharacter();
private:
	static CharacterManager* instance;

	Character* player = nullptr;
	Character* enemy = nullptr;
private:
	CharacterManager() = default;
	~CharacterManager() = default;
};