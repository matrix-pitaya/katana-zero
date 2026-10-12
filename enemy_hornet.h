#pragma once
#include"character.h"
#include"barb.h"
#include"sword.h"
#include<vector>
using namespace std;
class EnemyHornet:public Character
{
public:
	EnemyHornet();
	~EnemyHornet();

	void OnUpdata(float delta) override;
	void OnRender() override;
	void OnHurt() override;

	void SetIsFacingLeft(bool flag);
	bool GetIsFacingLeft();
	void SetDashingInAir(bool flag);
	bool GetDashingInAir();
	void SetDashingOnFloor(bool flag);
	bool GetDashingOnFloor();
	void SetThrowingSilk(bool flag);
	bool GetThrowingSilk();
	CollisionBox* GetSilkCollionBox();

	void ThrowBarbs();
	void ThrowSword();

	void OnDash();
	void OnThrowSilk();
private:
	bool isThrowingSilk = false;
	bool isDashingInAir = false;
	bool isDashingOnFloor = false;

	Animation animationSilk;
	AnimationGroup animationDashInAirVfx;
	AnimationGroup animationDashOnFloorVfx;
	Animation* currentDashAnimation = nullptr;

	vector<Barb*> barbList;
	vector<Sword*> swordList;
	CollisionBox* collisionBoxSilk = nullptr;
};