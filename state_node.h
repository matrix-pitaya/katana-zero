#pragma once
class StateNode
{
public:
	virtual void OnEnter() = 0;
	virtual void OnUpdata(float delta) = 0;
	virtual void OnExit() = 0;
};