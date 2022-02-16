#pragma once
#include "State.h"

class SettingsState : public State
{
private:
	enum class DifficultyText
	{
		Easy = 0, 
		Medium, 
		Hard, 
		Impossible,
	};

	enum class SettingsUIText
	{
		Title, 
		
	};

	std::map<DifficultyText, sf::Text> mDifficultyText;
	std::map<SettingsUIText, sf::Text> mSettingsText;
	
	int mSettingsIndex;
	bool mKeyUp;

	class Game& game;

public:
	SettingsState();
	~SettingsState();
	void InitUIText();
	virtual void Init() override;
	virtual void Update(const float& dt) override;
	virtual void HandleInput(sf::Event& event) override;
	virtual void Render(const float& dt) override;

};