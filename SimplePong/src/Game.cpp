#include "stdafx.h"
#include "Game.h"
#include "MenuState.h"

std::unique_ptr<Game> Game::mInstance = nullptr;


void Game::initWindow()
{
	mWindow.reset(new sf::RenderWindow(sf::VideoMode(1920, 1080), "Simple Pong", sf::Style::Fullscreen));
	mWindow->setFramerateLimit(60);
	mWindow->setVerticalSyncEnabled(true);
}

//void Game::initUI()
//{
//	mTopGUIBlock.setFillColor(sf::Color::Black);
//	mTopGUIBlock.setSize(sf::Vector2f(mWindow->getSize().x, 100.f));
//	mTopGUIBlock.setPosition(sf::Vector2f(mWindow->getPosition()));
//
//	mGoal.setFont(mFontB);
//	mGoal.setCharacterSize(100);
//	mGoal.setFillColor(sf::Color::Red);
//	mGoal.setString("mGoal!!");
//	mGoal.setPosition(mWindow->getSize().x / 1.75f- mGoal.getGlobalBounds().width, mWindow->getSize().y / 4);
//
//	mPlayer1Upgrade.setFont(mFont);
//	mPlayer1Upgrade.setCharacterSize(30);
//	mPlayer1Upgrade.setFillColor(sf::Color::Yellow);
//	mPlayer1Upgrade.setString("PLAYER 1 mUpgrade AVAILABLE");
//	mPlayer1Upgrade.setPosition(mWindow->getSize().x / 12, mWindow->getSize().y / 6);
//
//	mPlayer2Upgrade.setFont(mFont);
//	mPlayer2Upgrade.setCharacterSize(30);
//	mPlayer2Upgrade.setFillColor(sf::Color::Yellow);
//	mPlayer2Upgrade.setString("PLAYER 2 mUpgrade AVAILABLE");
//	mPlayer2Upgrade.setPosition(mPlayer1Upgrade.getPosition().x + 1200.f, mPlayer1Upgrade.getPosition().y);
//
//	mP1UpgradeType.setFont(mFont);
//	mP1UpgradeType.setCharacterSize(30);
//	mP1UpgradeType.setFillColor(sf::Color::Yellow);
//	mP1UpgradeType.setString("This Changes Based on mUpgrade");
//	mP1UpgradeType.setPosition(mPlayer1Upgrade.getPosition().x, mPlayer1Upgrade.getPosition().y);
//
//	mP2UpgradeType.setFont(mFont);
//	mP2UpgradeType.setCharacterSize(30);
//	mP2UpgradeType.setFillColor(sf::Color::Yellow);
//	mP2UpgradeType.setString("This Changes Based on mUpgrade");
//	mP2UpgradeType.setPosition(mPlayer1Upgrade.getPosition().x + 1200.f, mPlayer1Upgrade.getPosition().y);
//
//	mPlayer1Score.setFont(mFont);
//	mPlayer1Score.setCharacterSize(50);
//	mPlayer1Score.setFillColor(sf::Color::White);
//	mPlayer1Score.setString("SCORE: ");
//	mPlayer1Score.setPosition(mWindow->getSize().x / 16, 20.f);
//
//	mPlayer2Score.setFont(mFont);
//	mPlayer2Score.setCharacterSize(50);
//	mPlayer2Score.setFillColor(sf::Color::White);
//	mPlayer2Score.setString("SCORE: ");
//	mPlayer2Score.setPosition(mPlayer1Score.getPosition().x + 1500.f,  mPlayer1Score.getPosition().y);
//
//	mPlayer2Join.setFont(mFont);
//	mPlayer2Join.setCharacterSize(30);
//	mPlayer2Join.setFillColor(sf::Color::White);
//	mPlayer2Join.setString("PLAYER 2 PRESS SPACE\nTO JOIN GAME!");
//	mPlayer2Join.setPosition(mPlayer1Score.getPosition().x + 1150.f, mPlayer1Score.getPosition().y - 10);
//
//	mSpeedLevel.setFont(mFont);
//	mSpeedLevel.setCharacterSize(60);
//	mSpeedLevel.setFillColor(sf::Color::White);
//	mSpeedLevel.setString("Test ");
//	mSpeedLevel.setPosition((mWindow->getSize().x / 2.25) - mSpeedLevel.getGlobalBounds().width, mPlayer1Score.getPosition().y - 10.f);
//}


Game::Game()
{
	initWindow();
}

Game::~Game()
{
	
}

void Game::updateDeltaTime()
{
	mDt = mDtClock.restart().asSeconds();
}

void Game::update()
{
	updateDeltaTime();

	mGameStateMachine->Update(mDt);

	// Exit the Game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		mWindow->close();

}

void Game::HandleInputs()
{
	sf::Event event;
	while (mWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mWindow->close();
		}
	}

	mGameStateMachine->HandleInputs(event);
}

void Game::render()
{
	// Render the mWindow 
	mWindow->clear(sf::Color(0, 0, 0, 255));

	mGameStateMachine->Render(mDt);

	//if (mUpgradeAccepted1)
	//	mWindow->draw(mP1UpgradeType);

	//if (mUpgradeAccepted2)
	//	mWindow->draw(mP2UpgradeType);

	// Final Display
	mWindow->display();
}

void Game::run()
{
	mGameStateMachine = std::make_unique<StateMachine>();
	mGameStateMachine->AddState(std::make_unique<MenuState>());
	mGameStateMachine->ChangeState();

	
	while (mWindow->isOpen())
	{
		HandleInputs();
		update();
		render();
	}
}
