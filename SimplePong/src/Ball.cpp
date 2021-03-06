#include "stdafx.h"
#include "Ball.h"

Ball::Ball(float radius, const sf::Texture* texture)
	: mUp(false)
	, mDown(false)
	, mSpeed(650.f)
	, mRadius(50.f)
	, mRotation(1000.f)
	, mLevel(1)
	, mLeft(false)
	, mRight(false)
{
	mBall.setRadius(radius);
	mBall.setFillColor(sf::Color::White);
	mBall.setTexture(texture);
	mBall.setTextureRect(sf::IntRect(0, 0, 128, 128));
	mBall.setOrigin(sf::Vector2f(mRadius, mRadius));

}

Ball::~Ball()
{

}

void Ball::SetStartPosition(sf::Window& window)
{
	mBall.setPosition(sf::Vector2f((window.getSize().x / 2) - mBall.getGlobalBounds().width, (window.getSize().y / 2) - mBall.getGlobalBounds().width));
}

void Ball::SetBallMovement(float dir, float ballVert, const float dt)
{
	mBall.move(dir * mSpeed * dt * mLevel, ballVert * dt * (mSpeed / 5) * mLevel);
}

void Ball::SetRotationDir(bool clockwise)
{
	if (clockwise)
		mRotation = 1000.f;
	else
		mRotation = -1000.f;
}
