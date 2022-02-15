#pragma once

#include "State.h"


typedef std::unique_ptr<State> StateRef;

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void AddState(StateRef newState, bool isReplacing = true);
	void RemoveState();

	void ChangeState();
	void Update(float dt);
	void HandleInputs();
	
	StateRef& GetCurrentState();

private:
	std::stack<StateRef> mStates;
	StateRef mNewState;
	bool mIsAdding;
	bool mIsRemoving;
	bool mIsReplacing;
};
