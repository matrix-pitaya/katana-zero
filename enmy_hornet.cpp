#include"enemy_hornet.h"
#include"collision_manager.h"
#include"resources_manager.h"
#include"enemy_hornet_state_nodes.h"
using namespace std;
EnemyHornet::EnemyHornet()
{
	hp = 15;
	isFacingLeft = true;
	position = { 1050,200 };
	logicHeight = 150;

	hitBox->SetSize({ 50,80 });
	hurtBox->SetSize({ 100,180 });

	hitBox->SetDstLayer(CollisionLayer::Player);
	hitBox->SetSrcLayer(CollisionLayer::None);

	hurtBox->SetDstLayer(CollisionLayer::None);
	hurtBox->SetSrcLayer(CollisionLayer::Enemy);

	hurtBox->SetOnCollide([&]() {DecreaseHp(); });

	collisionBoxSilk = CollisionManager::Instance()->CreateCollisionBox();
	collisionBoxSilk->SetDstLayer(CollisionLayer::Player);
	collisionBoxSilk->SetSrcLayer(CollisionLayer::None);
	collisionBoxSilk->SetSize({ 225,225 });
	collisionBoxSilk->SetEnabled(false);

	{
		AnimationGroup& animation_aim = animationPool["aim"];
		Animation& animation_left = animation_aim.left;
		animation_left.set_loop(false);
		animation_left.set_interval(0.05f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_aim_left"));

		Animation& animation_right = animation_aim.right;
		animation_right.set_loop(false);
		animation_right.set_interval(0.05f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_aim_right"));
	}
	{
		AnimationGroup& animation_dash_in_air = animationPool["dash_in_air"];
		Animation& animation_left = animation_dash_in_air.left;
		animation_left.set_loop(true);
		animation_left.set_interval(0.05f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_dash_in_air_left"));

		Animation& animation_right = animation_dash_in_air.right;
		animation_right.set_loop(true);
		animation_right.set_interval(0.05f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_dash_in_air_right"));
	}
	{
		AnimationGroup& animation_dash_on_floor = animationPool["dash_on_floor"];
		Animation& animation_left = animation_dash_on_floor.left;
		animation_left.set_loop(true);
		animation_left.set_interval(0.05f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_dash_on_floor_left"));

		Animation& animation_right = animation_dash_on_floor.right;
		animation_right.set_loop(true);
		animation_right.set_interval(0.05f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_dash_on_floor_right"));
	}
	{
		AnimationGroup& animation_fall = animationPool["fall"];
		Animation& animation_left = animation_fall.left;
		animation_left.set_loop(true);
		animation_left.set_interval(0.1f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_fall_left"));

		Animation& animation_right = animation_fall.right;
		animation_right.set_loop(true);
		animation_right.set_interval(0.1f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_fall_right"));
	}
	{
		AnimationGroup& idleAnimation = animationPool["idle"];
		Animation& animation_left = idleAnimation.left;
		animation_left.set_loop(true);
		animation_left.set_interval(0.1f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_idle_left"));

		Animation& animation_right = idleAnimation.right;
		animation_right.set_loop(true);
		animation_right.set_interval(0.1f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_idle_right"));
	}
	{
		AnimationGroup& animation_jump = animationPool["jump"];
		Animation& animation_left = animation_jump.left;
		animation_left.set_loop(false);
		animation_left.set_interval(0.1f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_jump_left"));

		Animation& animation_right = animation_jump.right;
		animation_right.set_loop(false);
		animation_right.set_interval(0.1f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_jump_right"));
	}
	{
		AnimationGroup& animation_run = animationPool["run"];
		Animation& animation_left = animation_run.left;
		animation_left.set_loop(true);
		animation_left.set_interval(0.05f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_run_left"));

		Animation& animation_right = animation_run.right;
		animation_right.set_loop(true);
		animation_right.set_interval(0.05f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_run_right"));
	}
	{
		AnimationGroup& animation_squat = animationPool["squat"];
		Animation& animation_left = animation_squat.left;
		animation_left.set_loop(false);
		animation_left.set_interval(0.05f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_squat_left"));

		Animation& animation_right = animation_squat.right;
		animation_right.set_loop(false);
		animation_right.set_interval(0.05f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_squat_right"));
	}
	{
		AnimationGroup& animation_throw_barb = animationPool["throw_barb"];
		Animation& animation_left = animation_throw_barb.left;
		animation_left.set_loop(false);
		animation_left.set_interval(0.1f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_throw_barb_left"));

		Animation& animation_right = animation_throw_barb.right;
		animation_right.set_loop(false);
		animation_right.set_interval(0.1f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_throw_barb_right"));
	}
	{
		AnimationGroup& animation_throw_silk = animationPool["throw_silk"];
		Animation& animation_left = animation_throw_silk.left;
		animation_left.set_loop(false);
		animation_left.set_interval(0.1f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_throw_silk_left"));

		Animation& animation_right = animation_throw_silk.right;
		animation_right.set_loop(false);
		animation_right.set_interval(0.1f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_throw_silk_right"));
	}
	{
		AnimationGroup& animation_throw_sword = animationPool["ThrowSword"];
		Animation& animation_left = animation_throw_sword.left;
		animation_left.set_loop(false);
		animation_left.set_interval(0.05f);
		animation_left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_throw_sword_left"));

		Animation& animation_right = animation_throw_sword.right;
		animation_right.set_loop(false);
		animation_right.set_interval(0.05f);
		animation_right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		animation_right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_throw_sword_right"));
	}

	animationSilk.set_loop(false);
	animationSilk.set_interval(0.1f);
	animationSilk.set_anchor_mode(Animation::AnchorMode::Centered);
	animationSilk.add_frame(ResourcesManager::Instance()->FindAtlas("silk"));

	animationDashInAirVfx.left.set_loop(false);
	animationDashInAirVfx.left.set_interval(0.1f);
	animationDashInAirVfx.left.set_anchor_mode(Animation::AnchorMode::Centered);
	animationDashInAirVfx.left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_vfx_dash_in_air_left"));
	animationDashInAirVfx.right.set_loop(false);
	animationDashInAirVfx.right.set_interval(0.1f);
	animationDashInAirVfx.right.set_anchor_mode(Animation::AnchorMode::Centered);
	animationDashInAirVfx.right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_vfx_dash_in_air_right"));

	animationDashOnFloorVfx.left.set_loop(false);
	animationDashOnFloorVfx.left.set_interval(0.1f);
	animationDashOnFloorVfx.left.set_anchor_mode(Animation::AnchorMode::BottomCentered);
	animationDashOnFloorVfx.left.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_vfx_dash_on_floor_left"));
	animationDashOnFloorVfx.right.set_loop(false);
	animationDashOnFloorVfx.right.set_interval(0.1f);
	animationDashOnFloorVfx.right.set_anchor_mode(Animation::AnchorMode::BottomCentered);
	animationDashOnFloorVfx.right.add_frame(ResourcesManager::Instance()->FindAtlas("enemy_hornet_vfx_dash_on_floor_right"));

	stateMachine.RegisterState("aim", new EnemyHorentAimState(this));
	stateMachine.RegisterState("dash_in_air", new EnemyHorentDashAirState(this));
	stateMachine.RegisterState("dash_on_floor", new EnemyHorentDashOnFloorState(this));
	stateMachine.RegisterState("dead", new EnemyHorentDeadState(this));
	stateMachine.RegisterState("fall", new EnemyHorentFallState(this));
	stateMachine.RegisterState("idle", new EnemyHorentIdleState(this));
	stateMachine.RegisterState("jump", new EnemyHorentJumpState(this));
	stateMachine.RegisterState("run", new EnemyHorentRunState(this));
	stateMachine.RegisterState("squat", new EnemyHorentSquatState(this));
	stateMachine.RegisterState("throw_barb", new EnemyHorentThrowBarbState(this));
	stateMachine.RegisterState("throw_silk", new EnemyHorentThrowSilkState(this));
	stateMachine.RegisterState("ThrowSword", new EnemyHorentThrowSwordState(this));

	stateMachine.SetEntry("fall");
}
EnemyHornet::~EnemyHornet()
{
	CollisionManager::Instance()->DestroyCollisionBox(collisionBoxSilk);

	stateMachine.DestroyState("aim");
	stateMachine.DestroyState("dash_in_air");
	stateMachine.DestroyState("dash_on_floor");
	stateMachine.DestroyState("dead");
	stateMachine.DestroyState("fall");
	stateMachine.DestroyState("idle");
	stateMachine.DestroyState("jump");
	stateMachine.DestroyState("run");
	stateMachine.DestroyState("squat");
	stateMachine.DestroyState("throw_barb");
	stateMachine.DestroyState("throw_silk");
	stateMachine.DestroyState("ThrowSword");

	for (Barb*& barb : barbList)
	{
		delete barb;
		barb = nullptr;
	}
	for (Sword*& sword : swordList)
	{
		delete sword;
		sword = nullptr;
	}

	Utility::StopAudio(_T("enemy_hornet_run"));
}
void EnemyHornet::OnUpdata(float delta)
{
	if (velocity.x != 0)
	{
		isFacingLeft = (velocity.x < 0);
	}

	Character::OnUpdata(delta);

	hitBox->SetPosition(GetLogicCenter());

	if (isThrowingSilk)
	{
		collisionBoxSilk->SetPosition(GetLogicCenter());
		animationSilk.SetPosition(GetLogicCenter());
		animationSilk.OnUpdata(delta);
	}

	if (isDashingInAir || isDashingOnFloor)
	{
		currentDashAnimation->SetPosition(isDashingInAir ? GetLogicCenter() : position);
		currentDashAnimation->OnUpdata(delta);
	}

	for (Barb*& barb : barbList)
	{
		barb->OnUpdata(delta);
	}
	for (Sword*& sword : swordList)
	{
		sword->OnUpdata(delta);
	}

	barbList.erase(remove_if(barbList.begin(), barbList.end(), [](Barb*& barb)
		{
			bool can_remove = !barb->CheckValid();
			if (can_remove)
			{
				delete barb;
				barb = nullptr;
			}
			return can_remove;
		}
	), barbList.end());

	swordList.erase(remove_if(swordList.begin(), swordList.end(), [](Sword*& sword)
		{
			bool canRemove = !sword->CheckValid();
			if (canRemove)
			{
				delete sword;
				sword = nullptr;
			}
			return canRemove;
		}), swordList.end());
}
void EnemyHornet::OnRender()
{
	for (Barb*& barb : barbList)
	{
		barb->OnRender();
	}
	for (Sword*& sword : swordList)
	{
		sword->OnRender();
	}

	Character::OnRender();

	if(isThrowingSilk)
	{
		animationSilk.OnRender();
	}
	if (isDashingInAir || isDashingOnFloor)
	{
		currentDashAnimation->OnRender();;
	}
}
void EnemyHornet::OnHurt()
{
	switch (Utility::RandomRange(1, 3))
	{
	case 1:
		Utility::PlayAudio(_T("enemy_hornet_hurt_1"), false);
		break;
	case 2:
		Utility::PlayAudio(_T("enemy_hornet_hurt_2"), false);
		break;
	case 3:
		Utility::PlayAudio(_T("enemy_hornet_hurt_3"), false);
		break;
	}
	Character::OnHurt();
}
void EnemyHornet::SetIsFacingLeft(bool flag)
{
	isFacingLeft = flag;
}
bool EnemyHornet::GetIsFacingLeft()
{
	return isFacingLeft;
}
void EnemyHornet::SetDashingInAir(bool flag)
{
	isDashingInAir = flag;
}
bool EnemyHornet::GetDashingInAir()
{
	return isDashingInAir;
}
void EnemyHornet::SetDashingOnFloor(bool flag)
{
	isDashingOnFloor = flag;
}
bool EnemyHornet::GetDashingOnFloor()
{
	return isDashingOnFloor;
}
void EnemyHornet::SetThrowingSilk(bool flag)
{
	isThrowingSilk = flag;
}
bool EnemyHornet::GetThrowingSilk()
{
	return isThrowingSilk;
}
void EnemyHornet::ThrowBarbs()
{
	int num_new_barb = Utility::RandomRange(3, 6);
	if (barbList.size() > 10)
	{
		num_new_barb = 1;
	}
	int width_new_barb = getwidth() / num_new_barb;
	for (int i = 0; i < num_new_barb; i++)
	{
		Barb* new_bar = new Barb();
		int rand_x = Utility::RandomRange(i * width_new_barb, (i + 1) * width_new_barb);
		int rand_y = Utility::RandomRange(250, 500);
		new_bar->SetPosition({ (float)rand_x, (float)rand_y });
		barbList.push_back(new_bar);
	}
}
void EnemyHornet::ThrowSword()
{
	Sword* new_sword = new Sword(GetLogicCenter(), isFacingLeft);
	swordList.push_back(new_sword);
}
void EnemyHornet::OnDash()
{
	if (isDashingInAir)
	{
		currentDashAnimation = isFacingLeft ? &animationDashInAirVfx.left : &animationDashInAirVfx.right;
	}
	else
	{
		currentDashAnimation = isFacingLeft ? &animationDashOnFloorVfx.left : &animationDashOnFloorVfx.right;
	}

	currentDashAnimation->Reset();
}
void EnemyHornet::OnThrowSilk()
{
	animationSilk.Reset();
}
CollisionBox* EnemyHornet::GetSilkCollionBox()
{
	return collisionBoxSilk;
}