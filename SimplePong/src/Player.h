#pragma once

class Player
{
private:
	sf::RectangleShape player;

	float movementSpeed;
	bool driftUp;
	bool driftDown;

	bool bUp;
	bool bDown;

	bool secondPlayer;
	bool bPlayerAIOn;

	float maxPlayerDown;
	bool bLeft;
	bool bRight;
	unsigned speedDifficulty;
	float ballUp;
	float ballDown;

	float playerSpeed;
public:
	Player(float xPos, float yPos, float max_down_pos, sf::Color color, const sf::Texture* texture, bool second_player);
	~Player();

	void PlayerAIDrift(const float& dt);
	void PlayerAIOn(bool AIOn);
	bool IsPlayerAI() { return bPlayerAIOn; }
	float GetPlayerYPosition();
	void PlayerMoveUP(const float& dt);
	void PlayerMoveDown(const float& dt);
	sf::FloatRect GetBounds();
	void Flash(bool change_color);
	void PlayerUpgrades(unsigned upgradeVal);

	void UpdatePlayerMovement(const float& dt);
	void Update(const float& dt);
	void Render(sf::RenderTarget& target);
};

