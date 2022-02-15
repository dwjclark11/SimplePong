#include "stdafx.h"
#include "SoundPlayer.h"

#include "SFML/Audio/Listener.hpp"

#include <cmath>

namespace
{
	// Sound coordinate system, point of view of a player in front of the screen:
	// X = left; Y = up; Z = back (out of screen)
	const float ListenerZ = 300.f;
	const float Attenuation = 8.f;
	const float MinDisance2D = 200.f;
	const float MinDistance3D = std::sqrt(MinDisance2D * MinDisance2D + ListenerZ * ListenerZ);
}

SoundPlayer::SoundPlayer()
	:mSoundBuffers()
	, mSounds()
{
	mSoundBuffers.load(SoundEffect::Bounce1, "Sounds/paddle_1_hit.wav");
	mSoundBuffers.load(SoundEffect::Goal, "Sounds/Goal.wav");
	mSoundBuffers.load(SoundEffect::Start, "Sounds/Ball_Start.wav");
	//mSoundBuffers.load(SoundEffect::Bounce, "Sounds/Upgrade.wav");
	//mSoundBuffers.load(SoundEffect::ButtonDown, "Sounds/cursorDown.ogg");
	//mSoundBuffers.load(SoundEffect::ButtonUp, "Sounds/cursorUp.ogg");
	//mSoundBuffers.load(SoundEffect::TitleStart, "Sounds/TitleStart.ogg");
	//mSoundBuffers.load(SoundEffect::ButtonStart, "Sounds/Start.ogg");
	//mSoundBuffers.load(SoundEffect::BackButton, "Sounds/BackButton.ogg");
	
	// Listener points towards the screen (default in SFML)
	sf::Listener::setDirection(0.f, 0.f, -1.f);
}

void SoundPlayer::play(SoundEffect::ID effect)
{
	play(effect, getListenerPosition());
}

void SoundPlayer::play(SoundEffect::ID effect, sf::Vector2f position)
{
	mSounds.push_back(sf::Sound());
	sf::Sound& sound = mSounds.back();

	sound.setBuffer(mSoundBuffers.get(effect));
	sound.setPosition(position.x, -position.y, 0.f);
	sound.setAttenuation(Attenuation);
	sound.setMinDistance(MinDistance3D);

	sound.play();
}

void SoundPlayer::removeStoppedSounds()
{
	mSounds.remove_if([](const sf::Sound& s)
		{
			return s.getStatus() == sf::Sound::Stopped;
		});
}

void SoundPlayer::setListenerPosition(sf::Vector2f position)
{
	sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

sf::Vector2f SoundPlayer::getListenerPosition() const
{
	sf::Vector3f position = sf::Listener::getPosition();
	return sf::Vector2f(position.x, -position.y);
}