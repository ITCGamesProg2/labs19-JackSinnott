#include "Tank.h"
#include "LevelLoader.h"
#include "CollisionDetector.h"

/// <summary>
/// @brief Constructor that stores drawable state (texture, sprite) for the tank.
/// Stores references to the texture and container of wall sprites. 
/// Creates sprites for the tank base and turret from the supplied texture.
/// </summary>
/// <param name="texture">A reference to the sprite sheet texture</param>
///< param name="texture">A reference to the container of wall sprites</param>  
Tank::Tank(sf::Texture const& texture, std::vector<sf::Sprite>& wallSprites, std::vector<sf::Sprite>& enemySprites)
	: m_texture(texture)
	, m_wallSprites(wallSprites)
	, m_enemySprites(enemySprites)

{
	// Initialises the tank base and turret sprites.
	initSprites();
}

void Tank::update(double dt)
{

	position.x = (m_tankBase.getPosition().x + cos(m_rotation * MathUtility::DEG_TO_RAD) * m_speed * (dt / 1000));
	position.y = (m_tankBase.getPosition().y + sin(m_rotation * MathUtility::DEG_TO_RAD) * m_speed * (dt / 1000));
	handleKeyInput();
	m_tankBase.setPosition(position);
	m_tankBase.setRotation(m_rotation);

	position.x = (m_tankBase.getPosition().x + cos(m_turretRotation * MathUtility::DEG_TO_RAD) * m_speed * (dt / 1000));
	position.y = (m_tankBase.getPosition().y + sin(m_turretRotation * MathUtility::DEG_TO_RAD) * m_speed * (dt / 1000));

	m_turret.setPosition(position);
	m_turret.setRotation(m_turretRotation);

	m_speed *= 0.999;

	if (checkWallCollision())
	{
		deflect();
	}

	m_pool.update(dt, m_wallSprites);
	m_shootTimer -= dt;
	if (m_shootTimer <= 0)
	{
		m_shootTimer = s_TIME_BETWEEN_SHOTS;
		m_fireRequested = false;
	}
}

void Tank::render(sf::RenderWindow & window) 
{
	window.draw(m_tankBase);
	window.draw(m_turret);
	m_pool.render(window);
}

void Tank::increaseSpeed()
{
	m_previousSpeed = m_speed;
	if (m_speed < 100.0)
	{
		m_speed += 1;
	}
}

void Tank::setPosition(int x, int y)
{
	m_tankBase.setPosition(x, y);
	m_turret.setPosition(x, y);
}

sf::Vector2f Tank::getPosition()  const
{
	return position;
}

void Tank::decreaseSpeed()
{
	m_previousSpeed = m_speed;
	if (m_speed > -100.0)
	{
		m_speed -= 1;
	}
}

void Tank::increaseRotation()
{
	m_previousRotation = m_rotation;
	m_previousTurretRotation = m_turretRotation;
	m_rotation += 1;
	m_turretRotation += 1;
	if (m_rotation == 360.0)
	{
		m_rotation = 0;
	}
}

void Tank::decreaseRotation()
{
	m_previousRotation = m_rotation;
	m_previousTurretRotation = m_turretRotation;
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
	m_previousTurretRotation = m_turretRotation;
	if (m_turretRotation == 360.0)
	{
		m_turretRotation = 0;
	}
}

void Tank::decreaseTurretRotation()
{
	m_turretRotation -= 1;
	m_previousTurretRotation = m_turretRotation;
	if (m_turretRotation == 0.0)
	{
		m_turretRotation = 359.0;
	}

	sf::Vector2f rotatedVector = thor::rotatedVector(sf::Vector2f(1, 0), m_turret.getRotation());

}

bool Tank::checkWallCollision()
{
	for (sf::Sprite const& sprite : m_wallSprites)
	{
		// Checks if either the tank base or turret has collided with the current wall sprite.
		if (CollisionDetector::collision(m_turret, sprite) ||
			CollisionDetector::collision(m_tankBase, sprite))
		{
			return true;
		}
	}
	return false;
}

void Tank::deflect()
{
	// In case tank was rotating.
	adjustRotation();

	// If tank was moving.
	if (m_speed != 0)
	{
		// Temporarily disable turret rotations on collision.
		m_enableRotation = false;
		// Back up to position in previous frame.
		m_tankBase.setPosition(m_previousPosition);
		// Apply small force in opposite direction of travel.
		if (m_previousSpeed < 0)
		{
			m_speed = 8;
		}
		else
		{
			m_speed = -8;
		}
	}
	else
	{
		m_enableRotation = true;
	}
}

void Tank::adjustRotation()
{
	// If tank was rotating...
	if (m_rotation != m_previousRotation)
	{
		// Work out which direction to rotate the tank base post-collision.
		if (m_rotation > m_previousRotation)
		{
			m_rotation = m_previousRotation - 1;
		}
		else
		{
			m_rotation = m_previousRotation + 1;
		}
	}
	// If turret was rotating while tank was moving
	if (m_turretRotation != m_previousTurretRotation)
	{
		// Set the turret rotation back to it's pre-collision value.
		m_turretRotation = m_previousTurretRotation;
	}
}



void Tank::handleKeyInput()
{
	m_previousPosition = m_tankBase.getPosition();

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
		m_previousTurretRotation = m_turretRotation;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		requestFire();
	}
}


////////////////////////////////////////////////////////////
void Tank::requestFire()
{
	m_fireRequested = true;
	if (m_shootTimer == s_TIME_BETWEEN_SHOTS)
	{
		
		sf::Vector2f tipOfTurret(m_turret.getPosition().x + 2.0f, m_turret.getPosition().y);
		tipOfTurret.x += std::cos(MathUtility::DEG_TO_RAD * m_turret.getRotation()) * ((m_turret.getLocalBounds().top + m_turret.getLocalBounds().height) * 1.7f);
		tipOfTurret.y += std::sin(MathUtility::DEG_TO_RAD * m_turret.getRotation()) * ((m_turret.getLocalBounds().top + m_turret.getLocalBounds().height) * 1.7f);
		m_pool.create(m_texture, tipOfTurret.x, tipOfTurret.y, m_turret.getRotation());
	}
	
}



void Tank::initSprites()
{
	// Initialise the tank base
	m_tankBase.setTexture(m_texture);
	sf::IntRect baseRect(2, 43, 79, 43);
	m_tankBase.setTextureRect(baseRect);
	m_tankBase.setOrigin(baseRect.width / 2.0, baseRect.height / 2.0);
	//m_tankBase.setPosition(100);

	// Initialise the turret
	m_turret.setTexture(m_texture);
	sf::IntRect turretRect(19, 1, 83, 31);
	m_turret.setTextureRect(turretRect);
	m_turret.setOrigin(turretRect.width / 3.0, turretRect.height / 2.0);
	//m_turret.setPosition(100);

}