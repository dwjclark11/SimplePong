#pragma once

class State
{
public:
	virtual ~State() {}
	virtual void Init() = 0;
	virtual void HandleInput() = 0;
	virtual void Update(const float& dt) = 0;
	virtual void Render(const float& dt) = 0;

	virtual void Pause() {}
	virtual void Resume() {}
};