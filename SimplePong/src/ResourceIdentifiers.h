#pragma once

namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

namespace Textures
{
	enum ID
	{
		None,
	};
}

namespace Fonts
{
	enum ID
	{
		Main,

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
		//UpgradeAccepted,
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