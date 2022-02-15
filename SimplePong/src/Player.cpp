#include "stdafx.h"
#include "Player.h"

Player::Player(float xPos, float yPos, float max_down_pos, sf::Color color, const sf::Texture* texture, bool second_player)
{
	player.setFillColor(color);
	player.setTexture(texture);
	player.setSize(sf::Vector2f(20, 200));
	player.setPosition(sf::Vector2f(xPos, yPos));

	maxPlayerDown = max_down_pos;
	playerSpeed = 1200.f;
	secondPlayer = second_player;
	bPlayerAIOn = false;
}

Player::~Player()
{

}

void Player::PlayerAIDrift(const float& dt)
{

	//Top of the Screen
	if (player.getPosition().y - (player.getGlobalBounds().height - 40.f) <= 0)
	{
		player.setPosition(player.getPosition().x, 0.f + (player.getGlobalBounds().height - 40.f));
		driftDown = true;
		driftUp = false;
	}

	// Player 1 Drift Up
	if (driftUp)
	{
		player.move(0, -.05f * dt * playerSpeed);
	}

	//Bottom of the Screen
	if (player.getPosition().y + player.getGlobalBounds().height >= maxPlayerDown)
	{
		player.setPosition(player.getPosition().x, maxPlayerDown - player.getGlobalBounds().height);
		driftDown = false;
		driftUp = true;
	}

	// Player 1 Drift Down
	if (driftDown)
	{
		player.move(0, .05f * dt * playerSpeed);
	}
}

void Player::PlayerAIOn(bool AIOn)
{
	if (AIOn)
		bPlayerAIOn = true;
	else
		bPlayerAIOn = false;
}

float Player::GetPlayerYPosition()
{
	return player.getPosition().y;
}

void Player::PlayerMoveUP(const float& dt)
{
	player.move(0, -.5f * dt * playerSpeed);
	driftDown = false;
	driftUp = true;
}

void Player::PlayerMoveDown(const float& dt)
{
	player.move(0, .5f * dt * playerSpeed);
	driftDown = true;
	driftUp = false;
}

sf::FloatRect Player::GetBounds()
{
	return player.getGlobalBounds();
}

void Player::Flash(bool change_color)
{
	sf::Color flashColor = sf::Color::Red;

	if (secondPlayer)
		flashColor = sf::Color::Blue;

	if (change_color)
	{
		player.setFillColor(flashColor);
	}
	else
	{
		player.setFillColor(sf::Color::White);
	}
}

void Player::PlayerUpgrades(unsigned upgradeVal)
{
	switch (upgradeVal)
	{
	case 1:
		if (playerSpeed < 550.f)
			playerSpeed += 50.f;
		break;
	
	case 3:
		if (player.getSize().y < 130.f)
			player.setSize(sf::Vector2f(35.f, 130.f));
		break;

	case 6:
		if (playerSpeed < 700.f)
			playerSpeed = 700.f; 
		break;
	default:
		break;
	
	}
}

void Player::UpdatePlayerMovement(const float& dt)
{
	if (!secondPlayer)
	{
		// ====================================================================================================
		// Player 1 Movement
		// ====================================================================================================
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			player.move(0, -.5f * dt * playerSpeed);
			driftDown = false;
			driftUp = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			player.move(0, .5f * dt * playerSpeed);
			driftDown = true;
			driftUp = false;

		}
		// Player 1 Drift Up
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && driftUp)
		{
			player.move(0, -.05f * dt * playerSpeed);
		}
		// Player 1 Drift Down
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && driftDown)
		{
			player.move(0, .05f * dt * playerSpeed);
		}

		//Top of the Screen
		if (player.getPosition().y - (player.getGlobalBounds().height - 40.f) <= 0)
		{
			player.setPosition(player.getPosition().x, 0.f + (player.getGlobalBounds().height - 40.f));
			driftDown = true;
			driftUp = false;
		}
		//Bottom of the Screen
		if (player.getPosition().y + player.getGlobalBounds().height >= maxPlayerDown)
		{
			player.setPosition(player.getPosition().x, maxPlayerDown - player.getGlobalBounds().height);
			driftDown = false;
			driftUp = true;
		}
	}
	else if (secondPlayer && !bPlayerAIOn)
	{

		// ====================================================================================================
		// Player  Movement
		// ====================================================================================================
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			player.move(0, -.5f * dt * playerSpeed);

			driftDown = false;
			driftUp = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			player.move(0, .5f * dt * playerSpeed);
			driftDown = true;
			driftUp = false;
		}

		// Player 1 Drift Up
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && driftUp)
		{
			player.move(0, -.05f * dt * playerSpeed);
		}
		// Player 1 Drift Down
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && driftDown)
		{
			player.move(0, .05f * dt * playerSpeed);
		}

		//Top of the Screen
		if (player.getPosition().y - (player.getGlobalBounds().height - 40.f) <= 0)
		{
			player.setPosition(player.getPosition().x, 0.f + (player.getGlobalBounds().height - 40.f));
			driftDown = true;
			driftUp = false;
		}
		//Bottom of the Screen
		if (player.getPosition().y + player.getGlobalBounds().height >= maxPlayerDown)
		{
			player.setPosition(player.getPosition().x, maxPlayerDown - player.getGlobalBounds().height);
			driftDown = false;
			driftUp = true;
		}
	}
}

void Player::Update(const float& dt)
{
	UpdatePlayerMovement(dt);
}

void Player::Render(sf::RenderTarget & target)
{
	target.draw(player);
}
