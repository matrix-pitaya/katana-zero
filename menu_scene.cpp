#include"menu_scene.h"
#include"resources_manager.h"
#include"camera_manager.h"
#include"scene_manager.h"
#include"util.h"
MenuScene::MenuScene()
{
	blinkTimer.SetOneShot(false);
	blinkTimer.SetWaitTime(0.1f);
	blinkTimer.SetOnTimeout([&]()
		{
			isVisable = !isVisable;
		});

	blinkDurationTimer.SetOneShot(true);
	blinkDurationTimer.SetWaitTime(0.8f);
	blinkDurationTimer.SetOnTimeout([&]()
		{
			isBlinking = false;
			isVisable = true;
			blinkChangeTimer.Restart();
		});

	blinkChangeTimer.SetOneShot(true);
	blinkChangeTimer.SetWaitTime(5.0f);
	blinkChangeTimer.SetOnTimeout([&]()
		{
			isBlinking = true;
			isVisable = true;
			blinkDurationTimer.Restart();
		});

	animationPlant.set_loop(true);
	animationPlant.set_interval(0.075f);
	animationPlant.set_anchor_mode(Animation::AnchorMode::BottomCentered);
	animationPlant.add_frame(ResourcesManager::Instance()->FindAtlas("menu_plants"));

	grassLineMoveTimer.SetOneShot(false);
	grassLineMoveTimer.SetWaitTime(0.05f);
	grassLineMoveTimer.SetOnTimeout([&]()
		{
			grassMoveLine++;
		});
}
void MenuScene::OnEnter()
{
	switch (Utility::RandomRange(1,4))
	{
		case 2:
			Utility::PlayAudio(_T("menu_bgm_1"), true);
			break;
		case 1:
			Utility::PlayAudio(_T("menu_bgm_2"), true);
			break;
		case 3:
			Utility::PlayAudio(_T("menu_bgm_3"), true);
			break;
		case 4:
			Utility::PlayAudio(_T("menu_bgm_4"), true);
			break;
	}
	SceneManager::Instance()->SetIsGameOver(false);
	animationPlant.SetPosition({ (float)(getwidth() / 2),(float)(getheight()) });
	isOuting = false;
	isEnterVisable = true;
	progress = 0;
	blackBackgroundY = getwidth();
	katanaZeroMovePositionY = 0;
	othersMovePositionY = 0;
	backgroundMoveY = 0;
	CameraManager::Instance()->GetCamera()->Reset();
}
void  MenuScene::OnUpdata(float delta)
{
	if (isBlinking)
	{
		blinkTimer.OnUpdata(delta);
	}
	blinkDurationTimer.OnUpdata(delta);
	blinkChangeTimer.OnUpdata(delta);

	animationPlant.OnUpdata(delta);
	grassLineMoveTimer.OnUpdata(delta);

	if (grassMoveLine == getwidth())
	{
		grassMoveLine = 0;
	}

	if (isOuting)
	{
		progress += SCENE_SPEED_PROGRESS * delta;
		if (progress >= 1)
		{
			progress = 1;
		}
		katanaZeroMovePositionY += delta * Utility::Lerp(0, SCENE_SPEED_KATANA_ZERO, progress);
		backgroundMoveY += delta * Utility::Lerp(0, SCENE_SPEED_BACKGROUND, progress);
		othersMovePositionY += delta * Utility::Lerp(0, SCENE_SPEED_OTHERS, progress);
		blackBackgroundY = getheight() - othersMovePositionY;
		animationPlant.SetPosition({ (float)(getwidth() / 2),(float)(getheight() - othersMovePositionY) });
		if (blackBackgroundY <= 0)
		{
			SceneManager::Instance()->SwitchTo(SceneType::Select);
		}
	}
}
void  MenuScene::OnRender()
{
	DrawBackground();
	DrawBackgroundIron();
	Draw_ZERO_Bottom();
	Draw_ZER_Up();
	Draw_O_Up();
	Draw_KATANA();
	DrawEnter();
	DrawGrass();
	DrawPlant();
	DrawBlackBackground();
}
void  MenuScene::OnInput(const ExMessage& msg)
{
	switch (msg.message)
	{

	case WM_KEYUP:
		switch (msg.vkcode)
		{
		case VK_RETURN:
			isOuting = true;
			isEnterVisable = false;
			break;
		}
		break;
	}
}
void  MenuScene::OnExit()
{
	
}
void  MenuScene::DrawBackground()
{
	IMAGE* img_background = ResourcesManager::Instance()->FindImage("menu_background");
	Rect rect_dst =
	{
		0,
		0 - backgroundMoveY,
		getwidth(),
		getheight()
	};
	Utility::PutimageEX(img_background, &rect_dst);
}
void  MenuScene::DrawBackgroundIron()
{
	IMAGE* img_back_ground_iron = ResourcesManager::Instance()->FindImage("menu_background_iron");
	Rect rect_dst_iron =
	{
		0,
		0 - othersMovePositionY,
		getwidth(),
		getheight()
	};
	Utility::PutimageEX(img_back_ground_iron, &rect_dst_iron);
}
void  MenuScene::Draw_ZERO_Bottom()
{
	IMAGE* img_ZERO_bottom = ResourcesManager::Instance()->FindImage("ZERO_bottom");
	Rect rect_dst_ZERO_bottom =
	{
		(getwidth() - img_ZERO_bottom->getwidth()) / 2,
		(getheight() - img_ZERO_bottom->getheight()) / 2 - 50 - katanaZeroMovePositionY,
		img_ZERO_bottom->getwidth(),
		img_ZERO_bottom->getheight()
	};
	Utility::PutimageEX(img_ZERO_bottom, &rect_dst_ZERO_bottom);
}
void  MenuScene::Draw_ZER_Up()
{
	IMAGE* img_ZER = ResourcesManager::Instance()->FindImage("ZERO_up_ZER");
	Rect rect_dst_ZER =
	{
		(getwidth() - img_ZER->getwidth()) / 2,
		(getheight() - img_ZER->getheight()) / 2 - 50 - katanaZeroMovePositionY,
		img_ZER->getwidth(),
		img_ZER->getheight()
	};
	Utility::PutimageEX(img_ZER, &rect_dst_ZER);
}
void  MenuScene::Draw_O_Up()
{
	if (isVisable)
	{
		IMAGE* img_O = ResourcesManager::Instance()->FindImage("ZERO_up_O");
		Rect rect_dst_O =
		{
			(getwidth() - img_O->getwidth()) / 2,
			(getheight() - img_O->getheight()) / 2 - 50 - katanaZeroMovePositionY,
			img_O->getwidth(),
			img_O->getheight()
		};
		Utility::PutimageEX(img_O, &rect_dst_O);
	}
}
void  MenuScene::Draw_KATANA()
{
	IMAGE* img_KATANA = ResourcesManager::Instance()->FindImage("KATANA");
	Rect rect_dst_KATANA =
	{
		(getwidth() - img_KATANA->getwidth()) / 2 - 3,
		(getheight() - img_KATANA->getheight()) / 2 - 50 - 80 - katanaZeroMovePositionY,
		img_KATANA->getwidth(),
		img_KATANA->getheight()
	};
	Utility::PutimageEX(img_KATANA, &rect_dst_KATANA);
}
void  MenuScene::DrawGrass()
{
	IMAGE* img_grass = ResourcesManager::Instance()->FindImage("menu_grass");
	Rect rect_dst_grass_left =
	{
		grassMoveLine - img_grass->getwidth(),
		(getheight() - img_grass->getheight()) - othersMovePositionY,

		img_grass->getwidth(),
		img_grass->getheight()
	};
	Rect rect_dst_grass_right =
	{
		grassMoveLine,
		(getheight() - img_grass->getheight() - othersMovePositionY) ,
		img_grass->getwidth(),
		img_grass->getheight()
	};
	Utility::PutimageEX(img_grass, &rect_dst_grass_left);
	Utility::PutimageEX(img_grass, &rect_dst_grass_right);
}
void  MenuScene::DrawPlant()
{
	animationPlant.OnRender();
}
void MenuScene::DrawBlackBackground()
{
	IMAGE* img_black_background = ResourcesManager::Instance()->FindImage("black_background");
	Rect rect_black_background =
	{
		0,
		blackBackgroundY,
		img_black_background->getwidth(),
		img_black_background->getheight()
	};
	Utility::PutimageEX(img_black_background, &rect_black_background);
}
void MenuScene::DrawEnter()
{
	if (isEnterVisable)
	{
		IMAGE* img_enter = ResourcesManager::Instance()->FindImage("enter");
		Rect rect_dst =
		{
			getwidth() / 2 - img_enter->getwidth() / 2 ,
			getheight() * 2 / 3,
			img_enter->getwidth(),
			img_enter->getheight()
		};
		Utility::PutimageEX(img_enter, &rect_dst);
	}
}