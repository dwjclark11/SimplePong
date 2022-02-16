#include "stdafx.h"
#include "MenuState.h"
#include "GameState.h"
#include "Game.h"

MenuState::MenuState()
	: mTextIndex(0)
	, mKeyUp(true)
{

}

void MenuState::Init()
{
	mFontHolder.load(Fonts::ID::Main, "Fonts/Main.ttf");
	mFontHolder.load(Fonts::ID::MenuTitle, "Fonts/ASTONISHED.ttf");
	mTextureHolder.load(Textures::ID::MenuBackground, "Textures/space.png");
	
	
	sf::Text startText;
	startText.setCharacterSize(30);
	startText.setFont(mFontHolder.get(Fonts::ID::Main));
	startText.setFillColor(sf::Color::White);
	startText.setString("START");
	startText.setPosition(Game::GetInstance().GetGameWindow()->getSize().x / 2.f, Game::GetInstance().GetGameWindow()->getSize().y / 2.f);
	
	sf::Text settingsText;
	settingsText.setCharacterSize(30);
	settingsText.setFont(mFontHolder.get(Fonts::ID::Main));
	settingsText.setFillColor(sf::Color::White);
	settingsText.setString("SETTINGS");
	settingsText.setPosition(startText.getPosition().x, startText.getPosition().y + startText.getGlobalBounds().height * 2);

	sf::Text quitText;
	quitText.setCharacterSize(30);
	quitText.setFont(mFontHolder.get(Fonts::ID::Main));
	quitText.setFillColor(sf::Color::White);
	quitText.setString("QUIT");
	quitText.setPosition(settingsText.getPosition().x, settingsText.getPosition().y + settingsText.getGlobalBounds().height * 2);


	sf::Text menuTitle;
	menuTitle.setCharacterSize(120);
	menuTitle.setFont(mFontHolder.get(Fonts::ID::MenuTitle));
	menuTitle.setFillColor(sf::Color::White);
	menuTitle.setString("SPACE PONG BATTLE");
	menuTitle.setPosition(startText.getPosition().x, startText.getPosition().y - settingsText.getGlobalBounds().height * 8);



	mMenuText.insert(std::make_pair(MenuState::MenuText::Start, std::move(startText)));
	mMenuText.insert(std::make_pair(MenuState::MenuText::Settings, std::move(settingsText)));
	mMenuText.insert(std::make_pair(MenuState::MenuText::Quit, std::move(quitText)));
	mMenuText.insert(std::make_pair(MenuState::MenuText::MenuTitle, std::move(menuTitle)));
	
	mBackgroundSprite.setTexture(mTextureHolder.get(Textures::ID::MenuBackground));

	mMusicPlayer.setVolume(30);
	mMusicPlayer.play(Music::ID::MenuTheme);
}

void MenuState::HandleInput(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && mKeyUp)
	{
		if (mTextIndex == 0)
		{
			mSoundPlayer.play(SoundEffect::ButtonSelect);
			Game::GetInstance().GetStateMachine()->AddState(std::make_unique<GameState>());
			Game::GetInstance().GetStateMachine()->ChangeState();
		}
		else if (mTextIndex == 2)
		{
			mSoundPlayer.play(SoundEffect::ButtonCancel);
			Game::GetInstance().GetGameWindow()->close();
		}
		mKeyUp = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && mKeyUp)
	{
		mTextIndex--;
		mSoundPlayer.play(SoundEffect::ButtonUp);

		if (mTextIndex < 0)
			mTextIndex = 2;
		
		mKeyUp = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mKeyUp)
	{
		mTextIndex++;
		mSoundPlayer.play(SoundEffect::ButtonUp);
		if (mTextIndex > 2)
			mTextIndex = 0;
		mKeyUp = false;
	}

	switch (event.type)
	{
	case sf::Event::KeyReleased:
			mKeyUp = true;
	}
}

void MenuState::UpdateUIText()
{
	for (auto& text : mMenuText)
	{
		if (text.first == static_cast<MenuState::MenuText>(mTextIndex))
			text.second.setFillColor(sf::Color::Red);
		else
			text.second.setFillColor(sf::Color::White);
	}

}

void MenuState::Update(const float& dt)
{
	UpdateUIText();
	mSoundPlayer.removeStoppedSounds();
}

void MenuState::Render(const float& dt)
{
	Game::GetInstance().GetGameWindow()->draw(mBackgroundSprite);

	for (auto& text : mMenuText)
		Game::GetInstance().GetGameWindow()->draw(text.second);
}
