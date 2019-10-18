#include "Tank.h"
#include "LevelLoader.h"

/// <summary>
/// @brief Constructor that stores drawable state (texture, sprite) for the tank.
/// Stores references to the texture and container of wall sprites. 
/// Creates sprites for the tank base and turret from the supplied texture.
/// </summary>
/// <param name="texture">A reference to the sprite sheet texture</param>
///< param name="texture">A reference to the container of wall sprites</param>  
Tank::Tank(sf::Texture const& texture, std::vector<sf::Sprite>& wallSprites)
	: m_texture(texture)
	, m_wallSprites(wallSprites)
{
	// Initialises the tank base and turret sprites.
	initSprites();
}

void Tank::update(double dt)
{	
	handleKeyInput();
	position.x = (m_tankBase.getPosition().x + cos(m_rotation * MathUtility::DEG_TO_RAD) * m_speed * (dt / 1000));
	position.y = (m_tankBase.getPosition().y + sin(m_rotation * MathUtility::DEG_TO_RAD) * m_speed * (dt / 1000));
	
	m_tankBase.setPosition(position);
	m_tankBase.setRotation(m_rotation);
	

	position.x = (m_tankBase.getPosition().x + cos(m_turretRotation * MathUtility::DEG_TO_RAD) * m_speed * (dt / 1000));
	position.y = (m_tankBase.getPosition().y + sin(m_turretRotation * MathUtility::DEG_TO_RAD) * m_speed * (dt / 1000));

	m_turret.setPosition(position);
	m_turret.setRotation(m_turretRotation);
	
	m_speed *= 0.999;
}

void Tank::render(sf::RenderWindow & window) 
{
	window.draw(m_tankBase);
	window.draw(m_turret);
}

void Tank::increaseSpeed()
{
	if (m_speed < 100.0)
	{
		m_speed += 1;
	}
}

void Tank::setPosition()
{
	m_tankBase.setPosition(100, 100);
	m_turret.setPosition(100, 105);
}

void Tank::decreaseSpeed()
{
	if (m_speed > -100.0)
	{
		m_speed -= 1;
	}
}

void Tank::increaseRotation()
{
	m_rotation += 1;
	m_turretRotation += 1;
	if (m_rotation == 360.0)
	{
		m_rotation = 0;
	}
}

void Tank::decreaseRotation()
{
	m_rotation -= 1;
	m_turretRotation -= 1;
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0;
	}
}

void Tank::increaseTurretRotation()
{
	m_turretRotation += 1;
	if (m_turretRotation == 360.0)
	{
		m_turretRotation = 0;
	}
}

void Tank::decreaseTurretRotation()
{
	m_turretRotation -= 1;
	if (m_turretRotation == 0.0)
	{
		m_turretRotation = 359.0;
	}
}

void Tank::handleKeyInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		decreaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		increaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		increaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		decreaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		decreaseTurretRotation();	
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		increaseTurretRotation();	
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		m_turretRotation = m_rotation;
	}
}


void Tank::initSprites()
{
	// Initialise the tank base
	m_tankBase.setTexture(m_texture);
	sf::IntRect baseRect(2, 43, 79, 43);
	m_tankBase.setTextureRect(baseRect);
	m_tankBase.setOrigin(baseRect.width / 2.0, baseRect.height / 2.0);
	m_tankBase.setPosition(100);

	// Initialise the turret
	m_turret.setTexture(m_texture);
	sf::IntRect turretRect(19, 1, 83, 31);
	m_turret.setTextureRect(turretRect);
	m_turret.setOrigin(turretRect.width / 3.0, turretRect.height / 2.0);
	m_turret.setPosition(100);

}