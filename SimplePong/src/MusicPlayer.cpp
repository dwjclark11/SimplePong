#include "stdafx.h"
#include "MusicPlayer.h"

MusicPlayer::MusicPlayer()
	: mMusic()
	, mFilenames()
	, mVolume(20.f)
{
	//mFilenames[Music::MenuTheme] = "Music/Main.ogg";
	//mFilenames[Music::TitleTheme] = "Music/TitleTheme.ogg";
	mFilenames[Music::GamePlay] = "Music/Just Move.ogg";
	main = false;
	pause = false;
}

void MusicPlayer::play(Music::ID theme)
{
	std::string filename =  mFilenames[theme];

	if (!mMusic.openFromFile(filename))
		throw std::runtime_error("Music " + filename + "could not be loaded!");

	mMusic.setVolume(mVolume);
	mMusic.setLoop(true);
	mMusic.play();
}

void MusicPlayer::stop()
{
	mMusic.stop();
}

void MusicPlayer::setPaused(bool paused)
{
	if (paused)
	{
		mMusic.pause();
		pause = true;
	}
	else
	{
		mMusic.play();
		pause = false;
	}
}

void MusicPlayer::setVolume(float volume)
{
	mVolume = volume;
}

const bool& MusicPlayer::getPaused() const
{
	return pause;
}

void MusicPlayer::setMain(bool menu)
{
	if (menu)
	{
		main = true;
	}
	else
	{
		main = false;
	}
}

const bool& MusicPlayer::getMain() const
{
	return main;
}

void MusicPlayer::setPitch(float pitch)
{
	mMusic.setPitch(pitch);
}
