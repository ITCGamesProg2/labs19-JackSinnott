#include "Projectile.h"

Projectile::Projectile(sf::Texture const& texture, std::vector<sf::Sprite>& wallSprites, Tank tank)
	: m_texture(texture),
	m_wallSprites(wallSprites),
	m_tank(tank)
{
	bulletCountdown = sf::seconds(1.0f);
	bulletCount.reset(bulletCountdown);
	bulletCount.start();
	initSprites();
}

void Projectile::update(double dt)
{
	checkCollision();
	m_bullet.setPosition(position);
	sf::Vector2f rotatedVector = thor::rotatedVector(sf::Vector2f(1, 0), m_bullet.getRotation());

	if (rotatedVector.x >= 0 && rotatedVector.y >= 0)
	{
		position.x += 1000;
		position.y += 1000;
	}
	else if (rotatedVector.x < 0 && rotatedVector.y > 0)
	{
		position.x -= 1000;
		position.y += 1000;
	}
	else if (rotatedVector.x > 0 && rotatedVector.y < 0)
	{
		position.x += 1000;
		position.y -= 1000;
	}
	else if (rotatedVector.x < 0 && rotatedVector.y < 0)
	{
		position.x -= 1000;
		position.y -= 1000;
	}
	
}

void Projectile::render(sf::RenderWindow &m_win)
{
	m_win.draw(m_bullet);
}

void Projectile::setPosition(sf::Vector2f m_position)
{
	position = m_position;
	
}

bool Projectile::checkCollision()
{
	for (sf::Sprite const& sprite : m_wallSprites)
	{
		// Checks if the bullet collided with the wall.
		if (CollisionDetector::collision(m_bullet, sprite))
		{
			return true;
		}
	}
	return false;
}

 void Projectile::handleKeyInput(sf::Vector2f m_position)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (bulletCount.isExpired())
		{
			setPosition(m_position);
			shot = true;
		}
	}
}

void Projectile::fired(double dt, sf::Vector2f Position, double t_rotation)
{
	if (shot == true)
	{
		m_rotation = m_tank.m_turretRotation;
		m_speed = 1000;
		bulletCount.restart(bulletCountdown);
		position.x = (position.x + cos(m_rotation * MathUtility::DEG_TO_RAD) * m_speed * (dt / 1000));
		position.y = (Position.y + sin(m_rotation * MathUtility::DEG_TO_RAD) * m_speed * (dt / 1000));
		shot = false;
	}
	
}

void Projectile::initSprites()
{
	// Initialise the bullet
	m_bullet.setTexture(m_texture);
	sf::IntRect baseRect(7, 176, 7, 10);
	m_bullet.setTextureRect(baseRect);
	m_bullet.setOrigin(baseRect.width / 2.0, baseRect.height / 2.0);

}

