#pragma once
#include <SFML/Graphics.hpp>
#include "MathUtility.h"
#include <collection.h>


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

	/// <summary>
/// @brief Checks for collisions between the tank and the walls.
/// 
/// </summary>
/// <returns>True if collision detected between tank and wall.</returns>
	bool checkWallCollision();

	/// <summary>
/// @brief Stops the tank if moving and applies a small increase in speed in the opposite direction of travel.
/// If the tank speed is currently 0, the rotation is set to a value that is less than the previous rotation value
///  (scenario: tank is stopped and rotates into a wall, so it gets rotated towards the opposite direction).
/// If the tank is moving, further rotations are disabled and the previous tank position is restored.
/// The tank speed is adjusted so that it will travel slowly in the opposite direction. The tank rotation 
///  is also adjusted as above if necessary (scenario: tank is both moving and rotating, upon wall collision it's 
///  speed is reversed but with a smaller magnitude, while it is rotated in the opposite direction of it's 
///  pre-collision rotation).
/// </summary>
	void deflect();

	void adjustRotation();

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
	float m_previousRotation;
	float m_previousTurretRotation;
	bool m_enableRotation = true;
};
