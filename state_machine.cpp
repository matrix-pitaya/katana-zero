#include"state_machine.h"
void StateMachine::OnUpdata(float delta)
{
	if (!currentState)
	{
		return;
	}
	currentState->OnUpdata(delta);
}

void StateMachine::SetEntry(const string& id)
{
	currentState = statePool[id];
	currentState->OnEnter();
}

void StateMachine::SwitchTo(const string& id)
{
	if (currentState)
	{
		currentState->OnExit();
	}
	currentState = statePool[id];
	if (currentState)
	{
		currentState->OnEnter();
	}
}

void StateMachine::RegisterState(const string& id, StateNode* state_node)
{
	statePool[id] = state_node;
}

void StateMachine::DestroyState(const string& id)
{
	const auto& iter = statePool.find(id);
	if (iter == statePool.end())
	{
		return;
	}
	delete iter->second;
	iter->second = nullptr;
}