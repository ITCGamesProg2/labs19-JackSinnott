#pragma once
#include <SFML/Graphics.hpp>
#include "MathUtility.h"
#include "CollisionDetector.h"
#include "Tank.h"
#include <Thor/Vectors.hpp>
#include <Thor/Time.hpp>

class Projectile
{
public:
	Projectile(sf::Texture const& texture, std::vector<sf::Sprite>& wallSprites, Tank tank);

	void update(double dt);
	void render(sf::RenderWindow &m_win);
	void setPosition(sf::Vector2f m_position);


	/// <summary>
	/// @brief Checks for collisions between the bullet and the walls.
	/// 
	/// </summary>
	/// <returns>True if collision detected between bullet and wall.</returns>
	bool checkCollision();

	/// <summary>
	/// @brief Gets the key input to know firing is true
	/// </summary>
	/// <returns> True if space button is pressed </returns>
	void handleKeyInput(sf::Vector2f m_position);

	/// <summary>
	/// @brief Assigns the rotation and movement to bullet
	/// </summary>
	void fired(double dt, sf::Vector2f m_position, double t_rotation);

private:
	void initSprites();

	// Used to give the bullet its position in the window
	sf::Vector2f velocity;
	sf::Vector2f position;
	double m_rotation;
	double m_speed;

	// Data variables for drawing the images
	sf::Sprite m_bullet;
	sf::Texture const m_texture;

	// data variables for collision detection
	std::vector<sf::Sprite>& m_wallSprites;

	// Tank object for decerning angles
	Tank m_tank;

	sf::Time bulletCountdown;
	thor::Timer bulletCount;
	bool shot = false;
};