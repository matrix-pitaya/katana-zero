#include"scene_manager.h"
#include"menu_scene.h"
#include"select_scene.h"
#include"game_scene_six.h"
#include"game_scene_eight.h"
SceneManager* SceneManager::instance = nullptr;

SceneManager* SceneManager::Instance()
{
	if (!instance)
	{
		instance = new SceneManager();
	}
	return instance;
}

SceneManager::SceneManager()
{
	scenes.emplace(SceneType::Menu, new MenuScene());
	scenes.emplace(SceneType::Select, new SelectScene());
	scenes.emplace(SceneType::GameOne, new GameSceneSix());
	scenes.emplace(SceneType::GameTwo, new GameSceneSix());
	scenes.emplace(SceneType::GameThree, new GameSceneSix());
	scenes.emplace(SceneType::GameFour, new GameSceneSix());
	scenes.emplace(SceneType::GameFive, new GameSceneSix());
	scenes.emplace(SceneType::GameSix, new GameSceneSix());
	scenes.emplace(SceneType::GameSeven, new GameSceneSix());
	scenes.emplace(SceneType::GameEight, new GameSceneEight());
	scenes.emplace(SceneType::GameNine, new GameSceneSix());
	scenes.emplace(SceneType::GameTen, new GameSceneSix());
	scenes.emplace(SceneType::GameEleven, new GameSceneSix());
	scenes.emplace(SceneType::GameTwelve, new GameSceneSix());

	sceneIsPass.emplace(SceneType::Menu, true);
	sceneIsPass.emplace(SceneType::Select, true);
	sceneIsPass.emplace(SceneType::GameOne, false);
	sceneIsPass.emplace(SceneType::GameTwo, false);
	sceneIsPass.emplace(SceneType::GameThree, false);
	sceneIsPass.emplace(SceneType::GameFour, false);
	sceneIsPass.emplace(SceneType::GameFive, false);
	sceneIsPass.emplace(SceneType::GameSix, false);
	sceneIsPass.emplace(SceneType::GameSeven, false);
	sceneIsPass.emplace(SceneType::GameEight, false);
	sceneIsPass.emplace(SceneType::GameNine, false);
	sceneIsPass.emplace(SceneType::GameTen, false);
	sceneIsPass.emplace(SceneType::GameEleven, false);
	sceneIsPass.emplace(SceneType::GameTwelve, false);

	currentScene = scenes[SceneType::Menu];
}
SceneManager::~SceneManager()
{
	for (auto& pair : scenes)
	{
		if (pair.second)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}
}

void SceneManager::SwitchTo(SceneType type)
{
	currentScene->OnExit();
	currentScene = scenes[type];
	currentScene->OnEnter();
}
void SceneManager::OnEnter()
{
	currentScene->OnEnter();
}
void SceneManager::OnUpdata(float delta)
{
	if (isNeedInit)
	{
		currentScene->OnEnter();
		isNeedInit = false;
	}
	currentScene->OnUpdata(delta);
}
void SceneManager::OnRender()
{
	currentScene->OnRender();
}
void SceneManager::OnInput(const ExMessage& msg)
{
	currentScene->OnInput(msg);
}
void SceneManager::OnExit()
{
	currentScene->OnExit();
}

SceneType SceneManager::GetSceneType()
{
	return currentSceneType;
}

void SceneManager::SetSceneType(SceneType type)
{
	currentSceneType = type;
}
void SceneManager::SetIsGameOver(bool flag)
{
	isGameOver = flag;
}
bool SceneManager::GetIsGameOver()
{
	return isGameOver;
}
void SceneManager::SetIsPass(SceneType type)
{
	sceneIsPass[type] = true;
}
bool SceneManager::GetIsPass(SceneType type)
{
	return sceneIsPass[type];
}