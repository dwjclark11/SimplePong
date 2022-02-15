#pragma once

class Ball
{
private:
	sf::CircleShape mBall;
	float mRadius;
	float mSpeed;
	float mRotation;
	int mLevel;
	// Ball Directions
	bool mUp;
	bool mDown;
	bool mLeft;
	bool mRight;

public:
	Ball(float radius, const sf::Texture* texture);
	~Ball();
	void SetStartPosition(sf::Window& window);
	void SetPosition(float x, float y) { mBall.setPosition(sf::Vector2f(x, y)); }
	const sf::Vector2f GetPosition() const { return mBall.getPosition(); }
	const sf::FloatRect GetGlobalBounds() const { return mBall.getGlobalBounds(); }
	void SetBallMovement(float dir, float moveSpeed, float ballVert, const float dt);
	void SetBallFillColor(sf::Color color) { mBall.setFillColor(color); }
	void SetBallOutlineColor(sf::Color color) { mBall.setOutlineColor(color); }
	void SetBallOutlineThickness(float thickness) { mBall.setOutlineThickness(thickness); }
	
	const sf::CircleShape GetBall() const { return mBall; }
	void SetTextureRect(sf::IntRect intRect) { mBall.setTextureRect(intRect); }

	void SetBallDown(bool down) { mDown = down; }
	void SetBallUp(bool up) { mUp = up; }
	const bool GetBallUp() const { return mUp; }
	const bool GetBallDown() const { return mDown; }
	void SetBallLeft(bool left) { mLeft = left; }
	void SetBallRight(bool right) { mRight = right; }
	const bool GetBallLeft() const { return mLeft; }
	const bool GetBallRight() const { return mRight; }
	void SetSpeed(float speed) { mSpeed = speed; }
	const float GetSpeed() const { return mSpeed; }
	void IncreaseLevel() { mLevel++; }
	void ResetLevel() { mLevel = 1; }
	const int GetLevel() const { return mLevel; }
	void UpdateRotation() { mBall.rotate(mRotation); }
	void SetRotationDir(bool clockwise);
};