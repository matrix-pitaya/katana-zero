#pragma once
#include"camera.h"
class CameraManager
{
public:
	static CameraManager* Instance();
	Camera* GetCamera();
private:
	static CameraManager* instance;

	Camera* camera = nullptr;

	CameraManager();
	~CameraManager();
};