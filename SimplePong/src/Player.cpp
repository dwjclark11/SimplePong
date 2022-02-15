#include "stdafx.h"
#include "Player.h"

Player::Player(float xPos, float yPos, float max_down_pos, sf::Color color, const sf::Texture* texture, bool second_player)
	: mDriftUp(false)
	, mDriftDown(false)
	, mRight(false)
	, mLeft(false)
	, mPlayerAIOn(false)
	, mSpeedDifficulty(1)
	, mBallUp(false)
	, mBallDown(false)
	, mUp(false)
	, mDown(false)
{
	mPlayer.setFillColor(color);
	mPlayer.setTexture(texture);
	mPlayer.setSize(sf::Vector2f(20, 200));
	mPlayer.setPosition(sf::Vector2f(xPos, yPos));

	mMaxPlayerDown = max_down_pos;
	mPlayerSpeed = 1200.f;
	mSecondPlayer = second_player;
	
}

Player::~Player()
{

}

void Player::PlayerAIDrift(const float& dt)
{

	//Top of the Screen
	if (mPlayer.getPosition().y - (mPlayer.getGlobalBounds().height - 40.f) <= 0)
	{
		mPlayer.setPosition(mPlayer.getPosition().x, 0.f + (mPlayer.getGlobalBounds().height - 40.f));
		mDriftDown = true;
		mDriftUp = false;
	}

	// Player 1 Drift Up
	if (mDriftUp)
	{
		mPlayer.move(0, -.05f * dt * mPlayerSpeed);
	}

	//Bottom of the Screen
	if (mPlayer.getPosition().y + mPlayer.getGlobalBounds().height >= mMaxPlayerDown)
	{
		mPlayer.setPosition(mPlayer.getPosition().x, mMaxPlayerDown - mPlayer.getGlobalBounds().height);
		mDriftDown = false;
		mDriftUp = true;
	}

	// Player 1 Drift Down
	if (mDriftDown)
	{
		mPlayer.move(0, .05f * dt * mPlayerSpeed);
	}
}

void Player::PlayerAIOn(bool AIOn)
{
	if (AIOn)
		mPlayerAIOn = true;
	else
		mPlayerAIOn = false;
}

float Player::GetPlayerYPosition()
{
	return mPlayer.getPosition().y;
}

void Player::PlayerMoveUP(const float& dt)
{
	mPlayer.move(0, -.5f * dt * mPlayerSpeed);
	mDriftDown = false;
	mDriftUp = true;
}

void Player::PlayerMoveDown(const float& dt)
{
	mPlayer.move(0, .5f * dt * mPlayerSpeed);
	mDriftDown = true;
	mDriftUp = false;
}

sf::FloatRect Player::GetBounds()
{
	return mPlayer.getGlobalBounds();
}

void Player::Flash(bool change_color)
{
	sf::Color flashColor = sf::Color::Red;

	if (mSecondPlayer)
		flashColor = sf::Color::Blue;

	if (change_color)
	{
		mPlayer.setFillColor(flashColor);
	}
	else
	{
		mPlayer.setFillColor(sf::Color::White);
	}
}

void Player::PlayerUpgrades(unsigned upgradeVal)
{
	switch (upgradeVal)
	{
	case 1:
		if (mPlayerSpeed < 550.f)
			mPlayerSpeed += 50.f;
		break;
	
	case 3:
		if (mPlayer.getSize().y < 130.f)
			mPlayer.setSize(sf::Vector2f(35.f, 130.f));
		break;

	case 6:
		if (mPlayerSpeed < 700.f)
			mPlayerSpeed = 700.f; 
		break;
	default:
		break;
	
	}
}

void Player::UpdatePlayerMovement(const float& dt)
{
	if (!mSecondPlayer)
	{
		// ====================================================================================================
		// Player 1 Movement
		// ====================================================================================================
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			mPlayer.move(0, -.5f * dt * mPlayerSpeed);
			mDriftDown = false;
			mDriftUp = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			mPlayer.move(0, .5f * dt * mPlayerSpeed);
			mDriftDown = true;
			mDriftUp = false;

		}
		// Player 1 Drift Up
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mDriftUp)
		{
			mPlayer.move(0, -.05f * dt * mPlayerSpeed);
		}
		// Player 1 Drift Down
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && mDriftDown)
		{
			mPlayer.move(0, .05f * dt * mPlayerSpeed);
		}

		//Top of the Screen
		if (mPlayer.getPosition().y - (mPlayer.getGlobalBounds().height - 40.f) <= 0)
		{
			mPlayer.setPosition(mPlayer.getPosition().x, 0.f + (mPlayer.getGlobalBounds().height - 40.f));
			mDriftDown = true;
			mDriftUp = false;
		}
		//Bottom of the Screen
		if (mPlayer.getPosition().y + mPlayer.getGlobalBounds().height >= mMaxPlayerDown)
		{
			mPlayer.setPosition(mPlayer.getPosition().x, mMaxPlayerDown - mPlayer.getGlobalBounds().height);
			mDriftDown = false;
			mDriftUp = true;
		}
	}
	else if (mSecondPlayer && !mPlayerAIOn)
	{

		// ====================================================================================================
		// Player  Movement
		// ====================================================================================================
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			mPlayer.move(0, -.5f * dt * mPlayerSpeed);

			mDriftDown = false;
			mDriftUp = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			mPlayer.move(0, .5f * dt * mPlayerSpeed);
			mDriftDown = true;
			mDriftUp = false;
		}

		// Player 1 Drift Up
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && mDriftUp)
		{
			mPlayer.move(0, -.05f * dt * mPlayerSpeed);
		}
		// Player 1 Drift Down
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mDriftDown)
		{
			mPlayer.move(0, .05f * dt * mPlayerSpeed);
		}

		//Top of the Screen
		if (mPlayer.getPosition().y - (mPlayer.getGlobalBounds().height - 40.f) <= 0)
		{
			mPlayer.setPosition(mPlayer.getPosition().x, 0.f + (mPlayer.getGlobalBounds().height - 40.f));
			mDriftDown = true;
			mDriftUp = false;
		}
		//Bottom of the Screen
		if (mPlayer.getPosition().y + mPlayer.getGlobalBounds().height >= mMaxPlayerDown)
		{
			mPlayer.setPosition(mPlayer.getPosition().x, mMaxPlayerDown - mPlayer.getGlobalBounds().height);
			mDriftDown = false;
			mDriftUp = true;
		}
	}
}

void Player::Update(const float& dt)
{
	UpdatePlayerMovement(dt);
}

void Player::Render(sf::RenderTarget & target)
{
	target.draw(mPlayer);
}
