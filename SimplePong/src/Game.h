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

	Menu Theme - 'Warped'
		This was made by Alexander Ehlers, find it at (https://opengameart.org/content/free-music-pack)

	Background Textures - 
		(https://opengameart.org/content/space-background-3)

	Menu Title Fonts -
		Astonished Fonts by Eduardo Recife / Misprinted Type @ (http://ww.misprintedtype.com)
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
	const std::unique_ptr<StateMachine>& GetStateMachine() const { return mGameStateMachine; }

	void updateDeltaTime();

	
	void update();
	void HandleInputs();
	void render();
	void run();

};

