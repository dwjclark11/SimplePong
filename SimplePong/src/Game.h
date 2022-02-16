#pragma once
#include "Player.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"
#include "Ball.h"
#include "StateMachine.h"
#include "ResourceIdentifiers.h"


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
public: 
	enum class GameDifficulty
	{
		Easy = 0,
		Medium,
		Hard,
		Impossible
	};

private: 

	std::unique_ptr<StateMachine> mGameStateMachine;

	sf::Clock mDtClock;

	float mDt;

	GameDifficulty mDifficulty;
	
	std::unique_ptr<sf::RenderWindow> mWindow;
	FontHolder mFontHolder;
	TextureHolder mTextureHolder;
	MusicPlayer mMusicPlayer;
	SoundPlayer mSoundPlayer;
	
	Game();
	// How do I avoid this?
	static std::unique_ptr<Game> mInstance;

	void initWindow();
	void InitFonts();
	void InitTextures();
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


	const std::unique_ptr<sf::RenderWindow>& GetGameWindow() const { return mWindow; }
	const std::unique_ptr<StateMachine>& GetStateMachine() const { return mGameStateMachine; }

	const FontHolder& GetFonts() const { return mFontHolder; }
	const TextureHolder& GetTextures() const { return mTextureHolder; }
	
	const GameDifficulty& GetDifficulty() const { return mDifficulty; }
	void SetGameDifficulty(Game::GameDifficulty difficulty) { mDifficulty = difficulty; }

	MusicPlayer& GetMusicPlayer() { return mMusicPlayer; }
	SoundPlayer& GetSoundPlayer() { return mSoundPlayer; }

	void updateDeltaTime();

	
	void update();
	void HandleInputs();
	void render();
	void run();

};

