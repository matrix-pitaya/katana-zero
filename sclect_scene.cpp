#include"select_scene.h"
#include"scene_manager.h"
#include"resources_manager.h"
#include"util.h"
SelectScene::SelectScene()
{
	timerHandoff.SetOneShot(true);
	timerHandoff.SetWaitTime(0.5f);
	timerHandoff.SetOnTimeout([&]()
		{
			isHandoff = false;
		});

	animationBlurredScreen.set_loop(true);
	animationBlurredScreen.set_interval(0.05f);
	animationBlurredScreen.SetPosition({ (float)(getwidth() / 2), (float)(getheight() / 4) });
	animationBlurredScreen.set_anchor_mode(Animation::AnchorMode::Centered);
	animationBlurredScreen.add_frame(ResourcesManager::Instance()->FindAtlas("blurred_screen"));
}
void SelectScene::OnEnter()
{
	isHandoff = false;
	SceneManager::Instance()->SetSceneType(SceneType::GameOne);
}
void SelectScene::OnUpdata(float delta)
{
	if (isHandoff)
	{
		timerHandoff.OnUpdata(delta);
		animationBlurredScreen.OnUpdata(delta);
	}
}
void SelectScene::OnRender()
{
	DrawBackground();
	DrawSelectGame();
	DrawAV();
	DrawBlurredScreen();
	DrawTrophy();
	DrawForeground();
	DrawSelectVideo();
	DrawRemote();
}
void SelectScene::OnInput(const ExMessage& msg)
{
	switch (msg.message)
	{
	case WM_KEYDOWN:
		switch (msg.vkcode)
		{
		case'A':
		case'a':
			isLeftDown = true;
			break;
		case'D':
		case'd':
			isRightDown = true;
			break;
		case VK_RETURN:
			isReadyDown = true;
			break;
		}
		break;
	case WM_KEYUP:
		switch (msg.vkcode)
		{
		case'A':
		case'a':
			Utility::PlayAudio(_T("blurred_screen"), false);
			isLeftDown = false;
			isHandoff = true;
			timerHandoff.Restart();
			SceneManager::Instance()->SetSceneType((SceneType)(((int)SceneType::Invalid + ((int)SceneManager::Instance()->GetSceneType()) - 1 ) % (int)SceneType::Invalid));
			break;
		case'D':
		case'd':
			Utility::PlayAudio(_T("blurred_screen"), false);
			isRightDown = false;
			isHandoff = true;
			timerHandoff.Restart();
			SceneManager::Instance()->SetSceneType((SceneType)((((int)SceneManager::Instance()->GetSceneType()) + 1) % (int)SceneType::Invalid));
			break;
		case VK_RETURN:
			isReadyDown = false;
			switch (SceneManager::Instance()->GetSceneType())
			{
			case SceneType::GameOne:
				SceneManager::Instance()->SwitchTo(SceneType::GameOne);
				break;
			case SceneType::GameTwo:
				SceneManager::Instance()->SwitchTo(SceneType::GameTwo);
				break;
			case SceneType::GameThree:
				SceneManager::Instance()->SwitchTo(SceneType::GameThree);
				break;
			case SceneType::GameFour:
				SceneManager::Instance()->SwitchTo(SceneType::GameFour);
				break;
			case SceneType::GameFive:
				SceneManager::Instance()->SwitchTo(SceneType::GameFive);
				break;
			case SceneType::GameSix:
				SceneManager::Instance()->SwitchTo(SceneType::GameSix);
				break;
			case SceneType::GameSeven:
				SceneManager::Instance()->SwitchTo(SceneType::GameSeven);
				break;
			case SceneType::GameEight:
				SceneManager::Instance()->SwitchTo(SceneType::GameEight);
				break;
			case SceneType::GameNine:
				SceneManager::Instance()->SwitchTo(SceneType::GameNine);
				break;
			case SceneType::GameTen:
				SceneManager::Instance()->SwitchTo(SceneType::GameTen);
				break;
			case SceneType::GameEleven:
				SceneManager::Instance()->SwitchTo(SceneType::GameEleven);
				break;
			case SceneType::GameTwelve:
				SceneManager::Instance()->SwitchTo(SceneType::GameTwelve);
				break;
			}
		}
		break;
	}
}
void SelectScene::OnExit()
{
	Utility::StopAudio(_T("menu_bgm_1"));
	Utility::StopAudio(_T("menu_bgm_2"));
	Utility::StopAudio(_T("menu_bgm_3"));
	Utility::StopAudio(_T("menu_bgm_4"));
}
void SelectScene::DrawBackground()
{
	IMAGE* img_background = ResourcesManager::Instance()->FindImage("select_background");
	Rect rect_dst =
	{
		0,
		0,
		getwidth(),
		getheight()
	};
	Utility::PutimageEX(img_background, &rect_dst);
}
void SelectScene::DrawForeground()
{
	IMAGE* img_foreground = ResourcesManager::Instance()->FindImage("select_foreground");
	Rect rect_dst =
	{
		0,
		0,
		getwidth(),
		getheight()
	};
	Utility::PutimageEX(img_foreground, &rect_dst);
}
void SelectScene::DrawRemote()
{
	if (isLeftDown)
	{
		IMAGE* img_remote_left_down = ResourcesManager::Instance()->FindImage("remote_left_down");
		Rect rect_dst =
		{
			(getwidth() + img_remote_left_down->getwidth()) / 2,
			(getheight() - img_remote_left_down->getheight()),
			img_remote_left_down->getwidth(),
			img_remote_left_down->getheight()
		};
		Utility::PutimageEX(img_remote_left_down, &rect_dst);
	}
	else if (isRightDown)
	{
		IMAGE* img_remote_right_down = ResourcesManager::Instance()->FindImage("remote_right_down");
		Rect rect_dst =
		{
			(getwidth() + img_remote_right_down->getwidth()) / 2,
			(getheight() - img_remote_right_down->getheight()),
			img_remote_right_down->getwidth(),
			img_remote_right_down->getheight()
		};
		Utility::PutimageEX(img_remote_right_down, &rect_dst);
	}
	else if (isReadyDown)
	{
		IMAGE* img_remote_ready_down = ResourcesManager::Instance()->FindImage("remote_ready_down");
		Rect rect_dst =
		{
			(getwidth() + img_remote_ready_down->getwidth()) / 2,
			(getheight() - img_remote_ready_down->getheight()),
			img_remote_ready_down->getwidth(),
			img_remote_ready_down->getheight()
		};
		Utility::PutimageEX(img_remote_ready_down, &rect_dst);
	}
	else
	{
		IMAGE* img_remote = ResourcesManager::Instance()->FindImage("remote");
		Rect rect_dst =
		{
			(getwidth() + img_remote->getwidth()) / 2,
			(getheight() - img_remote->getheight()),
			img_remote->getwidth(),
			img_remote->getheight()
		};
		Utility::PutimageEX(img_remote, &rect_dst);
	}
}
void SelectScene::DrawAV()
{
	IMAGE* img_AV = ResourcesManager::Instance()->FindImage("AV");
	Rect rect_dst =
	{
		getwidth() / 3 + img_AV->getwidth() * 2,
		img_AV->getheight() * 2,
		img_AV->getwidth(),
		img_AV->getheight()
	};
	Utility::PutimageEX(img_AV, &rect_dst);
}
void SelectScene::DrawSelectGame()
{
	switch (SceneManager::Instance()->GetSceneType())
	{
	case SceneType::GameOne:
	{
		IMAGE* img_select_game_one = ResourcesManager::Instance()->FindImage("select_game_one");
		Rect rect_dst_one =
		{
			(getwidth() - img_select_game_one->getwidth()) / 2 + 5,
			getheight() / 2 - img_select_game_one->getheight() - 25,
			img_select_game_one->getwidth(),
			img_select_game_one->getheight()
		};
		Utility::PutimageEX(img_select_game_one, &rect_dst_one);
	}
		break;
	case SceneType::GameTwo:
	{
		IMAGE* img_select_game_two = ResourcesManager::Instance()->FindImage("select_game_two");
		Rect rect_dst_two =
		{
			(getwidth() - img_select_game_two->getwidth()) / 2 + 5,
			getheight() / 2 - img_select_game_two->getheight() - 25,
			img_select_game_two->getwidth(),
			img_select_game_two->getheight()
		};
		Utility::PutimageEX(img_select_game_two, &rect_dst_two);
	}
		break;
	case SceneType::GameThree:
	{
		IMAGE* img_select_game_three = ResourcesManager::Instance()->FindImage("select_game_three");
		Rect rect_dst_three =
		{
			(getwidth() - img_select_game_three->getwidth()) / 2 + 5,
			getheight() / 2 - img_select_game_three->getheight() - 25,
			img_select_game_three->getwidth(),
			img_select_game_three->getheight()
		};
		Utility::PutimageEX(img_select_game_three, &rect_dst_three);
	}
		break;
	case SceneType::GameFour:
	{
		IMAGE* img_select_game_four = ResourcesManager::Instance()->FindImage("select_game_four");
		Rect rect_dst_four =
		{
			(getwidth() - img_select_game_four->getwidth()) / 2 + 5,
			getheight() / 2 - img_select_game_four->getheight() - 25,
			img_select_game_four->getwidth(),
			img_select_game_four->getheight()
		};
		Utility::PutimageEX(img_select_game_four, &rect_dst_four);
	}
		break;
	case SceneType::GameFive:
	{
		IMAGE* img_select_game_five = ResourcesManager::Instance()->FindImage("select_game_five");
		Rect rect_dst_five =
		{
			(getwidth() - img_select_game_five->getwidth()) / 2 + 5,
			getheight() / 2 - img_select_game_five->getheight() - 25,
			img_select_game_five->getwidth(),
			img_select_game_five->getheight()
		};
		Utility::PutimageEX(img_select_game_five, &rect_dst_five);
	}
		break;
	case SceneType::GameSix:
	{
		IMAGE* img_select_game_six = ResourcesManager::Instance()->FindImage("select_game_six");
		Rect rect_dst_six =
		{
			(getwidth() - img_select_game_six->getwidth()) / 2 + 5,
			getheight() / 2 - img_select_game_six->getheight() - 25,
			img_select_game_six->getwidth(),
			img_select_game_six->getheight()
		};
		Utility::PutimageEX(img_select_game_six, &rect_dst_six);
	}
		break;
	case SceneType::GameSeven:
	{
		IMAGE* img_select_game_seven = ResourcesManager::Instance()->FindImage("select_game_seven");
		Rect rect_dst_seven =
		{
			(getwidth() - img_select_game_seven->getwidth()) / 2 + 5,
			getheight() / 2 - img_select_game_seven->getheight() - 25,
			img_select_game_seven->getwidth(),
			img_select_game_seven->getheight()
		};
		Utility::PutimageEX(img_select_game_seven, &rect_dst_seven);
	}
		break;
	case SceneType::GameEight:
	{
		IMAGE* img_select_game_eight = ResourcesManager::Instance()->FindImage("select_game_eight");
		Rect rect_dst_eight =
		{
			(getwidth() - img_select_game_eight->getwidth()) / 2 + 5,
			getheight() / 2 - img_select_game_eight->getheight() - 25,
			img_select_game_eight->getwidth(),
			img_select_game_eight->getheight()
		};
		Utility::PutimageEX(img_select_game_eight, &rect_dst_eight);
	}
		break;
	case SceneType::GameNine:
	{
		IMAGE* img_select_game_nine = ResourcesManager::Instance()->FindImage("select_game_nine");
		Rect rect_dst_nine =
		{
			(getwidth() - img_select_game_nine->getwidth()) / 2 + 5,
			getheight() / 2 - img_select_game_nine->getheight() - 25,
			img_select_game_nine->getwidth(),
			img_select_game_nine->getheight()
		};
		Utility::PutimageEX(img_select_game_nine, &rect_dst_nine);
	}
		break;
	case SceneType::GameTen:
	{
		IMAGE* img_select_game_ten = ResourcesManager::Instance()->FindImage("select_game_ten");
		Rect rect_dst_ten =
		{
			(getwidth() - img_select_game_ten->getwidth()) / 2 + 5,
			getheight() / 2 - img_select_game_ten->getheight() - 25,
			img_select_game_ten->getwidth(),
			img_select_game_ten->getheight()
		};
		Utility::PutimageEX(img_select_game_ten, &rect_dst_ten);
	}
		break;
	case SceneType::GameEleven:
	{
		IMAGE* img_select_game_eleven = ResourcesManager::Instance()->FindImage("select_game_eleven");
		Rect rect_dst_eleven =
		{
			(getwidth() - img_select_game_eleven->getwidth()) / 2 + 5,
			getheight() / 2 - img_select_game_eleven->getheight() - 25,
			img_select_game_eleven->getwidth(),
			img_select_game_eleven->getheight()
		};
		Utility::PutimageEX(img_select_game_eleven, &rect_dst_eleven);
	}
		break;
	case SceneType::GameTwelve:
	{
		IMAGE* img_select_game_twelve = ResourcesManager::Instance()->FindImage("select_game_twelve");
		Rect rect_dst_twelve =
		{
			(getwidth() - img_select_game_twelve->getwidth()) / 2 + 5,
			getheight() / 2 - img_select_game_twelve->getheight() - 25,
			img_select_game_twelve->getwidth(),
			img_select_game_twelve->getheight()
		};
		Utility::PutimageEX(img_select_game_twelve, &rect_dst_twelve);
	}
		break;
	}
}
void SelectScene::DrawSelectVideo()
{
	{
		IMAGE* img_select = ResourcesManager::Instance()->FindImage("select_1");
		Rect rect_dst =
		{
			getwidth() / 9 + 5 * 0,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 0 + 5,
			img_select->getwidth(),
			img_select->getheight()
		};
		IMAGE* img_select_right = ResourcesManager::Instance()->FindImage("select_right");
		Rect rect_dst_ =
		{
			getwidth() / 9 + 5 * 0 + img_select_right->getwidth() + 30,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 0 + 5,
			img_select_right->getwidth(),
			img_select_right->getheight()
		};
		Utility::PutimageEX(img_select_right, &rect_dst_);
		Utility::PutimageEX(img_select, &rect_dst);
		Utility::ShededText(rect_dst.x + img_select->getwidth() / 2 - 10, rect_dst_.y + img_select->getheight() / 4, _T("工厂"));
		if (SceneManager::Instance()->GetIsPass(SceneType::GameOne))
		{
			IMAGE* img_start = ResourcesManager::Instance()->FindImage("complete_start");
			Rect rect_dst_start =
			{
				rect_dst.x + img_select->getwidth() / 2 - 38,
				rect_dst_.y + img_select->getheight() / 4,
				img_start->getwidth(),
				img_start->getheight()
			};
			Utility::PutimageEX(img_start, &rect_dst_start);
		}
	}
	{
		IMAGE* img_select = ResourcesManager::Instance()->FindImage("select_2");
		Rect rect_dst =
		{
			getwidth() / 9 + 5 * 1,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 1 + 5,
			img_select->getwidth(),
			img_select->getheight()
		};
		IMAGE* img_select_right = ResourcesManager::Instance()->FindImage("select_right");
		Rect rect_dst_ =
		{
			getwidth() / 9 + 5 * 0 + img_select_right->getwidth() + 25 - 2,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 1 + 5,
			img_select_right->getwidth(),
			img_select_right->getheight()
		};
		Utility::PutimageEX(img_select_right, &rect_dst_);
		Utility::PutimageEX(img_select, &rect_dst);
		Utility::ShededText(rect_dst.x + img_select->getwidth() / 2 - 10, rect_dst_.y + img_select->getheight() / 4, _T("酒店"));
		if (SceneManager::Instance()->GetIsPass(SceneType::GameTwo))
		{
			IMAGE* img_start = ResourcesManager::Instance()->FindImage("complete_start");
			Rect rect_dst_start =
			{
				rect_dst.x + img_select->getwidth() / 2 - 35,
				rect_dst_.y + img_select->getheight() / 4,
				img_start->getwidth(),
				img_start->getheight()
			};
			Utility::PutimageEX(img_start, &rect_dst_start);
		}
	}
	{
		IMAGE* img_select = ResourcesManager::Instance()->FindImage("select_3");
		Rect rect_dst =
		{
			getwidth() / 9 + 5 * 2,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 2 + 5,
			img_select->getwidth(),
			img_select->getheight()
		};
		IMAGE* img_select_right = ResourcesManager::Instance()->FindImage("select_right");
		Rect rect_dst_ =
		{
			getwidth() / 9 + 5 * 0 + img_select_right->getwidth() + 20,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 2 + 5,
			img_select_right->getwidth(),
			img_select_right->getheight()
		};
		Utility::PutimageEX(img_select_right, &rect_dst_);
		Utility::PutimageEX(img_select, &rect_dst);
		Utility::ShededText(rect_dst.x + img_select->getwidth() / 2 - 10, rect_dst_.y + img_select->getheight() / 4, _T("舞厅"));
		if (SceneManager::Instance()->GetIsPass(SceneType::GameThree))
		{
			IMAGE* img_start = ResourcesManager::Instance()->FindImage("complete_start");
			Rect rect_dst_start =
			{
				rect_dst.x + img_select->getwidth() / 2 - 46,
				rect_dst_.y + img_select->getheight() / 4,
				img_start->getwidth(),
				img_start->getheight()
			};
			Utility::PutimageEX(img_start, &rect_dst_start);
		}
	}
	{
		IMAGE* img_select = ResourcesManager::Instance()->FindImage("select_4");
		Rect rect_dst =
		{
			getwidth() / 9 + 5 * 2 - 2,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 3 + 5,
			img_select->getwidth(),
			img_select->getheight()
		};
		IMAGE* img_select_right = ResourcesManager::Instance()->FindImage("select_right");
		Rect rect_dst_ =
		{
			getwidth() / 9 + 5 * 0 + img_select_right->getwidth() + 23,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 3 + 5,
			img_select_right->getwidth(),
			img_select_right->getheight()
		};
		Utility::PutimageEX(img_select_right, &rect_dst_);
		Utility::PutimageEX(img_select, &rect_dst);
		Utility::ShededText(rect_dst.x + img_select->getwidth() / 2 - 10, rect_dst_.y + img_select->getheight() / 4, _T("监狱"));
		if (SceneManager::Instance()->GetIsPass(SceneType::GameFour))
		{
			IMAGE* img_start = ResourcesManager::Instance()->FindImage("complete_start");
			Rect rect_dst_start =
			{
				rect_dst.x + img_select->getwidth() / 2 - 35,
				rect_dst_.y + img_select->getheight() / 4,
				img_start->getwidth(),
				img_start->getheight()
			};
			Utility::PutimageEX(img_start, &rect_dst_start);
		}
	}
	{
		IMAGE* img_select = ResourcesManager::Instance()->FindImage("select_5");
		Rect rect_dst =
		{
			getwidth() / 9 + img_select->getwidth() * 17 / 10 - 25,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 0 + 5,
			img_select->getwidth(),
			img_select->getheight()
		};
		IMAGE* img_select_left = ResourcesManager::Instance()->FindImage("select_left");
		Rect rect_dst_ =
		{
			getwidth() / 9 + img_select->getwidth() * 17 / 10 - img_select_left->getwidth() / 3 - 25,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 0 + 5,
			img_select_left->getwidth(),
			img_select_left->getheight()
		};
		Utility::PutimageEX(img_select_left, &rect_dst_);
		Utility::PutimageEX(img_select, &rect_dst);
		Utility::ShededText(rect_dst.x + img_select->getwidth() / 2 - 10, rect_dst_.y + img_select->getheight() / 4, _T("制片厂"));
		if (SceneManager::Instance()->GetIsPass(SceneType::GameFive))
		{
			IMAGE* img_start = ResourcesManager::Instance()->FindImage("complete_start");
			Rect rect_dst_start =
			{
				rect_dst.x + img_select->getwidth() / 2 - 35,
				rect_dst_.y + img_select->getheight() / 4,
				img_start->getwidth(),
				img_start->getheight()
			};
			Utility::PutimageEX(img_start, &rect_dst_start);
		}
	}
	{
		IMAGE* img_select = ResourcesManager::Instance()->FindImage("select_6");
		Rect rect_dst =
		{
			getwidth() / 9 - 15 + img_select->getwidth() * 17 / 10 - 25,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 1 + 5,
			img_select->getwidth(),
			img_select->getheight()
		};
		IMAGE* img_select_left = ResourcesManager::Instance()->FindImage("select_left");
		Rect rect_dst_ =
		{
			getwidth() / 9 - 8 + img_select->getwidth() * 17 / 10 - img_select_left->getwidth() / 3 - 25,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 1 + 5,
			img_select_left->getwidth(),
			img_select_left->getheight()
		};
		Utility::PutimageEX(img_select_left, &rect_dst_);
		Utility::PutimageEX(img_select, &rect_dst);
		Utility::ShededText(rect_dst.x + img_select->getwidth() / 2 - 10, rect_dst_.y + img_select->getheight() / 4, _T("公馆"));
		if (SceneManager::Instance()->GetIsPass(SceneType::GameSix))
		{
			IMAGE* img_start = ResourcesManager::Instance()->FindImage("complete_start");
			Rect rect_dst_start =
			{
				rect_dst.x + img_select->getwidth() / 2 - 40,
				rect_dst_.y + img_select->getheight() / 4,
				img_start->getwidth(),
				img_start->getheight()
			};
			Utility::PutimageEX(img_start, &rect_dst_start);
		}
	}
	{
		IMAGE* img_select = ResourcesManager::Instance()->FindImage("select_7");
		Rect rect_dst =
		{
			getwidth() / 9 - 20 + img_select->getwidth() * 17 / 10 - 25,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 2 + 5,
			img_select->getwidth(),
			img_select->getheight()
		};
		IMAGE* img_select_left = ResourcesManager::Instance()->FindImage("select_left");
		Rect rect_dst_ =
		{
			getwidth() / 9 - 15 + img_select->getwidth() * 17 / 10 - img_select_left->getwidth() / 3 - 25,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 2 + 5,
			img_select_left->getwidth(),
			img_select_left->getheight()
		};
		Utility::PutimageEX(img_select_left, &rect_dst_);
		Utility::PutimageEX(img_select, &rect_dst);
		Utility::ShededText(rect_dst.x + img_select->getwidth() / 2 - 10, rect_dst_.y + img_select->getheight() / 4, _T("唐人街"));
		if (SceneManager::Instance()->GetIsPass(SceneType::GameSeven))
		{
			IMAGE* img_start = ResourcesManager::Instance()->FindImage("complete_start");
			Rect rect_dst_start =
			{
				rect_dst.x + img_select->getwidth() / 2 - 30,
				rect_dst_.y + img_select->getheight() / 4,
				img_start->getwidth(),
				img_start->getheight()
			};
			Utility::PutimageEX(img_start, &rect_dst_start);
		}
	}
	{
		IMAGE* img_select = ResourcesManager::Instance()->FindImage("select_8");
		Rect rect_dst =
		{
			getwidth() / 9 - 5 + img_select->getwidth() * 17 / 10 - 25,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 3 + 5,
			img_select->getwidth(),
			img_select->getheight()
		};
		IMAGE* img_select_left = ResourcesManager::Instance()->FindImage("select_left");
		Rect rect_dst_ =
		{
			getwidth() / 9 + 5 + img_select->getwidth() * 17 / 10 - img_select_left->getwidth() / 3 - 25,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 3 + 5,
			img_select_left->getwidth(),
			img_select_left->getheight()
		};
		Utility::PutimageEX(img_select_left, &rect_dst_);
		Utility::PutimageEX(img_select, &rect_dst);
		Utility::ShededText(rect_dst.x + img_select->getwidth() / 2 - 65, rect_dst_.y + img_select->getheight() / 4, _T("录像带 - 龙王"));
		if (SceneManager::Instance()->GetIsPass(SceneType::GameEight))
		{
			IMAGE* img_start = ResourcesManager::Instance()->FindImage("complete_start");
			Rect rect_dst_start =
			{
				rect_dst.x + img_select->getwidth() / 2 - 85,
				rect_dst_.y + img_select->getheight() / 4,
				img_start->getwidth(),
				img_start->getheight()
			};
			Utility::PutimageEX(img_start, &rect_dst_start);
		}
	}
	{
		IMAGE* img_select = ResourcesManager::Instance()->FindImage("select_9");
		Rect rect_dst =
		{
			getwidth() / 9 - 5 + img_select->getwidth() * 3 - 15,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 0 + 5,
			img_select->getwidth(),
			img_select->getheight()
		};
		IMAGE* img_select_left = ResourcesManager::Instance()->FindImage("select_left");
		Rect rect_dst_ =
		{
			getwidth() / 9 +10 + img_select->getwidth() * 3 - 15 - img_select_left->getwidth() / 3,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 0 + 5,
			img_select_left->getwidth(),
			img_select_left->getheight()
		};
		Utility::PutimageEX(img_select_left, &rect_dst_);
		Utility::PutimageEX(img_select, &rect_dst);
		Utility::ShededText(rect_dst.x + img_select->getwidth() / 2 - 10, rect_dst_.y + img_select->getheight() / 4, _T("屠宰场"));
		if (SceneManager::Instance()->GetIsPass(SceneType::GameNine))
		{
			IMAGE* img_start = ResourcesManager::Instance()->FindImage("complete_start");
			Rect rect_dst_start =
			{
				rect_dst.x + img_select->getwidth() / 2 - 35,
				rect_dst_.y + img_select->getheight() / 4,
				img_start->getwidth(),
				img_start->getheight()
			};
			Utility::PutimageEX(img_start, &rect_dst_start);
		}
	}
	{
		IMAGE* img_select = ResourcesManager::Instance()->FindImage("select_10");
		Rect rect_dst =
		{
			getwidth() / 9 - 15 + img_select->getwidth() * 3 - 15,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 1 + 5,
			img_select->getwidth(),
			img_select->getheight()
		};
		IMAGE* img_select_left = ResourcesManager::Instance()->FindImage("select_left");
		Rect rect_dst_ =
		{
			getwidth() / 9 - 8 + img_select->getwidth() * 3 - 15 - img_select_left->getwidth() / 3,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 1 + 5,
			img_select_left->getwidth(),
			img_select_left->getheight()
		};
		Utility::PutimageEX(img_select_left, &rect_dst_);
		Utility::PutimageEX(img_select, &rect_dst);
		Utility::ShededText(rect_dst.x + img_select->getwidth() / 2 - 10, rect_dst_.y + img_select->getheight() / 4, _T("地堡"));
		if (SceneManager::Instance()->GetIsPass(SceneType::GameTen))
		{
			IMAGE* img_start = ResourcesManager::Instance()->FindImage("complete_start");
			Rect rect_dst_start =
			{
				rect_dst.x + img_select->getwidth() / 2 - 40,
				rect_dst_.y + img_select->getheight() / 4,
				img_start->getwidth(),
				img_start->getheight()
			};
			Utility::PutimageEX(img_start, &rect_dst_start);
		}
	}
	{
		IMAGE* img_select = ResourcesManager::Instance()->FindImage("select_11");
		Rect rect_dst =
		{
			getwidth() / 9 - 15 + img_select->getwidth() * 3 - 10,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 2 + 5,
			img_select->getwidth(),
			img_select->getheight()
		};
		IMAGE* img_select_left = ResourcesManager::Instance()->FindImage("select_left");
		Rect rect_dst_ =
		{
			getwidth() / 9 - 8 + img_select->getwidth() * 3 - 5 - img_select_left->getwidth() / 3,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 2 + 5,
			img_select_left->getwidth(),
			img_select_left->getheight()
		};
		Utility::PutimageEX(img_select_left, &rect_dst_);
		Utility::PutimageEX(img_select, &rect_dst);
		Utility::ShededText(rect_dst.x + img_select->getwidth() / 2 - 10, rect_dst_.y + img_select->getheight() / 4, _T("地堡 Ⅱ"));
		if (SceneManager::Instance()->GetIsPass(SceneType::GameEleven))
		{
			IMAGE* img_start = ResourcesManager::Instance()->FindImage("complete_start");
			Rect rect_dst_start =
			{
				rect_dst.x + img_select->getwidth() / 2 - 37,
				rect_dst_.y + img_select->getheight() / 4,
				img_start->getwidth(),
				img_start->getheight()
			};
			Utility::PutimageEX(img_start, &rect_dst_start);
		}
	}
	{
		IMAGE* img_select = ResourcesManager::Instance()->FindImage("select_12");
		Rect rect_dst =
		{
			getwidth() / 9 - 15 + img_select->getwidth() * 3,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 3 + 5,
			img_select->getwidth(),
			img_select->getheight()
		};
		IMAGE* img_select_left = ResourcesManager::Instance()->FindImage("select_left");
		Rect rect_dst_ =
		{
			getwidth() / 9 - 8 + img_select->getwidth() * 3 - 15 - img_select_left->getwidth() / 3,
			getheight() * 2 / 3 + img_select->getheight() / 4 + img_select->getheight() * 3 + 5,
			img_select_left->getwidth(),
			img_select_left->getheight()
		};
		Utility::PutimageEX(img_select_left, &rect_dst_);
		Utility::PutimageEX(img_select, &rect_dst);
		Utility::ShededText(rect_dst.x + img_select->getwidth() / 2 - 30, rect_dst_.y + img_select->getheight() / 4, _T("政府实验室"));
		if (SceneManager::Instance()->GetIsPass(SceneType::GameTwelve))
		{
			IMAGE* img_start = ResourcesManager::Instance()->FindImage("complete_start");
			Rect rect_dst_start =
			{
				rect_dst.x + img_select->getwidth() / 2 - 50,
				rect_dst_.y + img_select->getheight() / 4,
				img_start->getwidth(),
				img_start->getheight()
			};
			Utility::PutimageEX(img_start, &rect_dst_start);
		}
	}
}
void SelectScene::DrawBlurredScreen()
{
	if (isHandoff)
	{
		animationBlurredScreen.OnRender();
	}
}
void SelectScene::DrawTrophy()
{
	if (SceneManager::Instance()->GetIsPass(SceneType::GameOne)
		&& SceneManager::Instance()->GetIsPass(SceneType::GameTwo)
		&& SceneManager::Instance()->GetIsPass(SceneType::GameThree)
		&& SceneManager::Instance()->GetIsPass(SceneType::GameFour)
		&& SceneManager::Instance()->GetIsPass(SceneType::GameFive)
		&& SceneManager::Instance()->GetIsPass(SceneType::GameSix)
		&& SceneManager::Instance()->GetIsPass(SceneType::GameSeven)
		&& SceneManager::Instance()->GetIsPass(SceneType::GameEight)
		&& SceneManager::Instance()->GetIsPass(SceneType::GameNine)
		&& SceneManager::Instance()->GetIsPass(SceneType::GameTen)
		&& SceneManager::Instance()->GetIsPass(SceneType::GameEleven)
		&& SceneManager::Instance()->GetIsPass(SceneType::GameTwelve)
		)
	{
		IMAGE* img_trophy = ResourcesManager::Instance()->FindImage("trophy");
		Rect rect_dst =
		{
			getwidth() / 15,
			getheight() / 3 + 80,
			img_trophy->getwidth(),
			img_trophy->getheight()
		};
		Utility::PutimageEX(img_trophy, &rect_dst);
	}
}