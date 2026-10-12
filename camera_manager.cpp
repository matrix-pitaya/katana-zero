#include"camera_manager.h"
CameraManager* CameraManager::instance = nullptr;

CameraManager* CameraManager::Instance()
{
	if (!instance)
	{
		instance = new CameraManager();
	}

	return instance;
}
CameraManager::CameraManager()
{
	camera = new Camera;
}
CameraManager::~CameraManager()
{
	delete camera;
}
Camera* CameraManager::GetCamera()
{
	return camera;
}