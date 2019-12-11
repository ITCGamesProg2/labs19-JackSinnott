#include "Projectile.h"

Projectile::Projectile(sf::Texture const& texture, std::vector<sf::Sprite>& wallSprites)
	: m_texture(texture),
	m_wallSprites(wallSprites)
{
	
	initSprites();
	m_fireTime = sf::milliseconds(1000);
	m_rateOfFire.reset(m_fireTime);
	m_rateOfFire.start();
}

void Projectile::update(double dt)
{
	checkCollision();
   	position.x += velocity.x * (dt / 1000);
	position.y += velocity.y * (dt / 1000);
	m_bullet.setPosition(position);
	
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
	 if (m_rateOfFire.isExpired())
	 {
		 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		 {
			 setPosition(m_position);
			 position = m_position;
			 shot = true;
			 m_rateOfFire.restart(m_fireTime);
		 }
	 }
}

void Projectile::fired(double t_rotation)
{
	if (shot == true)
	{
		m_rotation = t_rotation;
		
		if (shot == true)
		{
			velocity.x = cos(t_rotation * MathUtility::DEG_TO_RAD) * m_speed;
			velocity.y = sin(t_rotation * MathUtility::DEG_TO_RAD) * m_speed;
		}
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

