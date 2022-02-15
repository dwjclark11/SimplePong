#pragma once
#include "Player.h"
#include "MusicPlayer.h"
#include "Ball.h"
#include "StateMachine.h"

/*
	Paddle Textures -
		were made by Nicolas A. Ortega (Deathsbreed) copyright DeathsbreedGames organization (http://deathsbreedgames.github.io/)
		All works (from DeathsbreedGamesare) are licensed with the CC-BY-SA license. These textures were found at (https://opengameart.org/content/pong-graphics)

	GamePlay Music -
		These song was found at (https://opengameart.org/content/pong-graphics) and created by Trevor Lents!

	Background Textures - 
		(https://opengameart.org/content/space-background-3)
*/


class Game
{
private: 
	sf::Clock mDtClock;
	sf::Clock mInterClock;
	sf::Clock mFlashClock;
	float mDt;
	float mInterTimer;
	float mFlasher;

	float mMovementSpeed;

	bool mFlash;
	bool mTurnOnAI;

	bool mLevelUp;

	unsigned mSpeedDifficulty;
	float mBallUp;
	float mBallDown;

	bool mEasy;
	bool mMedium;
	bool mHard;
	bool mImpossible;

	bool mP1UpgradeAvailable;
	bool mP2UpgradeAvailable;

	bool mUpgradeAccepted1;
	bool mUpgradeAccepted2;

	std::unique_ptr<Player> mPlayerA;
	std::unique_ptr<Player> mPlayerB;
	
	std::unique_ptr<sf::RenderWindow> mWindow;

	std::vector<Ball> mBalls;

	sf::RectangleShape mTopGUIBlock;

	MusicPlayer mMusicPlayer;
	sf::Music mMusic;
	sf::Sound mSound;
	sf::Sound mGooooaaaaallll;
	sf::Sound mStart;
	sf::SoundBuffer mSoundBuffer;
	sf::SoundBuffer mSoundBuffer1;
	sf::SoundBuffer mSoundBuffer2;

	sf::Font mFont;
	sf::Font mFontB;
	sf::Text mPlayer1Score;
	sf::Text mPlayer2Score;
	sf::Text mCcurrentRound;
	sf::Text mPlayer1Upgrade;
	sf::Text mPlayer2Upgrade;

	sf::Text mPlayer2Join;

	sf::Text mP1UpgradeType;
	sf::Text mP2UpgradeType;

	sf::Text mGoal;

	sf::Text mSpeedLevel;

	sf::Texture mBackgroundTexture;
	
	sf::Texture mSunTexture;
	sf::Texture mRedPaddleTexture;
	sf::Texture mBluePaddleTexture;
	
	sf::Sprite mBackgroundSprite;
	
	unsigned mCurrentSpeedLevel;
	bool mPlayer1Scored;
	bool mPlayer2Scored;
	unsigned mPScore1;
	unsigned mPScore2;
	bool mGoals;


public:
	Game();
	~Game();

	void initVariables();
	void initWindow();
	void initTextures();
	void initFont();
	void initUI();
	void initMusic();
	void initSound();
	void initPlayer();
	void initBall();


	void multiPlayerMode();

	void updateAIDifficulty();
	void updateAI();
	void updateDeltaTime();
	void updateBallMovement();
	void updateBallRotation(const float& dt);
	void updateBallCollisions();
	void updateBallSpeed();
	void updatePlayerScores();
	void updatePlayerUpgrades();
	void updateBallColors();
	void updateUI();
	void update();
	void render();
	void run();

};

