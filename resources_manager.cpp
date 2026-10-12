#include"resources_manager.h"
#include"util.h"
#include<graphics.h>
ResourcesManager* ResourcesManager::instance = nullptr;

ResourcesManager* ResourcesManager::Instance()
{
	if (!instance)
	{
		instance = new ResourcesManager;
	}

	return instance;
}

ResourcesManager::ResourcesManager() = default;
ResourcesManager::~ResourcesManager() = default;

struct ImageResInof
{
	string id;
	LPCTSTR path;
};

struct AtlasResInof
{
	string id;
	LPCTSTR path;
	int num_frame = 0;
};

static const vector<ImageResInof> imageInofList =
{
	{"ui_heart"           ,	 _T(R"(resource\ui\ui_heart.png)")},


	{"menu_background"		  ,  _T(R"(resource\menu\menu_background.png)")	       },
	{"menu_background_iron"	  ,  _T(R"(resource\menu\menu_background_iron.png)")   },
	{"menu_grass"			  ,  _T(R"(resource\menu\menu_grass.png)")			   },
	{"start"			      ,  _T(R"(resource\menu\selector_tip.png)")		   },
	{"ZERO_bottom"			  ,  _T(R"(resource\menu\ZER0_bottom.png)")			   },
	{"ZERO_up_ZER"			  ,  _T(R"(resource\menu\ZERO_up_ZER.png)")			   },
	{"ZERO_up_O"			  ,  _T(R"(resource\menu\ZERO_up_O.png)")			   },
	{"KATANA"				  ,  _T(R"(resource\menu\KATANA.png)")			       },
	{"black_background"		  ,  _T(R"(resource\menu\black_background.png)")	   },
	{"enter"				  ,  _T(R"(resource\menu\selector_tip.png)")		   },


	{"AV"					  ,  _T(R"(resource\select\AV.png)")				   },
	{"remote"				  ,  _T(R"(resource\select\remote.png)")			   },
	{"remote_left_down"		  ,  _T(R"(resource\select\remote_left_down.png)")	   },
	{"remote_right_down"	  ,  _T(R"(resource\select\remote_right_down.png)")	   },
	{"remote_ready_down"	  ,  _T(R"(resource\select\remote_ready_down.png)")	   },
	{"select_1"		          ,  _T(R"(resource\select\select_1.png)")			   },
	{"select_2"		          ,  _T(R"(resource\select\select_2.png)")			   },
	{"select_3"		          ,  _T(R"(resource\select\select_3.png)")			   },
	{"select_4"		          ,  _T(R"(resource\select\select_4.png)")			   },
	{"select_5"		          ,  _T(R"(resource\select\select_5.png)")			   },
	{"select_6"		          ,  _T(R"(resource\select\select_6.png)")			   },
	{"select_7"		          ,  _T(R"(resource\select\select_7.png)")			   },
	{"select_8"		          ,  _T(R"(resource\select\select_8.png)")			   },
	{"select_9"		          ,  _T(R"(resource\select\select_9.png)")			   },
	{"select_10"		      ,  _T(R"(resource\select\select_10.png)")			   },
	{"select_11"		      ,  _T(R"(resource\select\select_11.png)")			   },
	{"select_12"		      ,  _T(R"(resource\select\select_12.png)")			   },
	{"select_left"		      ,  _T(R"(resource\select\select_left.png)")		   },
	{"select_right"		      ,  _T(R"(resource\select\select_right.png)")		   },
	{"select_background"	  ,  _T(R"(resource\select\select_background.png)")	   },
	{"select_foreground"	  ,  _T(R"(resource\select\select_foreground.png)")	   },
	{"select_game_one"		  ,  _T(R"(resource\select\select_game_one.png)")	   },
	{"select_game_two"		  ,  _T(R"(resource\select\select_game_two.png)")	   },
	{"select_game_three"	  ,  _T(R"(resource\select\select_game_three.png)")	   },
	{"select_game_four"		  ,  _T(R"(resource\select\select_game_four.png)")	   },
	{"select_game_five"		  ,  _T(R"(resource\select\select_game_five.png)")	   },
	{"select_game_six"		  ,  _T(R"(resource\select\select_game_six.png)")	   },
	{"select_game_seven"	  ,  _T(R"(resource\select\select_game_seven.png)")	   },
	{"select_game_eight"	  ,  _T(R"(resource\select\select_game_eight.png)")	   },
	{"select_game_nine"		  ,  _T(R"(resource\select\select_game_nine.png)")	   },
	{"select_game_ten"		  ,  _T(R"(resource\select\select_game_ten.png)")	   },
	{"select_game_eleven"	  ,  _T(R"(resource\select\select_game_eleven.png)")   },
	{"select_game_twelve"	  ,  _T(R"(resource\select\select_game_twelve.png)")   },
	{"complete_start"		  ,  _T(R"(resource\select\complete_start.png)")	   },
	{"trophy"				  ,  _T(R"(resource\select\trophy.png)")			   },

	{"game_background_6"	  ,  _T(R"(resource\background\game_background_6.png)")},

	{"player_attack_right"  ,	  _T(R"(resource\player\attack.png)")},
	{"player_dead_right"    ,     _T(R"(resource\player\dead.png)")  },
	{"player_fall_right"    ,     _T(R"(resource\player\fall.png)")  },
	{"player_idle_right"    ,     _T(R"(resource\player\idle.png)")  },
	{"player_jump_right"    ,     _T(R"(resource\player\jump.png)")  },
	{"player_roll_right"    ,     _T(R"(resource\player\roll.png)")  },
	{"player_run_right"     ,     _T(R"(resource\player\run.png)")   },

	{"player_vfx_attack_down"   ,  _T(R"(resource\player\vfx_attack_down.png)") },
	{"player_vfx_attack_left"   ,  _T(R"(resource\player\vfx_attack_left.png)") },
	{"player_vfx_attack_right"  ,  _T(R"(resource\player\vfx_attack_right.png)")},
	{"player_vfx_attack_up"     ,  _T(R"(resource\player\vfx_attack_up.png)")   },
	{"player_vfx_jump"          ,  _T(R"(resource\player\vfx_jump.png)")        },
	{"player_vfx_land"          ,  _T(R"(resource\player\vfx_land.png)")        },

	{"enemy_dragon_aim_in_air_right"          ,  _T(R"(resource\enemy\dragon\aim_in_air\1.png)")},
};

static const vector<AtlasResInof> atlasInofList =
{
	{"menu_plants"  ,  _T(R"(resource\menu\menu_plants_%d.png)")        ,  12},

	{"blurred_screen"  ,  _T(R"(resource\select\blurred_screen_%d.png)") ,  4},

	{"player_run_vfx_left"  ,  _T(R"(resource\player\vfx_run\%d.png)") ,  6},

	{"barb_break"  ,  _T(R"(resource\enemy\hornet\barb_break\%d.png)")  ,  3},
	{"barb_loose"  ,  _T(R"(resource\enemy\hornet\barb_loose\%d.png)")  ,  5},
	{"silk"        ,  _T(R"(resource\enemy\hornet\silk\%d.png)")        ,  9},
	{"sword_left"  ,  _T(R"(resource\enemy\hornet\sword\%d.png)")       ,  3},
	{"enemy_hornet_aim_left"		     ,  _T(R"(resource\enemy\hornet\aim\%d.png)")             ,  9  },
	{"enemy_hornet_dash_in_air_left"     ,  _T(R"(resource\enemy\hornet\dash_in_air\%d.png)")     ,  2  },
	{"enemy_hornet_dash_on_floor_left"   ,  _T(R"(resource\enemy\hornet\dash_on_floor\%d.png)")   ,  2  },
	{"enemy_hornet_fall_left"			 ,  _T(R"(resource\enemy\hornet\fall\%d.png)")			  ,  4  },
	{"enemy_hornet_idle_left"			 ,  _T(R"(resource\enemy\hornet\idle\%d.png)")			  ,  6  },
	{"enemy_hornet_jump_left"			 ,  _T(R"(resource\enemy\hornet\jump\%d.png)")			  ,  8  },
	{"enemy_hornet_run_left"			 ,  _T(R"(resource\enemy\hornet\run\%d.png)")			  ,  8  },
	{"enemy_hornet_squat_left"			 ,  _T(R"(resource\enemy\hornet\squat\%d.png)")		      ,  10 },
	{"enemy_hornet_throw_barb_left"		 ,  _T(R"(resource\enemy\hornet\throw_barb\%d.png)")	  ,  8  },
	{"enemy_hornet_throw_silk_left"		 ,  _T(R"(resource\enemy\hornet\throw_silk\%d.png)")	  ,  17 },
	{"enemy_hornet_throw_sword_left"	 ,  _T(R"(resource\enemy\hornet\throw_sword\%d.png)")	  ,  16 },
	{"enemy_hornet_vfx_dash_in_air_left"	 ,  _T(R"(resource\enemy\hornet\vfx_dash_in_air\%d.png)")	 ,  5},
	{"enemy_hornet_vfx_dash_on_floor_left"	 ,  _T(R"(resource\enemy\hornet\vfx_dash_on_floor\%d.png)")  ,  6},

	{"fire_bullet_attacked"			 ,  _T(R"(resource\enemy\dragon\bullet_fire_attacked\%d.png)")	,  6},
	{"fire_bullet_left"				 ,  _T(R"(resource\enemy\dragon\bullet_fire_left\%d.png)")	 	,  5},
	{"fire_bullet_right"			 ,  _T(R"(resource\enemy\dragon\bullet_fire_right\%d.png)")	 	,  5},
	{"OnFireUp"						 ,  _T(R"(resource\enemy\dragon\bullet_fire_up\%d.png)")	 	,  5},
	{"fire_up_break"				 ,  _T(R"(resource\enemy\dragon\bullet_fire_up_break\%d.png)")	,  9},
	{"enemy_dragon_aim_right"		 ,  _T(R"(resource\enemy\dragon\aim\%d.png)")					,  3},
	{"enemy_dragon_attack_right"	 ,  _T(R"(resource\enemy\dragon\attack\%d.png)")				,  5},
	{"enemy_dragon_dash_right"		 ,  _T(R"(resource\enemy\dragon\dash\%d.png)")					,  2},
	{"enemy_dragon_dead_right"		 ,  _T(R"(resource\enemy\dragon\dead\%d.png)")					,  5},
	{"enemy_dragon_fall_right"		 ,  _T(R"(resource\enemy\dragon\fall\%d.png)")					,  4},
	{"enemy_dragon_fire_right"		 ,  _T(R"(resource\enemy\dragon\fire\%d.png)")					,  4},
	{"enemy_dragon_idle_right"		 ,  _T(R"(resource\enemy\dragon\idle\%d.png)")					,  6},
	{"enemy_dragon_jump_right"		 ,  _T(R"(resource\enemy\dragon\jump\%d.png)")					,  4},
	{"enemy_dragon_roll_right"		 ,  _T(R"(resource\enemy\dragon\roll\%d.png)")					,  6},
	{"enemy_dragon_run_right"		 ,  _T(R"(resource\enemy\dragon\run\%d.png)")					,  10},
	{"enemy_dragon_vfx_fire_right"	 ,  _T(R"(resource\enemy\dragon\vfx_fire\%d.png)")				,  9},
	{"enemy_dragon_vfx_slash_down"	 ,  _T(R"(resource\enemy\dragon\vfx_slash_down\%d.png)")		,  5},
	{"enemy_dragon_vfx_slash_up"	 ,  _T(R"(resource\enemy\dragon\vfx_slash_up\%d.png)")			,  5},
	{"enemy_dragon_vfx_slash_left"	 ,  _T(R"(resource\enemy\dragon\vfx_slash_left\%d.png)")		,  5},
	{"enemy_dragon_vfx_slash_right"	 ,  _T(R"(resource\enemy\dragon\vfx_slash_right\%d.png)")		,  5}
};

void ResourcesManager::Load()
{
	for (auto& info : imageInofList)
	{
		IMAGE* image = new IMAGE();
		loadimage(image, info.path);
		if (!Utility::ChekImageIsValid(image))
		{
			throw(info.path);
		}
		imagePool[info.id] = image;
	}
	for (auto& info : atlasInofList)
	{
		Atlas* atlas = new Atlas();
		atlas->Load(info.path, info.num_frame);
		for (int i = 0; i < atlas->GetSize(); i++)
		{
			if (!Utility::ChekImageIsValid(atlas->get_image(i)))
			{
				throw(info.path);
			}
		}
		atlasPool[info.id] = atlas;
	}

	FlipImage("player_attack_right", "player_attack_left", 5);
	FlipImage("player_dead_right"  , "player_dead_left"  , 6);
	FlipImage("player_fall_right"  , "player_fall_left"  , 5);
	FlipImage("player_idle_right"  , "player_idle_left"  , 5);
	FlipImage("player_jump_right"  , "player_jump_left"  , 5);
	FlipImage("player_roll_right"  , "player_roll_left"  , 7); 
	FlipImage("player_run_right"   , "player_run_left"   , 10);

	FlipImage("enemy_dragon_aim_in_air_right", "enemy_dragon_aim_in_air_left");

	FlipAtlas("player_run_vfx_left", "player_run_vfx_right");

	FlipAtlas("sword_left"							   , "sword_right"							);
	FlipAtlas("enemy_hornet_aim_left"				   , "enemy_hornet_aim_right"               );			
	FlipAtlas("enemy_hornet_dash_in_air_left"		   , "enemy_hornet_dash_in_air_right"       );				 
	FlipAtlas("enemy_hornet_dash_on_floor_left"	   , "enemy_hornet_dash_on_floor_right"		);				
	FlipAtlas("enemy_hornet_fall_left"				   , "enemy_hornet_fall_right"				);								
	FlipAtlas("enemy_hornet_idle_left"				   , "enemy_hornet_idle_right"              );								
	FlipAtlas("enemy_hornet_jump_left"				   , "enemy_hornet_jump_right"              );								
	FlipAtlas("enemy_hornet_run_left"			       , "enemy_hornet_run_right"               );									
	FlipAtlas("enemy_hornet_squat_left"			   , "enemy_hornet_squat_right"             );								
	FlipAtlas("enemy_hornet_throw_barb_left"		   , "enemy_hornet_throw_barb_right"        );
	FlipAtlas("enemy_hornet_throw_silk_left"		   , "enemy_hornet_throw_silk_right"        );
	FlipAtlas("enemy_hornet_throw_sword_left"		   , "enemy_hornet_throw_sword_right"       );
	FlipAtlas("enemy_hornet_vfx_dash_in_air_left"	   , "enemy_hornet_vfx_dash_in_air_right"   );
	FlipAtlas("enemy_hornet_vfx_dash_on_floor_left"   , "enemy_hornet_vfx_dash_on_floor_right" );

	FlipAtlas("enemy_dragon_aim_right"		, "enemy_dragon_aim_left"			);
	FlipAtlas("enemy_dragon_attack_right"	, "enemy_dragon_attack_left"		);
	FlipAtlas("enemy_dragon_dash_right"	, "enemy_dragon_dash_left"			);
	FlipAtlas("enemy_dragon_dead_right"	, "enemy_dragon_dead_left"			);
	FlipAtlas("enemy_dragon_fall_right"	, "enemy_dragon_fall_left"			);
	FlipAtlas("enemy_dragon_fire_right"	, "enemy_dragon_fire_left"			);
	FlipAtlas("enemy_dragon_idle_right"	, "enemy_dragon_idle_left"			);
	FlipAtlas("enemy_dragon_jump_right"	, "enemy_dragon_jump_left"			);
	FlipAtlas("enemy_dragon_roll_right"	, "enemy_dragon_roll_left"			);
	FlipAtlas("enemy_dragon_run_right"		, "enemy_dragon_run_left"			);
	FlipAtlas("enemy_dragon_vfx_fire_right", "enemy_dragon_vfx_fire_left"		);

	Utility::LoadAudio(_T(R"(resource\audio\menu_bgm_1.mp3)")				  , _T("menu_bgm_1"));
	Utility::LoadAudio(_T(R"(resource\audio\menu_bgm_2.mp3)")				  , _T("menu_bgm_2"));
	Utility::LoadAudio(_T(R"(resource\audio\menu_bgm_3.mp3)")				  , _T("menu_bgm_3"));
	Utility::LoadAudio(_T(R"(resource\audio\menu_bgm_4.mp3)")				  , _T("menu_bgm_4"));
	Utility::LoadAudio(_T(R"(resource\audio\blurred_screen.mp3)")			  , _T("blurred_screen"));
	Utility::LoadAudio(_T(R"(resource\audio\game_bgm_1.mp3)")			      , _T("game_bgm_1"));
	Utility::LoadAudio(_T(R"(resource\audio\game_bgm_2.mp3)")				  , _T("game_bgm_2"));
	Utility::LoadAudio(_T(R"(resource\audio\game_bgm_3.mp3)")				  , _T("game_bgm_3"));
	Utility::LoadAudio(_T(R"(resource\audio\game_bgm_4.mp3)")				  , _T("game_bgm_4"));
	Utility::LoadAudio(_T(R"(resource\audio\game_bgm_5.mp3)")				  , _T("game_bgm_5"));
	Utility::LoadAudio(_T(R"(resource\audio\game_bgm_6.mp3)")				  , _T("game_bgm_6"));
	Utility::LoadAudio(_T(R"(resource\audio\game_bgm_7.mp3)")                 , _T("game_bgm_7"));
	Utility::LoadAudio(_T(R"(resource\audio\game_bgm_8.mp3)")				  , _T("game_bgm_8"));
	Utility::LoadAudio(_T(R"(resource\audio\game_bgm_9.mp3)")				  ,	_T("game_bgm_9"));
	Utility::LoadAudio(_T(R"(resource\audio\barb_break.mp3)")			      , _T("barb_break"));
	Utility::LoadAudio(_T(R"(resource\audio\bullet_time.mp3)")				  , _T("bullet_time"));
	Utility::LoadAudio(_T(R"(resource\audio\enemy_hornet_dash.mp3)")		  , _T("enemy_hornet_dash"));
	Utility::LoadAudio(_T(R"(resource\audio\enemy_hornet_hurt_1.mp3)")		  , _T("enemy_hornet_hurt_1"));
	Utility::LoadAudio(_T(R"(resource\audio\enemy_hornet_hurt_2.mp3)")		  , _T("enemy_hornet_hurt_2"));
	Utility::LoadAudio(_T(R"(resource\audio\enemy_hornet_hurt_3.mp3)")		  , _T("enemy_hornet_hurt_3"));
	Utility::LoadAudio(_T(R"(resource\audio\enemy_hornet_run.mp3)")			  , _T("enemy_hornet_run"));
	Utility::LoadAudio(_T(R"(resource\audio\enemy_hornet_throw_barbs.mp3)")   , _T("enemy_hornet_throw_barbs"));
	Utility::LoadAudio(_T(R"(resource\audio\enemy_hornet_throw_silk.mp3)")    , _T("enemy_hornet_throw_silk"));
	Utility::LoadAudio(_T(R"(resource\audio\enemy_hornet_throw_sword.mp3)")   , _T("enemy_throw_sword"));
	Utility::LoadAudio(_T(R"(resource\audio\player_attack_1.mp3)")			  , _T("player_attack_1"));
	Utility::LoadAudio(_T(R"(resource\audio\player_attack_2.mp3)")			  , _T("player_attack_2"));
	Utility::LoadAudio(_T(R"(resource\audio\player_attack_3.mp3)")			  , _T("player_attack_3"));
	Utility::LoadAudio(_T(R"(resource\audio\player_dead.mp3)")				  , _T("player_dead"));
	Utility::LoadAudio(_T(R"(resource\audio\player_hurt.mp3)")				  , _T("player_hurt"));
	Utility::LoadAudio(_T(R"(resource\audio\player_jump.mp3)")				  , _T("player_jump"));
	Utility::LoadAudio(_T(R"(resource\audio\player_land.mp3)")				  , _T("player_land"));
	Utility::LoadAudio(_T(R"(resource\audio\player_roll.mp3)")				  , _T("player_roll"));
	Utility::LoadAudio(_T(R"(resource\audio\player_run.mp3)")				  , _T("player_run"));

	AddFontResourceEx(_T("resource/ttf/IPix.ttf"), FR_PRIVATE, NULL);
	settextstyle(20, 0, _T("IPix"));
	setbkmode(TRANSPARENT);
}

Atlas* ResourcesManager::FindAtlas(const string& id)
{
	const auto& iter = atlasPool.find(id);
	if (iter == atlasPool.end())
	{
		return nullptr;
	}
	return iter->second;
}

IMAGE* ResourcesManager::FindImage(const string& id)
{
	const auto& iter = imagePool.find(id);
	if (iter == imagePool.end())
	{
		return nullptr;
	}
	return iter->second;
}

void ResourcesManager::FlipImage(IMAGE* srcImage, IMAGE* dstImage, int num)
{
	int width = srcImage->getwidth();
	int height = srcImage->getheight();
	int widthFrame = width / num;
	Resize(dstImage, width, height);
	DWORD* srcBuffer = GetImageBuffer(srcImage);
	DWORD* dstBuffer = GetImageBuffer(dstImage);
	for (int i = 0; i < num ; i++)
	{
		int x_left = i * widthFrame;
		int x_right = (i + 1) * widthFrame;
		for (int y = 0; y < height; y++)
		{
			for (int x = x_left; x < x_right; x++)
			{
				int srcIndex = y * width + x;
				int dstIndex = y * width + x_right - (x - x_left);
				dstBuffer[dstIndex] = srcBuffer[srcIndex];
			}
		}
	}
}

void ResourcesManager::FlipImage(const string& srcId, const  string& dstId, int num)
{
	IMAGE* srcImage = imagePool[srcId];
	IMAGE* dstImage = new IMAGE();
	FlipImage(srcImage, dstImage, num);
	imagePool[dstId] = dstImage;
}

void ResourcesManager::FlipAtlas(const string& srcId, const  string& dstId)
{
	Atlas* srcAtlas = atlasPool[srcId];
	Atlas* dstAtlas = new Atlas();
	for (int i = 0; i < srcAtlas->GetSize(); i++)
	{
		IMAGE flippedImg;
		FlipImage(srcAtlas->get_image(i), &flippedImg);
		dstAtlas->add_image(flippedImg);
	}
	atlasPool[dstId] = dstAtlas;
}
