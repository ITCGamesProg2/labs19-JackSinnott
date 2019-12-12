#include "Projectile.h"

Projectile::Projectile(sf::Texture const& texture, std::vector<sf::Sprite>& wallSprites, std::vector<sf::Sprite>& enemySprite)
	: m_texture(texture),
	m_wallSprites(wallSprites),
	m_enemySprites(enemySprite)
{
	
	initSprites();
	m_fireTime = sf::milliseconds(1000);
	m_rateOfFire.reset(m_fireTime);
	m_rateOfFire.start();
}

void Projectile::update(double dt)
{
   	position.x += velocity.x * (dt / 1000);
	position.y += velocity.y * (dt / 1000);
	m_bullet.setPosition(position);
	boundaryCheck();
}

void Projectile::render(sf::RenderWindow &m_win)
{
	m_win.draw(m_bullet);
}

void Projectile::setPosition(sf::Vector2f m_position)
{
	position = m_position;
	
}

void Projectile::setVelocity(sf::Vector2f m_velocity)
{
	velocity.x = m_velocity.x;
	velocity.y = m_velocity.y;
}

void Projectile::boundaryCheck()
{
	if (position.x < 0 || position.x > ScreenSize::s_height)
	{
		position = { -100,-100 };
		velocity = { 0,0 };
	}
	if (position.y < 0 || position.y > ScreenSize::s_width)
	{
		position = { -100,-100 };
		velocity = { 0,0 };
	}

}

bool Projectile::hasfired()
{
	return bulletInOrbit;
}

bool Projectile::checkWallCollision()
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

bool Projectile::checkEnemyCollision(int t_index)
{
	
	if (CollisionDetector::collision(m_bullet, m_enemySprites[t_index]))
	{
		shotsFired++;
		return true;
	}
	
	return false;
}

 void Projectile::handleKeyInput(sf::Vector2f m_position)
{
	 if (m_rateOfFire.isExpired())
	 {

		 setPosition(m_position);
		 position = m_position;
		 shot = true;
		 m_rateOfFire.restart(m_fireTime);
		 bulletInOrbit = true;

	 }
}

 int Projectile::shotFired()
 {
	 return shotsFired;
 }

 int Projectile::accuracyRate()
 {
	 return accuracy;
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
			shooting = true;
			if (shooting)
			{
				accuracy++;
			}
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

