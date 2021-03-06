#include "stdafx.h"
#include "GameState.h"
#include "Player.h"
#include "Game.h"


GameState::GameState()
	: game(Game::GetInstance())
	, mBallMultiplier(4)
{
	
}

GameState::~GameState()
{
	std::cout << "Destroying Game state!\n";
}

void GameState::InitResources()
{
	// Start GamePlay Music
	game.GetMusicPlayer().setVolume(15);
	game.GetMusicPlayer().play(Music::GamePlay);
}

void GameState::InitVariables()
{

	// Ball Direction Booleans and Variables

	mLevelUp = false;
	mCurrentSpeedLevel = 0;
	mBallDown = 1.f;
	mBallUp = -1.f;
	mSpeedDifficulty = 0;
	mMovementSpeed = 650.f;

	// Player Scored Variables
	mPlayer1Scored = false;
	mPlayer2Scored = false;
	mPScore1 = 0;
	mPScore2 = 0;
	mGoals = false;

	mTurnOnAI = true;
	mFlash = false;

	// Player Upgrades Booleans
	mP1UpgradeAvailable = false;
	mP2UpgradeAvailable = false;
	mUpgradeAccepted1 = false;
	mUpgradeAccepted2 = false;

	// Difficulty Booleans
	mEasy = false;
	mMedium = true;
	mHard = false;
	mImpossible = false;
}

void GameState::InitBall()
{
	Ball ball(50.f, &game.GetTextures().get(Textures::ID::Ball));
	ball.SetStartPosition(*Game::GetInstance().GetGameWindow());

	mBalls.push_back(ball);

	switch(game.GetDifficulty())
	{
	case Game::GameDifficulty::Easy:
		mBallMultiplier = 5;
		break;
	case Game::GameDifficulty::Medium:
		mBallMultiplier = 4;
		break;
	case Game::GameDifficulty::Hard:
		mBallMultiplier = 3;
		break;
	case Game::GameDifficulty::Impossible:
		mBallMultiplier = 2;
		break;

	}

}

void GameState::InitUITexts()
{
	sf::Text player1Score;
	player1Score.setFont(game.GetFonts().get(Fonts::ID::Main));
	player1Score.setCharacterSize(30);
	player1Score.setFillColor(sf::Color::White);
	player1Score.setString("SCORE: ");
	player1Score.setPosition(game.GetGameWindow()->getSize().x / 20, 20.f);

	sf::Text player2Score;
	player2Score.setFont(game.GetFonts().get(Fonts::ID::Main));
	player2Score.setCharacterSize(30);
	player2Score.setFillColor(sf::Color::White);
	player2Score.setString("SCORE: ");
	player2Score.setPosition(player1Score.getPosition().x + 1500.f, player1Score.getPosition().y);

	sf::Text goal;
	goal.setFont(game.GetFonts().get(Fonts::ID::Goal));
	goal.setCharacterSize(100);
	goal.setFillColor(sf::Color::White);
	goal.setString("GOAL!!");
	goal.setPosition(game.GetGameWindow()->getSize().x / 2.5, game.GetGameWindow()->getSize().y / 4);

	sf::Text player2Join;
	player2Join.setFont(game.GetFonts().get(Fonts::ID::Main));
	player2Join.setCharacterSize(30);
	player2Join.setFillColor(sf::Color::White);
	player2Join.setString("PLAYER 2 PRESS SPACE\nTO JOIN GAME!");
	player2Join.setPosition(player1Score.getPosition().x + 1150.f, player1Score.getPosition().y - 10.f);

	sf::Text speedLevel;
	speedLevel.setFont(game.GetFonts().get(Fonts::ID::Main));
	speedLevel.setCharacterSize(60);
	speedLevel.setFillColor(sf::Color::White);
	speedLevel.setString("SPEED LEVEL: ");
	speedLevel.setPosition((game.GetGameWindow()->getSize().x / 2.25) - speedLevel.getGlobalBounds().width, player1Score.getPosition().y - 10.f);

	sf::Text player1Upgrade;
	player1Upgrade.setFont(game.GetFonts().get(Fonts::ID::Main));
	player1Upgrade.setCharacterSize(30);
	player1Upgrade.setFillColor(sf::Color::White);
	player1Upgrade.setString("PLAYER 1: Upgrade Available!");
	player1Upgrade.setPosition(Game::GetInstance().GetGameWindow()->getSize().x / 12, Game::GetInstance().GetGameWindow()->getSize().y / 6);

	sf::Text player2Upgrade;
	player2Upgrade.setFont(game.GetFonts().get(Fonts::ID::Main));
	player2Upgrade.setCharacterSize(30);
	player2Upgrade.setFillColor(sf::Color::White);
	player2Upgrade.setString("PLAYER 2: Upgrade Available!");
	player2Upgrade.setPosition(player1Upgrade.getPosition().x + 1200.f, player1Upgrade.getPosition().y);


	mUIText.insert(std::make_pair(GameState::UIText::Player1_Score, std::move(player1Score)));
	mUIText.insert(std::make_pair(GameState::UIText::Player2_Score, std::move(player2Score)));
	mUIText.insert(std::make_pair(GameState::UIText::SpeedLevel, std::move(speedLevel)));
	
	mGameText.insert(std::make_pair(GameState::GameText::Goal, std::move(goal)));
	mGameText.insert(std::make_pair(GameState::GameText::Player2_Join, std::move(player2Join)));
	mGameText.insert(std::make_pair(GameState::GameText::Player1_Upgrade, std::move(player1Upgrade)));
	mGameText.insert(std::make_pair(GameState::GameText::Player2_Upgrade, std::move(player2Upgrade)));
}

void GameState::Init()
{
	
	mTopGUIBlock.setFillColor(sf::Color::Black);
	mTopGUIBlock.setSize(sf::Vector2f(Game::GetInstance().GetGameWindow()->getSize().x, 100.f));
	mTopGUIBlock.setPosition(sf::Vector2f(Game::GetInstance().GetGameWindow()->getPosition()));

	InitVariables();
	InitResources();
	InitBall();
	InitUITexts();
	// Init Player A
	mPlayerA = std::make_unique<Player>(
		50.f, Game::GetInstance().GetGameWindow()->getSize().y / 2.f, 
		Game::GetInstance().GetGameWindow()->getSize().y / 1.f, 
		sf::Color::White, 
		&game.GetTextures().get(Textures::ID::Player1Paddle), false);

	// Init Player B
	mPlayerB = std::make_unique<Player>(
		game.GetGameWindow()->getSize().x - 150.f, 
		game.GetGameWindow()->getSize().y / 2.f, 
		game.GetGameWindow()->getSize().y / 1.f, 
		sf::Color::White, 
		&game.GetTextures().get(Textures::ID::Player2Paddle), true);
	mPlayerB->PlayerAIOn(true);
	
	// Set the AI Speed Based on the difficulty
	if (game.GetDifficulty() == Game::GameDifficulty::Easy)
		mPlayerB->IncreasePlayerSpeed(0.f);
	else if (game.GetDifficulty() == Game::GameDifficulty::Medium)
		mPlayerB->IncreasePlayerSpeed(50.f);
	else if (game.GetDifficulty() == Game::GameDifficulty::Hard)
		mPlayerB->IncreasePlayerSpeed(150.f);
	else if (game.GetDifficulty() == Game::GameDifficulty::Medium)
		mPlayerB->IncreasePlayerSpeed(300.f);

	// This is the texture rext size for the main background --> Repeating
	sf::IntRect textureRect(0, 0, 10000.f, Game::GetInstance().GetGameWindow()->getSize().y);

	// Init Background Sprite
	sf::Sprite backgroundSprite(game.GetTextures().get(Textures::ID::Background_Layer_1), textureRect);
	backgroundSprite.setScale(sf::Vector2f(7.f, 7.f));

	
	sf::Sprite starsSprite;
	starsSprite.setTexture(game.GetTextures().get(Textures::ID::Background_Layer_2));
	starsSprite.setScale(sf::Vector2f(7.f, 7.f));
	
	sf::Sprite farPlanetsSprite;
	farPlanetsSprite.setTexture(game.GetTextures().get(Textures::ID::Background_Layer_3));
	farPlanetsSprite.setScale(sf::Vector2f(7.f, 7.f));

	sf::Sprite ringPlanetsSprite;
	ringPlanetsSprite.setTexture(game.GetTextures().get(Textures::ID::Background_Layer_4));
	ringPlanetsSprite.setScale(sf::Vector2f(7.f, 7.f));

	sf::Sprite bigPlanetSprite;
	bigPlanetSprite.setTexture(game.GetTextures().get(Textures::ID::Background_Layer_5));
	bigPlanetSprite.setPosition(game.GetGameWindow()->getSize().x / 2, game.GetGameWindow()->getSize().y / 2);
	bigPlanetSprite.setScale(sf::Vector2f(7.f, 7.f));


	mBackgroundSprites.insert(std::make_pair(GameState::BackgroundImages::Main, std::move(backgroundSprite)));
	mBackgroundSprites.insert(std::make_pair(GameState::BackgroundImages::Stars, std::move(starsSprite)));
	mBackgroundSprites.insert(std::make_pair(GameState::BackgroundImages::Far_Away, std::move(farPlanetsSprite)));
	mBackgroundSprites.insert(std::make_pair(GameState::BackgroundImages::Ring, std::move(ringPlanetsSprite)));
	mBackgroundSprites.insert(std::make_pair(GameState::BackgroundImages::Big_Planet, std::move(bigPlanetSprite)));
}

void GameState::HandleInput(sf::Event& event)
{

}

void GameState::UpdateAI(const float& dt)
{
	for (auto& ball : mBalls)
	{
		if (ball.GetBallRight() && ball.GetPosition().y < mPlayerB->GetPlayerYPosition())
		{
			//std::cout << ball.GetPosition().y << ", " << mPlayerB->GetPlayerYPosition() << "\n";
			mPlayerB->PlayerMoveUP(dt);
		}

		else if (ball.GetBallRight() && ball.GetPosition().y > mPlayerB->GetPlayerYPosition())
		{
			//std::cout << ball.GetPosition().y << ", " << mPlayerB->GetPlayerYPosition() << "\n";
			mPlayerB->PlayerMoveDown(dt);
		}
	}

	mPlayerB->PlayerAIDrift(dt);
}

void GameState::UpdateUI()
{
	std::stringstream ss1;
	std::stringstream ss2;
	std::stringstream ss3;

	ss1 << "SCORE:   " << mPScore1; 
	mUIText.at(GameState::UIText::Player1_Score).setString(std::move(ss1.str()));

	ss2 << "SCORE:   " << mPScore2;
	mUIText.at(GameState::UIText::Player2_Score).setString(std::move(ss2.str()));

	ss3 << "SPEED LEVEL:   " << mCurrentSpeedLevel;
	mUIText.at(GameState::UIText::SpeedLevel).setString(std::move(ss3.str()));
}

void GameState::MultiPlayerMode()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		mTurnOnAI = false;
		mPlayerB->PlayerAIOn(false);
	}
}

void GameState::UpdateTimers()
{
	mInterTimer = mInterClock.getElapsedTime().asSeconds();

	mFlasher = mFlashClock.getElapsedTime().asSeconds();

	if (mFlasher > 0.5f)
	{
		mFlash = true;
		if (mFlasher > 1.f)
		{
			mFlash = false;
			mFlashClock.restart();
		}
	}
}

void GameState::UpdatePlayerScores()
{
	for (auto& ball : mBalls)
	{
		if (ball.GetPosition().x <= 0.f)
		{
			ball.SetPosition(Game::GetInstance().GetGameWindow()->getSize().x / 2 - ball.GetGlobalBounds().width, Game::GetInstance().GetGameWindow()->getSize().y / 2);
			ball.SetBallLeft(false);
			ball.SetBallRight(false);

			mSpeedDifficulty = 0;
			mCurrentSpeedLevel = 0;
			mPlayer2Scored = true;
			mMovementSpeed = 650.f;
			ball.SetSpeed(0.f);
		}

		if (ball.GetPosition().x >= Game::GetInstance().GetGameWindow()->getSize().x)
		{
			ball.SetPosition(Game::GetInstance().GetGameWindow()->getSize().x / 2, Game::GetInstance().GetGameWindow()->getSize().y / 2);
			ball.SetBallLeft(false);
			ball.SetBallRight(false);
			mSpeedDifficulty = 0;
			mCurrentSpeedLevel = 0;
			mPlayer1Scored = true;
			mMovementSpeed = 650.f;
			ball.SetSpeed(0.f);
		}
	}

	if (mPlayer1Scored)
	{
		game.GetSoundPlayer().play(SoundEffect::ID::Goal);
		mPScore1++;
		mPlayer1Scored = false;
		mGoals = true;
		mGameText.at(GameState::GameText::Goal).setString("PLAYER 1\n   GOAL!!");

		switch (mPScore1)
		{
		case 1:
			mP1UpgradeAvailable = true;
			break;

		case 2:
			mP1UpgradeAvailable = false;
			break;

		case 3:
			mP1UpgradeAvailable = true;
			break;
		default:
			break;
		}
	}

	if (mPlayer2Scored)
	{
		game.GetSoundPlayer().play(SoundEffect::ID::Goal);
		mPScore2++;
		mPlayer2Scored = false;
		mGoals = true;
		mGameText.at(GameState::GameText::Goal).setString("PLAYER 2\n   GOAL!!");

		switch (mPScore2)
		{
		case 1:
			mP2UpgradeAvailable = true;
			break;

		case 2:
			mP2UpgradeAvailable = false;
			break;

		case 3:
			mP2UpgradeAvailable = true;
			break;
		default:
			break;
		}
	}
}

void GameState::UpdatePlayerUpgrades()
{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) || mPlayerA->IsPlayerAI() && mP1UpgradeAvailable)
	{
		switch (mPScore1)
		{

		case 1:
			mPlayerA->PlayerUpgrades(mPScore1);
			game.GetSoundPlayer().play(SoundEffect::ID::Upgrade);
			mP1UpgradeAvailable = false;
			mUpgradeAccepted1 = true;
			break;
		case 3:
			game.GetSoundPlayer().play(SoundEffect::ID::Upgrade);
			mPlayerA->PlayerUpgrades(mPScore1);
			mP1UpgradeAvailable = false;
			mUpgradeAccepted1 = true;
			break;
		default:
			break;
		}
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) || mPlayerB->IsPlayerAI() && mP2UpgradeAvailable)
	{
		switch (mPScore2)
		{
			case 1:
			mPlayerB->PlayerUpgrades(mPScore2);
			game.GetSoundPlayer().play(SoundEffect::ID::Upgrade);
			mP2UpgradeAvailable = false;
			mUpgradeAccepted2 = true;
			break;

			case 3:
			mPlayerB->PlayerUpgrades(mPScore2);
			game.GetSoundPlayer().play(SoundEffect::ID::Upgrade);
			mP2UpgradeAvailable = false;
			mUpgradeAccepted2 = true;
			break;
		default:
			break;
		}
	}
}

void GameState::UpdateBackground(const float& dt)
{
	for (auto& bgSprites : mBackgroundSprites)
	{
		if (bgSprites.first == GameState::BackgroundImages::Main)
			bgSprites.second.move(sf::Vector2f(-10.f * mCurrentSpeedLevel * dt, 0.f));
		
		if (bgSprites.first == GameState::BackgroundImages::Stars)
			bgSprites.second.move(sf::Vector2f(-35.f  * mCurrentSpeedLevel * dt, 0.f));

		if (bgSprites.first == GameState::BackgroundImages::Far_Away)
			bgSprites.second.move(sf::Vector2f(-40.f * mCurrentSpeedLevel * dt, 0.f));

		if (bgSprites.first == GameState::BackgroundImages::Ring)
			bgSprites.second.move(sf::Vector2f(-45.f * mCurrentSpeedLevel * dt, 0.f));

		if (bgSprites.first == GameState::BackgroundImages::Big_Planet)
			bgSprites.second.move(sf::Vector2f(-10.f * mCurrentSpeedLevel * dt, 0.f));

		// Have a constant speed for all objects if the current level is zero
		if (mCurrentSpeedLevel == 0)
			bgSprites.second.move(sf::Vector2f(-10.f * dt, 0.f));

		if (bgSprites.first != GameState::BackgroundImages::Main && bgSprites.second.getPosition().x < -1920.f)
			bgSprites.second.setPosition(Game::GetInstance().GetGameWindow()->getSize().x, 0);
	}
}

void GameState::UpdateBallMovement(const float& dt)
{
	// ====================================================================================================
	// Ball Movement
	// ====================================================================================================
	for (auto& ball : mBalls)
	{

		// Start Game / After Goals / New Ball enters
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)/* || ball.GetSpeed() == 0.f*/) && !ball.GetBallLeft() && !ball.GetBallRight())
		{

			game.GetMusicPlayer().setPitch(1.0f);
			// Random direction Generators
			unsigned dir = rand() % 2 + 1;
			unsigned dir1 = rand() % 2 + 1;

			//mMovementSpeed = 300.f;
			mGoals = false;

			// What direction is the ball moving?
			if (dir == 1)
				ball.SetBallLeft(true);
			else
				ball.SetBallRight(true);

			if (dir1 == 1)
				ball.SetBallUp(true);
			else
				ball.SetBallDown(true);

			ball.ResetLevel();
			// Set the ball speed to the movement speed
			ball.SetSpeed(mMovementSpeed);
			
			game.GetSoundPlayer().play(SoundEffect::ID::Start);
		}

		// Check For mPlayerA/Ball Collision
		if (ball.GetGlobalBounds().intersects(mPlayerA->GetBounds()) && mInterTimer >= .05f)
		{
			unsigned dir = rand() % 2 + 1;

			if (dir == 1)
			{
				ball.SetBallDown(false);
				ball.SetBallUp(true);
			}
			else
			{
				ball.SetBallDown(true);
				ball.SetBallUp(false);
			}
			ball.SetBallRight(true);
			ball.SetBallLeft(false);
			ball.SetRotationDir(true);
			mPlayerA->Flash(true);
			mSpeedDifficulty++;
			
			game.GetSoundPlayer().play(SoundEffect::ID::Bounce1);

			mInterClock.restart();

		}
		else
		{
			if (mInterTimer > .2f)
			{
				mPlayerA->Flash(false);
			}
		}

		// Check For mPlayerB/Ball Collision
		if (ball.GetGlobalBounds().intersects(mPlayerB->GetBounds()) && mInterTimer >= .05f)
		{
			unsigned dir = rand() % 2 + 1;

			if (dir == 1)
			{
				ball.SetBallUp(true);
				ball.SetBallDown(false);
			}
			else
			{
				ball.SetBallUp(false);
				ball.SetBallDown(true);
			}

			ball.SetBallRight(false);
			ball.SetBallLeft(true);
			ball.SetRotationDir(false);

			mPlayerB->Flash(true);
			mSpeedDifficulty++;

			game.GetSoundPlayer().play(SoundEffect::ID::Bounce1);
			mInterClock.restart();
		}
		else
		{
			if (mInterTimer > .2f)
			{
				mPlayerB->Flash(false);
			}
		}

		// Ball is Moving Left
		if (ball.GetBallLeft())
		{
			if (ball.GetBallUp())
			{
				ball.SetBallMovement(-1.f, mBallUp, dt);
			}

			if (ball.GetBallDown())
			{
				ball.SetBallMovement(-1.f, mBallDown, dt);
			}
		}

		// Ball is Moving Right
		if (ball.GetBallRight())
		{
			if (ball.GetBallUp())
			{
				ball.SetBallMovement(1.f, mBallUp, dt);
			}

			if (ball.GetBallDown())
			{
				ball.SetBallMovement(1.f, mBallDown, dt);
			}
		}
	}
}

void GameState::UpdateBallRotation(const float& dt)
{
	for (auto& ball : mBalls)
		ball.UpdateRotation(dt);
}

void GameState::UpdateBallCollision(const float& dt)
{
	for (auto& ball : mBalls)
	{
		if (ball.GetPosition().y - ball.GetGlobalBounds().height <= 0.f && ball.GetBallUp())
		{
			ball.SetBallDown(true);
			ball.SetBallUp(false);

			if (ball.GetBallLeft() && ball.GetBallDown())
			{
				ball.SetPosition(ball.GetPosition().x, 0.f + ball.GetGlobalBounds().height);
			}
			else if (ball.GetBallRight() && ball.GetBallDown())
			{
				ball.SetPosition(ball.GetPosition().x, 0.f + ball.GetGlobalBounds().height);
			}
		}

		if (ball.GetPosition().y + ball.GetGlobalBounds().height >= Game::GetInstance().GetGameWindow()->getSize().y)
		{
			ball.SetBallDown(false);
			ball.SetBallUp(true);

			if (ball.GetBallLeft() && ball.GetBallUp())
			{
				ball.SetPosition(ball.GetPosition().x, Game::GetInstance().GetGameWindow()->getSize().y - ball.GetGlobalBounds().height);
			}
			else if (ball.GetBallRight() && ball.GetBallUp())
			{
				ball.SetPosition(ball.GetPosition().x, Game::GetInstance().GetGameWindow()->getSize().y - ball.GetGlobalBounds().height);
			}
		}
	}
}

void GameState::UpdateBallSpeed(const float& dt)
{
	int temp = mCurrentSpeedLevel;

	for (auto& ball : mBalls)
	{
		// Update Speed of Ball!!
		if (mSpeedDifficulty >= 10 && mLevelUp)
		{
			mLevelUp = false;
			ball.IncreaseLevel();
			//mMovementSpeed *= 1.25f;
			mCurrentSpeedLevel++;
			mSpeedDifficulty = 0;
			game.GetMusicPlayer().setPitch(mCurrentSpeedLevel * 0.1 + 1);
		}
		else if (mSpeedDifficulty > 9)
		{
			mLevelUp = true;
		}
	}

	// Add a new ball after speed level get so high
	if (temp != mCurrentSpeedLevel && mCurrentSpeedLevel % mBallMultiplier == 0)
	{
		Ball newBall(50.0f, &game.GetTextures().get(Textures::ID::Ball));
		mBalls.push_back(newBall);

		newBall.SetStartPosition(*game.GetGameWindow());
		temp = mCurrentSpeedLevel;
	}
}

void GameState::UpdateBallColors()
{
	for (auto& ball : mBalls)
	{
		switch (ball.GetLevel())
		{
		case 1:
			ball.SetBallFillColor(sf::Color::White);
			ball.SetTextureRect(sf::IntRect(128, 0, 128, 128));
			break;

		case 2:
			ball.SetBallFillColor(sf::Color::White);
			ball.SetTextureRect(sf::IntRect(256, 0, 128, 128));
			break;
		case 3:
			ball.SetBallFillColor(sf::Color::White);
			ball.SetTextureRect(sf::IntRect(384, 0, 128, 128));
			break;

		case 4:
			ball.SetTextureRect(sf::IntRect(0, 128, 128, 128));
			break;
		case 5:
			ball.SetBallFillColor(sf::Color::White);
			ball.SetTextureRect(sf::IntRect(128, 128, 128, 128));
			break;

		case 6:
			ball.SetBallFillColor(sf::Color::White);
			ball.SetTextureRect(sf::IntRect(256, 128, 128, 128));
			break;

		case 7:
			ball.SetBallFillColor(sf::Color::White);
			ball.SetTextureRect(sf::IntRect(384, 128, 128, 128));
			break;

		default:
			ball.SetBallFillColor(sf::Color::White);
			ball.SetTextureRect(sf::IntRect(0, 0, 128, 128));
			break;
		}
	}
}

void GameState::Update(const float& dt)
{
	MultiPlayerMode();
	UpdateTimers();
	UpdateUI();

	mPlayerA->Update(dt);
	mPlayerB->Update(dt);
	

	UpdateBallMovement(dt);
	UpdateBallRotation(dt);
	UpdateBallCollision(dt);
	UpdateBallSpeed(dt);
	UpdateBallColors();

	// Only Update AI if single player
	if (mPlayerB->IsPlayerAI()) UpdateAI(dt);

	UpdatePlayerScores();
	UpdatePlayerUpgrades();
	UpdateBackground(dt);

	// Remove the sounds if they are not playing
	game.GetSoundPlayer().removeStoppedSounds();
}

void GameState::Render(const float& dt)
{
	for (auto& bgSprite : mBackgroundSprites)
	{
		game.GetGameWindow()->draw(bgSprite.second);
	}
	game.GetGameWindow()->draw(mTopGUIBlock);

	mPlayerA->Render(*game.GetGameWindow());
	mPlayerB->Render(*game.GetGameWindow());

	// Draw Ball
	for (auto& ball : mBalls)
		game.GetGameWindow()->draw(ball.GetBall());

	// Draw UI Text
	for (auto& text : mUIText)
	{
		Game::GetInstance().GetGameWindow()->draw(text.second);
	}
	
	if (mP1UpgradeAvailable)
		game.GetGameWindow()->draw(mGameText.at(GameState::GameText::Player1_Upgrade));

	if (mP2UpgradeAvailable)
		game.GetGameWindow()->draw(mGameText.at(GameState::GameText::Player2_Upgrade));

	if (mTurnOnAI && mFlash)
		game.GetGameWindow()->draw(mGameText.at(GameState::GameText::Player2_Join));

	if (mGoals)
		game.GetGameWindow()->draw(mGameText.at(GameState::GameText::Goal));

}
