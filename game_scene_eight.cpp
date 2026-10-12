#include"game_scene_eight.h"
#include"resources_manager.h"
#include"util.h"
#include"character_manager.h"
#include"collision_manager.h"
#include"scene_manager.h"
#include"bullet_time_manager.h"
#include"camera_manager.h"
void GameSceneEight::OnEnter()
{
	switch (Utility::RandomRange(1, 9))
	{
	case 1:
		Utility::PlayAudio(_T("game_bgm_1"), true);
		break;
	case 2:
		Utility::PlayAudio(_T("game_bgm_2"), true);
		break;
	case 3:
		Utility::PlayAudio(_T("game_bgm_3"), true);
		break;
	case 4:
		Utility::PlayAudio(_T("game_bgm_4"), true);
		break;
	case 5:
		Utility::PlayAudio(_T("game_bgm_5"), true);
		break;
	case 6:
		Utility::PlayAudio(_T("game_bgm_6"), true);
		break;
	case 7:
		Utility::PlayAudio(_T("game_bgm_7"), true);
		break;
	case 8:
		Utility::PlayAudio(_T("game_bgm_8"), true);
		break;
	case 9:
		Utility::PlayAudio(_T("game_bgm_9"), true);
		break;
	}
	CharacterManager::Instance()->CreateCharacter();
	CameraManager::Instance()->GetCamera()->Reset();
}
void GameSceneEight::OnUpdata(float delta)
{
	if (SceneManager::Instance()->GetIsGameOver())
	{
		SceneManager::Instance()->SwitchTo(SceneType::Menu);
	}
}
void GameSceneEight::OnRender()
{
	DrawBackground();
	DrawRemainHp();
}
void GameSceneEight::OnInput(const ExMessage& msg)
{
	switch (msg.message)
	{

	case WM_KEYUP:
		switch (msg.vkcode)
		{
		case VK_RETURN:
			SceneManager::Instance()->SwitchTo(SceneType::Menu);
			break;
		}
		break;
	}
}
void GameSceneEight::OnExit()
{
	Utility::StopAudio(_T("game_bgm_1"));
	Utility::StopAudio(_T("game_bgm_2"));
	Utility::StopAudio(_T("game_bgm_3"));
	Utility::StopAudio(_T("game_bgm_4"));
	Utility::StopAudio(_T("game_bgm_5"));
	Utility::StopAudio(_T("game_bgm_6"));
	Utility::StopAudio(_T("game_bgm_7"));
	Utility::StopAudio(_T("game_bgm_8"));
	Utility::StopAudio(_T("game_bgm_9"));
	CharacterManager::Instance()->DestroyCharacter();
	SceneManager::Instance()->SetIsGameOver(false);
	CameraManager::Instance()->GetCamera()->Reset();
	BulletTimeManager::Instance()->SetStatus(BulletTimeManager::Status::Exiting);
}
void GameSceneEight::DrawBackground()
{
	IMAGE* img_background = ResourcesManager::Instance()->FindImage("game_background_6");
	Rect rect_dst =
	{
		(getwidth() - img_background->getwidth()) / 2,
		(getheight() - img_background->getheight()) / 2,
		img_background->getwidth(),
		img_background->getheight()
	};
	Utility::PutimageEX(img_background, &rect_dst);
}
void GameSceneEight::DrawRemainHp()
{
	IMAGE* img_ui_hp = ResourcesManager::Instance()->FindImage("ui_heart");
	Rect rect_dst = { 0,10,img_ui_hp->getwidth(),img_ui_hp->getheight() };
	for (int i = 0; i < CharacterManager::Instance()->GetPlayer()->GetHp(); i++)
	{
		rect_dst.x = 10 + i * 40;
		Utility::PutimageEX(img_ui_hp, &rect_dst);
	}
}