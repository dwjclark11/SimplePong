#include "stdafx.h"
#include "Game.h"

void Game::initVariables()
{
	mWindow = nullptr;

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
	mMedium = false;
	mHard = true;
	mImpossible = false;
}

void Game::initWindow()
{
	mWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "Simple Pong");
}

void Game::initTextures()
{
	if (!mBackgroundTexture.loadFromFile("Textures/parallax-space-backgound.png"))
		throw ("Unable to load parallax");

	if (!mSunTexture.loadFromFile("Textures/ball_images.png"))
		throw ("Unable to load Sun");
	
	if (!mRedPaddleTexture.loadFromFile("Textures/red_paddle.png"))
		throw ("Unable to load Red Paddle");

	if (!mBluePaddleTexture.loadFromFile("Textures/blue_paddle.png"))
		throw ("Unable to load Red Paddle");


	mBackgroundSprite.setTexture(mBackgroundTexture);
	mBackgroundSprite.setScale(sf::Vector2f(7.f, 7.f));
}

void Game::initFont()
{
	if (!mFont.loadFromFile("Fonts/Main.ttf"))
	{
		throw("ERROR UNABLE TO LOAD mFont!!");
	}

	if (!mFontB.loadFromFile("Fonts/Goal1.ttf"))
	{
		throw("ERROR UNABLE TO LOAD mFont!!");
	}
}

void Game::initUI()
{
	mTopGUIBlock.setFillColor(sf::Color::Black);
	mTopGUIBlock.setSize(sf::Vector2f(mWindow->getSize().x, 100.f));
	mTopGUIBlock.setPosition(sf::Vector2f(mWindow->getPosition()));

	mGoal.setFont(mFontB);
	mGoal.setCharacterSize(100);
	mGoal.setFillColor(sf::Color::Red);
	mGoal.setString("mGoal!!");
	mGoal.setPosition(mWindow->getSize().x / 1.75f- mGoal.getGlobalBounds().width, mWindow->getSize().y / 4);

	mPlayer1Upgrade.setFont(mFont);
	mPlayer1Upgrade.setCharacterSize(30);
	mPlayer1Upgrade.setFillColor(sf::Color::Yellow);
	mPlayer1Upgrade.setString("PLAYER 1 mUpgrade AVAILABLE");
	mPlayer1Upgrade.setPosition(mWindow->getSize().x / 12, mWindow->getSize().y / 6);

	mPlayer2Upgrade.setFont(mFont);
	mPlayer2Upgrade.setCharacterSize(30);
	mPlayer2Upgrade.setFillColor(sf::Color::Yellow);
	mPlayer2Upgrade.setString("PLAYER 2 mUpgrade AVAILABLE");
	mPlayer2Upgrade.setPosition(mPlayer1Upgrade.getPosition().x + 1200.f, mPlayer1Upgrade.getPosition().y);

	mP1UpgradeType.setFont(mFont);
	mP1UpgradeType.setCharacterSize(30);
	mP1UpgradeType.setFillColor(sf::Color::Yellow);
	mP1UpgradeType.setString("This Changes Based on mUpgrade");
	mP1UpgradeType.setPosition(mPlayer1Upgrade.getPosition().x, mPlayer1Upgrade.getPosition().y);

	mP2UpgradeType.setFont(mFont);
	mP2UpgradeType.setCharacterSize(30);
	mP2UpgradeType.setFillColor(sf::Color::Yellow);
	mP2UpgradeType.setString("This Changes Based on mUpgrade");
	mP2UpgradeType.setPosition(mPlayer1Upgrade.getPosition().x + 1200.f, mPlayer1Upgrade.getPosition().y);

	mPlayer1Score.setFont(mFont);
	mPlayer1Score.setCharacterSize(50);
	mPlayer1Score.setFillColor(sf::Color::White);
	mPlayer1Score.setString("SCORE: ");
	mPlayer1Score.setPosition(mWindow->getSize().x / 16, 20.f);

	mPlayer2Score.setFont(mFont);
	mPlayer2Score.setCharacterSize(50);
	mPlayer2Score.setFillColor(sf::Color::White);
	mPlayer2Score.setString("SCORE: ");
	mPlayer2Score.setPosition(mPlayer1Score.getPosition().x + 1500.f,  mPlayer1Score.getPosition().y);

	mPlayer2Join.setFont(mFont);
	mPlayer2Join.setCharacterSize(30);
	mPlayer2Join.setFillColor(sf::Color::White);
	mPlayer2Join.setString("PLAYER 2 PRESS SPACE\nTO JOIN GAME!");
	mPlayer2Join.setPosition(mPlayer1Score.getPosition().x + 1150.f, mPlayer1Score.getPosition().y - 10);

	mSpeedLevel.setFont(mFont);
	mSpeedLevel.setCharacterSize(60);
	mSpeedLevel.setFillColor(sf::Color::White);
	mSpeedLevel.setString("Test ");
	mSpeedLevel.setPosition((mWindow->getSize().x / 2.25) - mSpeedLevel.getGlobalBounds().width, mPlayer1Score.getPosition().y - 10.f);
}

void Game::initMusic()
{
	//if (!music.openFromFile("Music/Main.ogg"))
	//	throw ("COULD NOT LOAD MAIN MUSIC!!");

	//music.setLoop(true);
	//music.setVolume(20);
	mMusicPlayer.setVolume(15);
	mMusicPlayer.play(Music::GamePlay);
	
}

void Game::initSound()
{
	mSoundBuffer.loadFromFile("Sounds/paddle_1_hit.wav");
	mSoundBuffer1.loadFromFile("Sounds/Goal.wav");
	mSoundBuffer2.loadFromFile("Sounds/Ball_Start.wav");
	mGooooaaaaallll.setBuffer(mSoundBuffer1);
	mStart.setBuffer(mSoundBuffer2);
	mSound.setBuffer(mSoundBuffer);
	mSound.setVolume(100);
}

void Game::initPlayer()
{
	mPlayerA = std::make_unique<Player>(50.f, mWindow->getSize().y / 2.f, mWindow->getSize().y, sf::Color::White, &mRedPaddleTexture, false);
	mPlayerB = std::make_unique<Player>(mWindow->getSize().x - 150.f, mWindow->getSize().y / 2, mWindow->getSize().y, sf::Color::White, &mBluePaddleTexture, true);
}

void Game::initBall()
{
	Ball ball(50.f, &mSunTexture);
	ball.SetStartPosition(*mWindow);
	ball.UpdateRotation();
	mBalls.push_back(ball);
}

Game::Game()
{
	initVariables();
	initWindow();
	initTextures();
	initFont();
	initUI();
	initMusic();
	initSound();
	initPlayer();
	initBall();
	mMusic.play();
}

Game::~Game()
{
	
}


void Game::multiPlayerMode()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		mTurnOnAI = false;
		mPlayerB->PlayerAIOn(false);
	}
}

void Game::updateAIDifficulty()
{
	mImpossible = false;
	mMedium = true;
	mHard = false;
}

void Game::updateAI()
{
	for (auto& ball : mBalls)
	{
		if (mTurnOnAI && mMedium)
		{
			mPlayerB->PlayerAIOn(true);

			if (ball.GetBallRight() && ball.GetPosition().y < mPlayerB->GetPlayerYPosition())
			{
				//std::cout << ball.GetPosition().y << ", " << mPlayerB->GetPlayerYPosition() << "\n";
				mPlayerB->PlayerMoveUP(mDt);
			}

			else if (ball.GetBallRight() && ball.GetPosition().y > mPlayerB->GetPlayerYPosition())
			{
				//std::cout << ball.GetPosition().y << ", " << mPlayerB->GetPlayerYPosition() << "\n";
				mPlayerB->PlayerMoveDown(mDt);
			}
		}
		else if (mTurnOnAI && mHard)
		{
			mPlayerB->PlayerAIOn(true);
			mMovementSpeed = 800;
			if (ball.GetPosition().y < mPlayerB->GetPlayerYPosition())
			{
				//std::cout << ball.GetPosition().y << ", " << mPlayerB->GetPlayerYPosition() << "\n";
				mPlayerB->PlayerMoveUP(mDt);
			}

			else if (ball.GetPosition().y > mPlayerB->GetPlayerYPosition())
			{
				//std::cout << ball.GetPosition().y << ", " << mPlayerB->GetPlayerYPosition() << "\n";
				mPlayerB->PlayerMoveDown(mDt);
			}
		}
		else if (mTurnOnAI && mImpossible)
		{
			mPlayerB->PlayerAIOn(true);

			mMovementSpeed = 1000.f;
			//ball.GetBall().setRadius(15.f);
			if (ball.GetPosition().y < mPlayerB->GetPlayerYPosition())
			{
				//std::cout << ball.GetPosition().y << ", " << mPlayerB->GetPlayerYPosition() << "\n";
				mPlayerB->PlayerMoveUP(mDt);
			}

			else if (ball.GetPosition().y > mPlayerB->GetPlayerYPosition())
			{
				//std::cout << ball.GetPosition().y << ", " << mPlayerB->GetPlayerYPosition() << "\n";
				mPlayerB->PlayerMoveDown(mDt);
			}
		}
	}

	mPlayerB->PlayerAIDrift(mDt);
}
		

void Game::updateDeltaTime()
{
	mDt = mDtClock.restart().asSeconds();
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

void Game::updateBallMovement()
{
	// ====================================================================================================
	// Ball Movement
	// ====================================================================================================
	for (auto& ball : mBalls)
	{
		ball.UpdateRotation();
		// Start Game / After Goals / New Ball enters
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || ball.GetSpeed() == 0.f) && !ball.GetBallLeft() && !ball.GetBallRight())
		{

			mMusicPlayer.setPitch(1.0f);
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
			mStart.play();
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
			mSound.play();
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
			mSound.play();
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
				ball.SetBallMovement(-1.f, mMovementSpeed, mBallUp, mDt);
			}

			if (ball.GetBallDown())
			{
				ball.SetBallMovement(-1.f, mMovementSpeed, mBallDown, mDt);
			}
		}

		// Ball is Moving Right
		if (ball.GetBallRight())
		{
			if (ball.GetBallUp())
			{
				ball.SetBallMovement(1.f, mMovementSpeed, mBallUp, mDt);
			}

			if (ball.GetBallDown())
			{
				ball.SetBallMovement(1.f, mMovementSpeed, mBallDown, mDt);
			}
		}
	}
}

void Game::updateBallCollisions()
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

		if (ball.GetPosition().y + ball.GetGlobalBounds().height >= mWindow->getSize().y)
		{
			ball.SetBallDown(false);
			ball.SetBallUp(true);
			
			if (ball.GetBallLeft() && ball.GetBallUp())
			{
				ball.SetPosition(ball.GetPosition().x, mWindow->getSize().y - ball.GetGlobalBounds().height);
			}
			else if (ball.GetBallRight() && ball.GetBallUp())
			{
				ball.SetPosition(ball.GetPosition().x, mWindow->getSize().y - ball.GetGlobalBounds().height);
			}
		}
	}
}

void Game::updateBallSpeed()
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
			mMusicPlayer.setPitch(mCurrentSpeedLevel * 0.1 + 1);
		}
		else if (mSpeedDifficulty > 9)
		{
			mLevelUp = true;
		}
	}

	// Add a new ball after speed level get so high
	if (temp != mCurrentSpeedLevel && mCurrentSpeedLevel %4 == 0)
	{
		Ball newBall(50.0f, &mSunTexture);
		mBalls.push_back(newBall);

		newBall.SetStartPosition(*mWindow);		
		temp = mCurrentSpeedLevel;
	}
}

void Game::updatePlayerScores()
{
	for (auto& ball : mBalls)
	{
		if (ball.GetPosition().x <= 0.f)
		{
			ball.SetPosition(mWindow->getSize().x / 2 - ball.GetGlobalBounds().width, mWindow->getSize().y / 2);
			ball.SetBallLeft(false);
			ball.SetBallRight(false);
			
			mSpeedDifficulty = 0;
			mCurrentSpeedLevel = 0;
			mPlayer2Scored = true;
			mMovementSpeed = 650.f;
			ball.SetSpeed(0.f);
		}

		if (ball.GetPosition().x >= mWindow->getSize().x)
		{
			ball.SetPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2);
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
		mGooooaaaaallll.play();
		mPScore1++;
		mPlayer1Scored = false;
		mGoals = true;
		mGoal.setString("PLAYER 1 \n  mGoal!!");

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
		mGooooaaaaallll.play();
		mPScore2++;
		mPlayer2Scored = false;
		mGoals = true;
		mGoal.setString("PLAYER 2 \n  Goal!!");

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

void Game::updatePlayerUpgrades()
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) || mPlayerA->IsPlayerAI() && mP1UpgradeAvailable)
	{
		switch (mPScore1)
		{

		case 1:
			mPlayerA->PlayerUpgrades(mPScore1);
			//mUpgrade.play();
			mP1UpgradeAvailable = false;
			mUpgradeAccepted1 = true;
			break;
		case 3:
			//mUpgrade.play();
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
			//mUpgrade.play();
			mP2UpgradeAvailable = false;
			mUpgradeAccepted2 = true;
			break;

			case 3:
			mPlayerB->PlayerUpgrades(mPScore2);
			//mUpgrade.play();
			mP2UpgradeAvailable = false;
			mUpgradeAccepted2 = true;
			break;
		default:
			break;
		}
	}
}

void Game::updateBallColors()
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

void Game::updateUI()
{
	std::stringstream ss1;
	std::stringstream ss2;
	std::stringstream ss3;

	ss1 << "SCORE:   " << mPScore1; 
	mPlayer1Score.setString(ss1.str());

	ss2 << "SCORE:   " << mPScore2;
	mPlayer2Score.setString(ss2.str());

	ss3 << "SPEED LEVEL:   " << mCurrentSpeedLevel;
	mSpeedLevel.setString(ss3.str());
}

void Game::update()
{

	multiPlayerMode();
	updateAIDifficulty();
	updateDeltaTime();

	mPlayerA->Update(mDt);
	mPlayerB->Update(mDt);

	updateBallMovement();
	updateAI();
	updateBallCollisions();
	updateBallSpeed();
	updateBallColors();
	updatePlayerScores();
	updatePlayerUpgrades();
	updateUI();


	// Exit the Game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		mWindow->close();

	sf::Event event;

	while (mWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mWindow->close();
		}
	}
}

void Game::render()
{
	// Render the mWindow 
	mWindow->clear();

	// Render the Background
	mWindow->draw(mBackgroundSprite);
	mWindow->draw(mTopGUIBlock);

	// Draw Players
	mPlayerA->Render(*mWindow);
	mPlayerB->Render(*mWindow);

	// Draw Ball
	for (auto& ball : mBalls)
		mWindow->draw(ball.GetBall());
	
	mWindow->draw(mPlayer1Score);
	mWindow->draw(mPlayer2Score);
	mWindow->draw(mSpeedLevel);

	// Render Player mUpgrade Text
	if (mTurnOnAI && mFlash)
		mWindow->draw(mPlayer2Join);

	if (mP1UpgradeAvailable)
		mWindow->draw(mPlayer1Upgrade);

	if (mP2UpgradeAvailable)
		mWindow->draw(mPlayer2Upgrade);

	if (mUpgradeAccepted1)
		mWindow->draw(mP1UpgradeType);

	if (mUpgradeAccepted2)
		mWindow->draw(mP2UpgradeType);

	// If there is a mGoal Render mGoal Text
	if (mGoals)
		mWindow->draw(mGoal);

	// Final Display
	mWindow->display();
}

void Game::run()
{
	while (mWindow->isOpen())
	{
		update();
		render();
	}
}
