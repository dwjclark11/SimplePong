#pragma once
#include "State.h"
#include "ResourceIdentifiers.h"
#include "SoundPlayer.h"
#include "MusicPlayer.h"

class MenuState : public State
{
private:
	enum class MenuText
	{
		Start = 0,
		Settings,
		Quit,
		MenuTitle,
	};

	std::map<MenuText, sf::Text> mMenuText;

	sf::Sprite mBackgroundSprite;
	
	int mTextIndex;
	bool mKeyUp;
	class Game& game;

public:
	MenuState();
	~MenuState() {}
	virtual void Init() override;
	virtual void HandleInput(sf::Event& event) override;

	void UpdateUIText();

	virtual void Update(const float& dt) override;
	virtual void Render(const float& dt) override;

};
