#include "stdafx.h"
#include "StateMachine.h"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
	
}

void StateMachine::AddState(StateRef newState, bool isReplacing)
{
	mIsAdding = true;
	mIsReplacing = mIsReplacing;

	mNewState = std::move(newState);
}

void StateMachine::RemoveState()
{
	mIsRemoving = true;
}

void StateMachine::ChangeState()
{
	if (mIsRemoving && !mStates.empty())
	{
		mStates.pop();

		if (!mStates.empty())
		{
			mStates.top()->Resume();
		}

		mIsRemoving = false;
	}

	if (mIsAdding)
	{
		if (!mStates.empty())
		{
			if (mIsReplacing)
			{
				mStates.pop();
			}
			else
			{
				mStates.top()->Pause();
			}
		}

		mStates.push(std::move(mNewState));
		mStates.top()->Init();
		mIsAdding = false;
	}
}

void StateMachine::Update(float dt)
{
	if (!mStates.empty())
	{
		mStates.top()->Update(dt);
	}
}

void StateMachine::HandleInputs()
{
	if (!mStates.empty())
	{
		mStates.top()->HandleInput();
	}
}

StateRef& StateMachine::GetCurrentState()
{
	return mStates.top();
}