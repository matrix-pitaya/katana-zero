#pragma once
#include"camera_manager.h"
#include<graphics.h>
#include<random>

#pragma comment(lib,"WINMM.lib")
#pragma comment(lib,"MSIMG32.lib")

struct Rect
{
	int x, y;
	int w, h;
};

namespace Utility
{
	static random_device _rand;

	inline void PutimageEX(IMAGE* img, Rect* dstRect, Rect* srcRect = nullptr)
	{
		AlphaBlend(GetImageHDC(GetWorkingImage()), dstRect->x - CameraManager::Instance()->GetCamera()->GetPosition().x,
			dstRect->y - CameraManager::Instance()->GetCamera()->GetPosition().y, dstRect->w, dstRect->h,
			GetImageHDC(img), srcRect ? srcRect->x : 0, srcRect ? srcRect->y : 0, srcRect ? srcRect->w : img->getwidth()
			, srcRect ? srcRect->h : img->getheight(), { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
	}

	inline bool ChekImageIsValid(IMAGE* image)
	{
		return GetImageBuffer(image);
	}

	inline void LoadAudio(LPCTSTR path, LPCTSTR id)
	{
		static TCHAR cmd[512];
		_stprintf_s(cmd, _T("open %s alias %s"), path, id);
		mciSendString(cmd, NULL, 0, NULL);
	}

	inline void PlayAudio(LPCTSTR id, bool isLoop = false)
	{
		static TCHAR cmd[512];
		_stprintf_s(cmd, _T("play %s %s from 0"), id, isLoop ? _T("repeat") : _T(""));
		mciSendString(cmd, NULL, 0, NULL);
	}

	inline void StopAudio(LPCTSTR id)
	{
		static TCHAR cmd[512];
		_stprintf_s(cmd, _T("stop %s"), id);
		mciSendString(cmd, NULL, 0, NULL);
	}

	inline int RandomRange(int min_num, int max_num)
	{
		return min_num + _rand() % (max_num - min_num + 1);
	}

	inline float Lerp(float start, float end, float progress)
	{
		return (1 - progress) * start + progress * end;
	}

	inline void ShededText(int x, int y, LPCTSTR str)
	{
		settextcolor(RGB(45, 45, 45));
		outtextxy(x + 1, y + 1, str);
		settextcolor(RGB(0, 0, 0));
		outtextxy(x, y, str);
	}
}