#include "stdafx.h"
#include "SettingsState.h"
#include "MenuState.h"
#include "Game.h"

SettingsState::SettingsState()
	: mSettingsIndex(0)
	, mKeyUp(true)
	, game(Game::GetInstance())
{

}

SettingsState::~SettingsState()
{

}

void SettingsState::InitUIText()
{
	sf::Text settingsTitle;
	settingsTitle.setCharacterSize(120);
	settingsTitle.setFont(Game::GetInstance().GetFonts().get(Fonts::ID::Main));
	settingsTitle.setFillColor(sf::Color::White);
	settingsTitle.setString("SETTINGS");
	settingsTitle.setPosition(Game::GetInstance().GetGameWindow()->getSize().x / 2.f - settingsTitle.getGlobalBounds().width/2, Game::GetInstance().GetGameWindow()->getSize().y / 4.f);

	sf::Text easyText;
	easyText.setCharacterSize(30);
	easyText.setFont(Game::GetInstance().GetFonts().get(Fonts::ID::Main));
	easyText.setFillColor(sf::Color::White);
	easyText.setString("EASY");
	easyText.setPosition(Game::GetInstance().GetGameWindow()->getSize().x / 2.f - easyText.getGlobalBounds().width / 2, Game::GetInstance().GetGameWindow()->getSize().y / 2.5f);

	sf::Text mediumText;
	mediumText.setCharacterSize(30);
	mediumText.setFont(Game::GetInstance().GetFonts().get(Fonts::ID::Main));
	mediumText.setFillColor(sf::Color::White);
	mediumText.setString("MEDIUM");
	mediumText.setPosition(Game::GetInstance().GetGameWindow()->getSize().x / 2.f - mediumText.getGlobalBounds().width / 2, easyText.getPosition().y + mediumText.getGlobalBounds().height * 2);

	sf::Text hardText;
	hardText.setCharacterSize(30);
	hardText.setFont(Game::GetInstance().GetFonts().get(Fonts::ID::Main));
	hardText.setFillColor(sf::Color::White);
	hardText.setString("HARD");
	hardText.setPosition(Game::GetInstance().GetGameWindow()->getSize().x / 2.f - hardText.getGlobalBounds().width / 2, mediumText.getPosition().y + hardText.getGlobalBounds().height * 2);


	mSettingsText.insert(std::make_pair(SettingsState::SettingsUIText::Title, std::move(settingsTitle)));
	mDifficultyText.insert(std::make_pair(SettingsState::DifficultyText::Easy, std::move(easyText)));
	mDifficultyText.insert(std::make_pair(SettingsState::DifficultyText::Medium, std::move(mediumText)));
	mDifficultyText.insert(std::make_pair(SettingsState::DifficultyText::Hard, std::move(hardText)));
}

void SettingsState::Init()
{
	InitUIText();
}

void SettingsState::Update(const float& dt)
{
	for (auto& diffText : mDifficultyText)
	{
		if (diffText.first == static_cast<DifficultyText>(game.GetDifficulty()))
			diffText.second.setFillColor(sf::Color::Red);
		else if (diffText.first == static_cast<DifficultyText>(mSettingsIndex))
			diffText.second.setFillColor(sf::Color::Yellow);
		else
			diffText.second.setFillColor(sf::Color::White);
	}
}

void SettingsState::HandleInput(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && mKeyUp)
	{
		
		game.GetSoundPlayer().play(SoundEffect::ButtonSelect);
		game.SetGameDifficulty(static_cast<Game::GameDifficulty>(mSettingsIndex));
		
		mKeyUp = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && mKeyUp)
	{
		mSettingsIndex--;
		game.GetSoundPlayer().play(SoundEffect::ButtonUp);

		if (mSettingsIndex < 0)
			mSettingsIndex = 3;

		mKeyUp = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mKeyUp)
	{
		mSettingsIndex++;
		game.GetSoundPlayer().play(SoundEffect::ButtonUp);
		if (mSettingsIndex > 3)
			mSettingsIndex = 0;
		mKeyUp = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && mKeyUp)
	{
		game.GetSoundPlayer().play(SoundEffect::ButtonCancel);
		game.GetStateMachine()->AddState(std::make_unique<MenuState>());
		game.GetStateMachine()->ChangeState();
		mKeyUp = false;
	}


	switch (event.type)
	{
	case sf::Event::KeyReleased:
		mKeyUp = true;
	}
}

void SettingsState::Render(const float& dt)
{
	for (auto& uiText : mSettingsText)
	{
		Game::GetInstance().GetGameWindow()->draw(uiText.second);
	}

	for (auto& diffText : mDifficultyText)
	{
		Game::GetInstance().GetGameWindow()->draw(diffText.second);
	}
}
