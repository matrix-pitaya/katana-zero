#include"util.h"
#include"resources_manager.h"
#include"scene_manager.h"
#include"character_manager.h"
#include"collision_manager.h"
#include"bullet_time_manager.h"
#include<graphics.h>
#include<chrono>
#include<thread>
int main()
{
	ExMessage msg;

	HWND hwnd = initgraph(1280, 720);

	try
	{
		ResourcesManager::Instance()->Load();
	}
	catch(LPCTSTR id)
	{
		TCHAR err[512];
		_stprintf_s(err, _T("无法加载:%s"), id);
		MessageBox(hwnd, err, _T("资源加载失败"), MB_OK | MB_ICONERROR);
		return -1;
	}
	
	const chrono::nanoseconds frameDuration(1000000000 / 144);
	chrono::steady_clock::time_point lastTick = chrono::steady_clock::now();

	BeginBatchDraw();

	while (true)
	{
		while (peekmessage(&msg))
		{
			//处理消息
			SceneManager::Instance()->OnInput(msg);
			CharacterManager::Instance()->OnInput(msg);
			CollisionManager::Instance()->OnInput(msg);
		}
		
		chrono::steady_clock::time_point frameStart = chrono::steady_clock::now();
		chrono::duration<float> delta = chrono::duration<float>(frameStart - lastTick);

		//处理更新
		float _delta = BulletTimeManager::Instance()->OnUpdata(delta.count());
		SceneManager::Instance()->OnUpdata(_delta);
		CharacterManager::Instance()->OnUpdata(_delta);
		CollisionManager::Instance()->ProcessCollide();
		CameraManager::Instance()->GetCamera()->OnUpdata(_delta);
	
		setbkcolor(RGB(0, 0, 0));
		cleardevice();

		//处理绘图
		SceneManager::Instance()->OnRender();
		CharacterManager::Instance()->OnRender();
		CollisionManager::Instance()->OnRender();

		FlushBatchDraw();

		lastTick = frameStart;
		chrono::nanoseconds sleepDuration = frameDuration - (chrono::steady_clock::now() - frameStart);
		if (sleepDuration > chrono::nanoseconds(0))
		{
			std::this_thread::sleep_for(sleepDuration);
		}
	}

	EndBatchDraw();

	return 0;
}