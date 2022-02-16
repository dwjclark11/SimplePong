#pragma once

class Player
{
private:
	sf::RectangleShape mPlayer;

	bool mDriftUp;
	bool mDriftDown;

	bool mUp;
	bool mDown;

	bool mSecondPlayer;
	bool mPlayerAIOn;

	float mMaxPlayerDown;
	bool mLeft;
	bool mRight;
	unsigned mSpeedDifficulty;
	float mBallUp;
	float mBallDown;

	float mPlayerSpeed;

public:
	Player(float xPos, float yPos, float max_down_pos, sf::Color color, const sf::Texture* texture, bool second_player);
	~Player();

	void PlayerAIDrift(const float& dt);
	void PlayerAIOn(bool AIOn);
	bool IsPlayerAI() { return mPlayerAIOn; }
	float GetPlayerYPosition();
	void PlayerMoveUP(const float& dt);
	void PlayerMoveDown(const float& dt);
	sf::FloatRect GetBounds();
	void Flash(bool change_color);
	void PlayerUpgrades(unsigned upgradeVal);
	const float& GetPlayerSpeed() const { return mPlayerSpeed; }
	void IncreasePlayerSpeed(float speed) { mPlayerSpeed += speed; }
	void UpdatePlayerMovement(const float& dt);
	void Update(const float& dt);
	void Render(sf::RenderTarget& target);
};
