#include"bullet_time_manager.h"
#include<graphics.h>
#include"util.h"
BulletTimeManager* BulletTimeManager::instance = nullptr;

BulletTimeManager* BulletTimeManager::Instance()
{
	if (!instance)
	{
		instance = new BulletTimeManager();
	}
	return instance;
}

void  BulletTimeManager::PostProcess()
{
	DWORD* buffer = GetImageBuffer();
	int w = getwidth();
	int h = getheight();
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int idex = y * w + x;
			DWORD color = buffer[idex];
			BYTE r = (BYTE)(GetBValue(color) * Utility::Lerp(1.0f, DST_COLOR_FACTOR, progress));
			BYTE g = (BYTE)(GetGValue(color) * Utility::Lerp(1.0f, DST_COLOR_FACTOR, progress));
			BYTE b = (BYTE)(GetRValue(color) * Utility::Lerp(1.0f, DST_COLOR_FACTOR, progress));
			buffer[idex] = BGR(RGB(r, g, b)) | (((DWORD)(BYTE)(255)) << 24);
		}
	}
}

void  BulletTimeManager::SetStatus(Status status)
{
	this->status = status;
}

float  BulletTimeManager::OnUpdata(float delta)
{
	progress += SPEED_PROGRESS * delta * (status == Status::Entering ? 1 : -1);

	if (progress <= 0)
	{
		progress = 0.0f;
	}
	if (progress >= 1.0f)
	{
		progress = 1.0f;
	}
	
	return delta * Utility::Lerp(1.0f, DST_DELTA_FACTOR, progress);
}