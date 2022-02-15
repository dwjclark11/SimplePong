#pragma once
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>

#include <map>
#include <string>

class MusicPlayer : private sf::NonCopyable
{
public:

	MusicPlayer();

	void play(Music::ID theme);
	void stop();

	void setPaused(bool paused);
	void setVolume(float volume);
	const bool& getPaused() const;
	void setMain(bool menu);
	const bool& getMain() const;
	void setPitch(float pitch);

private:
	sf::Music mMusic;
	std::map<Music::ID, std::string> mFilenames;
	float mVolume;

	bool pause;
	bool main;

};
