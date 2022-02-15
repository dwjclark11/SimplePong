#pragma once

#include <sstream>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <random>
#include <cmath>
#include <ctime>
#include <cassert>

namespace sf
{
	class Sprite;
	class Text;
}

template <typename T>
std::string toString(const T& value);

// Convert enumerators to strings
std::string toString(sf::Keyboard::Key key);

// Call setOrigin() with the center of the object
void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

// Convert Degrees to Radians
float toDegree(float radian);
float toRadian(float degree);

// Random number generation
int randomInt(int exclusiveMax);

// Vector Operations
float length(sf::Vector2f vector);
sf::Vector2f unitVector(sf::Vector2f vector);

#include "Utility.inl"

