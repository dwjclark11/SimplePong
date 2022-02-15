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
		Background_Layer_1

	};
}

namespace Fonts
{
	enum ID
	{
		Main,
		Goal,

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
		//ButtonUp,
		//ButtonDown,
		//ButtonStart,
		//TitleStart,
		//BackButton,
		//Set_EditButton,

	};
}

namespace Music
{
	enum ID
	{
		//TitleTheme,
		//MenuTheme,
		GamePlay,

	};
}


template<typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>				TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>						FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>		SoundBufferHolder;
typedef ResourceHolder<sf::Music, Music::ID>					MusicHolder;