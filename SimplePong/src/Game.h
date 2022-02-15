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

	std::unique_ptr<StateMachine> mGameStateMachine;

	sf::Clock mDtClock;

	float mDt;

	bool mEasy;
	bool mMedium;
	bool mHard;
	bool mImpossible;

	
	std::unique_ptr<sf::RenderWindow> mWindow;


	sf::RectangleShape mTopGUIBlock;

	Game();
	// How do I avoid this?
	static std::unique_ptr<Game> mInstance;

public:

	~Game();

	static Game& GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance.reset(new Game());
		}

		return *mInstance;
	}

	
	void initWindow();

	const std::unique_ptr<sf::RenderWindow>& GetGameWindow() const { return mWindow; }
	void updateDeltaTime();

	
	void update();
	void render();
	void run();

};

