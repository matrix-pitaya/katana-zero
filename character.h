#pragma once
#include"vector2.h"
#include"animation.h"
#include"collision_box.h"
#include"state_machine.h"
#include<string>
#include<unordered_map>
#include<graphics.h>
using namespace std;
class Character
{
public:
	Character();
	virtual ~Character();

	virtual void OnInput(const ExMessage& msg);
	virtual void OnUpdata(float delta);
	virtual void OnRender();
	virtual void OnHurt();
	void SwitchState(const string& id);
	void SetAnimation(const string& id);

	void DecreaseHp();
	int GetHp();
	void SetPosition(const Vector2& position);
	Vector2& GetPosition();
	void SetVelocity(const Vector2& velocity);
	Vector2& get_velocity();
	Vector2 GetLogicCenter();
	void SetGravityEnabled(bool flag);
	CollisionBox* GetHitCollisionBox();
	CollisionBox* GetHurtCollisionBox();
	bool IsOnFloor();
	float GetFloorY();
	void MakeInvulnerable();

protected:
	struct AnimationGroup			
	{
		Animation left;		//朝向左的动画
		Animation right;	//朝向右的动画
	};

protected:
	const float FLOOR_Y = 620;		//地板的Y轴方向
	const float GRAVITY = 980 * 2;	//玩家所受重力大小

protected:
	int hp = 10;											//角色生命值
	Vector2 position;										//角色位置
	Vector2 velocity;										//角色速度
	float logicHeight = 0;									//角色逻辑高度
	bool isFacingLeft = true;								//当前角色朝向是否向左
	StateMachine stateMachine;								//角色状态机
	bool enableGravity = true;								//是否受到重力
	bool isInvulnerable = false;							//是否无效
	Timer invulnerableBlinkTimer;							//无敌状态闪烁定时器
	Timer invulnerableStatusTimer;							//无敌状态定时器
	bool isBlinkInvisable = false;							//是否为闪烁不可见帧
	CollisionBox* hitBox = nullptr;							//攻击碰撞箱
	CollisionBox* hurtBox = nullptr;						//受击碰撞箱
	AnimationGroup* currentAnimation = nullptr;				//当前播放动画
	unordered_map<string, AnimationGroup> animationPool;	//动画池
};