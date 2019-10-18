#pragma once
#include <SFML/Graphics.hpp>
#include "MathUtility.h"


/// <summary>
/// @brief A simple tank controller.
/// 
/// This class will manage all tank movement and rotations.
/// </summary>
class Tank
{
public:	
	Tank(sf::Texture const& texture, std::vector<sf::Sprite>& wallSprites);
	void update(double dt);
	void render(sf::RenderWindow & window);
	
	/// <summary>
	/// @Brief Increases the speed by 1, max speed is capped at 100
	/// </summary>
	void increaseSpeed();

	void setPosition();

	/// <summary>
	/// @brief Decreases the speed by 1, min speed is capped at -100.
	/// 
	/// </summary>
	void decreaseSpeed();

	/// <summary>
	/// @brief Increases the rotation by 1 degree, wraps to 0 degrees after 359.
	/// 
	/// </summary>
	void increaseRotation();

	/// <summary>
	/// @brief Decreases the rotation by 1 degree, wraps to 359 degrees after 0.
	/// 
	/// </summary>
	void decreaseRotation();

	void increaseTurretRotation();

	void decreaseTurretRotation();

	// Processes control keys and applies speed/rotation as appropriate
	void handleKeyInput();

	// The tank speed.
	double m_speed{ 0.0 };

	// The current rotation as applied to tank base.
	double m_rotation{ 0.0 };

	double m_turretRotation{ 0.0 };

private:
	void initSprites();
	sf::Sprite m_tankBase;
	sf::Sprite m_turret;
	sf::Texture const & m_texture;
	sf::Vector2f position{ 0,0 };
	// A reference to the container of wall sprites.
	std::vector<sf::Sprite>& m_wallSprites;
};
