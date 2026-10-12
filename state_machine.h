#pragma once
#include"state_node.h"
#include<string>
#include<unordered_map>
#include<graphics.h>
using namespace std;
class StateMachine
{
public:
	StateMachine() = default;
	~StateMachine() = default;

	void OnUpdata(float delta);

	void SetEntry(const string& id);
	void SwitchTo(const string& id);
	void RegisterState(const string& id, StateNode* state_node);
	void DestroyState(const string& id);

private:
	StateNode* currentState = nullptr;
	unordered_map<string, StateNode*> statePool;
};