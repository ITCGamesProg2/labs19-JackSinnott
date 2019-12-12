#pragma once
#include <SFML/Graphics.hpp>
#include "MathUtility.h"
#include "CollisionDetector.h"
#include "Tank.h"
#include <Thor/Vectors.hpp>
#include <Thor/Time.hpp>
#include <ScreenSize.h>

class Projectile
{
public:
	Projectile(sf::Texture const& texture, std::vector<sf::Sprite>& wallSprites, std::vector<sf::Sprite>& enemySprite);

	void update(double dt);
	void render(sf::RenderWindow &m_win);

	/// <summary>
	/// @brief Sets position of bullets in the window 
	/// </summary>
	/// <param name="m_position"></param>
	void setPosition(sf::Vector2f m_position);

	/// <summary>
	/// @brief Used to reset velocity ti zero if bullet hits target
	/// </summary>
	void setVelocity(sf::Vector2f m_velocity);

	void boundaryCheck();
	bool hasfired();

	/// <summary>
	/// @brief Checks for collisions between the bullet and the walls.
	/// 
	/// </summary>
	/// <returns>True if collision detected between bullet and wall.</returns>
	bool checkWallCollision();

	/// <summary>
	/// ~brief Checks for collision between the bullet and enemies
	/// </summary>
	/// <returns>True if collision detected between the bullets and enemies</returns>
	bool checkEnemyCollision(int t_index);

	/// <summary>
	/// @brief Gets the key input to know firing is true
	/// </summary>
	/// <returns> True if space button is pressed </returns>
	void handleKeyInput(sf::Vector2f m_position);

	int shotFired();
	int accuracyRate();
	/// <summary>
	/// @brief Assigns the rotation and movement to bullet
	/// </summary>
	void fired(double t_rotation);

private:
	/// <summary>
	/// @brief Assigns the textures to sprites and sets up intRect.
	/// </summary>
	void initSprites();

	// Gives the bullet its position in the window
	sf::Vector2f position;

	// Imposes changes in position
	sf::Vector2f velocity;
	
	// The rotation of the bullet
	double m_rotation;

	// The speed of the bullets
	double m_speed = 1000;;

	// Data variables for drawing the images
	sf::Sprite m_bullet;
	sf::Texture const &m_texture;

	thor::Timer m_rateOfFire;
	sf::Time m_fireTime;

	// data variables for collision detection
	std::vector<sf::Sprite>& m_wallSprites;
	std::vector<sf::Sprite>& m_enemySprites;

	// Bool to check if bullet has been shot
	bool shot = false;

	bool shooting = false;

	// Players accuracy in the game
	int accuracy = 1;

	bool bulletInOrbit = false;

	int shotsFired = 1;

};