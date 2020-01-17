#pragma once
#include <SFML/Graphics.hpp>
#include "MathUtility.h"
#include "CollisionDetector.h"
#include "ProjectilePool.h"


/// <summary>
/// @brief A simple tank controller.
/// 
/// This class will manage all tank movement and rotations.
/// </summary>
class Tank
{
public:	
	Tank(sf::Texture const& texture, std::vector<sf::Sprite>& wallSprites, std::vector<sf::Sprite>& enemySprite);

	void update(double dt);
	void render(sf::RenderWindow & window);
	
	/// <summary>
	/// @Brief Increases the speed by 1, max speed is capped at 100
	/// </summary>
	void increaseSpeed();

	// @brief Assigns position in window to tank
	void setPosition(int x, int y);

	sf::Vector2f getPosition() const;

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

	/// <summary>
	/// @brief Adjust the rotation of the tank and turret when a collision happens
	/// </summary>
	void adjustRotation();

	/// <summary>
	/// @brief Increases the turret rotation by 1 degrees, wraps to 359 degrees after 0.
	/// </summary>
	void increaseTurretRotation();

	/// <summary>
	/// @brief Decreses the turret rotation by 1 degrees, wraps to 0 after 259 degrees.
	/// </summary>
	void decreaseTurretRotation();

	// Processes control keys and applies speed/rotation as appropriate
	void handleKeyInput();

	// The tank speed.
	double m_speed{ 0.0 };

	// The tanks previous speed before update.
	double m_previousSpeed;

	// The current rotation as applied to tank base.
	double m_rotation{ 0.0 };

	// The last rotation before update of the tank base.
	double m_previousRotation;

	// The current rotation as applied to turret.
	double m_turretRotation{ 0.0 };

	// The last rotation before update as applied to the turret.
	double m_previousTurretRotation;

	/// <summary>
	/// @brief Generates a request to fire a projectile.
	/// A projectile will be fired from the tip of the turret only if time limit between shots
	///  has expired. Fire requests are not queued.
	/// </summary>
	void requestFire();


private:
	/// <summary>
	/// @brief assign textures to sprites and assign values to intRect for both turret and tank.
	/// </summary>
	void initSprites();

	// The sprites for the tank base and tank turret.
	sf::Sprite m_tankBase;
	sf::Sprite m_turret;

	// Single texture for both sprite images .
	sf::Texture const & m_texture;

	// The position in window of the tank.
	sf::Vector2f position{ 0,0 };

	// The previous position before update of the tank.
	sf::Vector2f m_previousPosition;

	// A reference to the container of wall sprites.
	std::vector<sf::Sprite>& m_wallSprites;

	// A reference to the container of enemy sprites.
	std::vector<sf::Sprite>& m_enemySprites;

	// Bool to check if rotation has been applied
	bool m_enableRotation = true;

	// Instance of the projectile pool so the tank can shoot bullets
	ProjectilePool m_pool;

	// The delay time between shots in milliseconds.
	static int const s_TIME_BETWEEN_SHOTS{ 800 };

	bool m_fireRequested = false;

	int m_shootTimer{ 800 };
	
};
