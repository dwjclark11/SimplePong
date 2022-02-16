#pragma once
#include "ResourceHolder.h"
namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
	class Music;
}

namespace Textures
{
	enum ID
	{
		None,
		Player1Paddle,
		Player2Paddle,
		Ball,
		Background_Layer_1,
		Background_Layer_2,
		Background_Layer_3,
		Background_Layer_4,
		Background_Layer_5,
		MenuBackground,
	};
}

namespace Fonts
{
	enum ID
	{
		Main,
		Goal,
		MenuTitle,
	};
}

namespace SoundEffect
{
	enum ID
	{
		Bounce1,
		Bounce2,
		Goal,
		Start,
		Upgrade,
		UpgradeAvailable,
		ButtonUp,
		ButtonSelect,
		ButtonCancel ,
	};
}

namespace Music
{
	enum ID
	{
		MenuTheme,
		GamePlay,
	};
}

template<typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>				TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>						FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>		SoundBufferHolder;
typedef ResourceHolder<sf::Music, Music::ID>					MusicHolder;