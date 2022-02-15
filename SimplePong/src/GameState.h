#pragma once
#include "State.h"
#include "ResourceIdentifiers.h"
#include "Ball.h"
#include "SoundPlayer.h"
#include "MusicPlayer.h"

class GameState : public State
{
private:
	enum class UIText
	{
		Player1_Score,
		Player2_Score,
		Current_Round,
		SpeedLevel,
	};

	enum class GameText
	{
		Goal,
		Player1_Upgrade,
		Player2_Upgrade,
		Player1_Upgrade_Type,
		Player2_Upgrade_Type,
		Player2_Join,
	};

	std::unique_ptr<class Player> mPlayerA;
	std::unique_ptr<class Player> mPlayerB;
	
	std::vector<Ball> mBalls;
	
	std::map<UIText, sf::Text> mUIText;
	std::map<GameText, sf::Text> mGameText;

	sf::Texture mRedPaddleTexture;
	sf::Texture mBluePaddleTexture;

	//sf::Clock mDtClock;
	sf::Clock mInterClock;
	sf::Clock mFlashClock;
	
	TextureHolder		mTextureHolder;
	FontHolder			mFontHolder;

	SoundPlayer			mSoundPlayer;
	MusicPlayer		    mMusicPlayer;

	sf::Sprite mBackgroundSprite;

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

	// These should be inside of player
	bool mP1UpgradeAvailable;
	bool mP2UpgradeAvailable;

	bool mUpgradeAccepted1;
	bool mUpgradeAccepted2;

	unsigned mCurrentSpeedLevel;
	bool mPlayer1Scored;
	bool mPlayer2Scored;
	unsigned mPScore1;
	unsigned mPScore2;
	bool mGoals;

public:
	GameState();
	~GameState();
	void InitResources();
	void InitVariables();
	void InitBall();
	void InitUITexts();

	virtual void Init() override;
	virtual void HandleInput() override;

	void UpdateAI(const float& dt);
	void UpdateUI();
	void MultiPlayerMode();
	void UpdateTimers();
	
	// Player Updates
	void UpdatePlayerScores();
	void UpdatePlayerUpgrades();
	
	// Ball Updates
	void UpdateBallMovement(const float& dt);
	void UpdateBallRotation(const float& dt);
	void UpdateBallCollision(const float& dt);
	void UpdateBallSpeed(const float& dt);
	void UpdateBallColors();
	
	virtual void Update(const float& dt) override;
	virtual void Render(const float& dt) override;

	virtual void Pause()  override {}
	virtual void Resume() override {}
};