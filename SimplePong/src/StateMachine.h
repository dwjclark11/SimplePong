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
	void Update(const float& dt);
	void HandleInputs(sf::Event& event);
	void Render(const float& dt );
	
	StateRef& GetCurrentState();

private:
	std::stack<StateRef> mStates;
	StateRef mNewState;
	bool mIsAdding;
	bool mIsRemoving;
	bool mIsReplacing;
};
