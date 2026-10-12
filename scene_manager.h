#pragma once
#include"scene.h"
#include<graphics.h>
#include<unordered_map>
class SceneManager
{
public:
	static SceneManager* Instance();

	void SwitchTo(SceneType type);
	void OnEnter();
	void OnUpdata(float delta);
	void OnRender();
	void OnInput(const ExMessage& msg);
	void OnExit();

	SceneType GetSceneType();
	void SetSceneType(SceneType type);

	void SetIsGameOver(bool flag);
	bool GetIsGameOver();

	void SetIsPass(SceneType type);
	bool GetIsPass(SceneType type);
private:
	SceneManager();
	~SceneManager();

private:
	static SceneManager* instance;

	SceneType currentSceneType = SceneType::Menu;

	Scene* currentScene = nullptr;

	std::unordered_map<SceneType, Scene*> scenes;
	std::unordered_map<SceneType, bool> sceneIsPass;

	bool isGameOver = false;
	bool isNeedInit = true;
};