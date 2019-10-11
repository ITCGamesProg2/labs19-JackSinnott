#include "Game.h"
#include <iostream>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_height, ScreenSize::s_width, 32), "SFML Playground", sf::Style::Default)
	, m_tank(m_texture, m_level.m_tank.m_position)
{
	m_window.setVerticalSyncEnabled(true);


	int currentLevel = 1;

	// Invokes our level loader to read the YAML data - will generate an exception if level loading fails.
	try
	{
		LevelLoader::load(currentLevel, m_level);
	}
	catch (std::exception& e)
	{
		std::cout << "Level Loading failure." << std::endl;
		std::cout << e.what() << std::endl;
		throw e;
	}

	if (!m_bgTexture.loadFromFile(m_level.m_background.m_fileName))
	{
		std::cout << "Error loading background image" << std::endl;
	}

	m_bgSprite.setTexture(m_bgTexture);

	if (!m_texture.loadFromFile("./resources/images/SpriteSheet.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	// Now the level data is loaded, set the tank position.
	m_tank.setPosition();

}

////////////////////////////////////////////////////////////
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
	}
}

////////////////////////////////////////////////////////////
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

////////////////////////////////////////////////////////////
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			m_window.close();
			break;
		//case sf::Keyboard::Up:
		//	// Up key was pressed...
		//	m_tank.increaseSpeed();
		//	break;
		//case sf::Keyboard::Down:
		//	m_tank.decreaseSpeed();
		//	break;
		//case sf::Keyboard::Left:
		//	m_tank.decreaseRotation();
		//	break;
		//case sf::Keyboard::Right:
		//	m_tank.increaseRotation();
		//	break;
		default:
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_tank.decreaseRotation();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			m_tank.increaseSpeed();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_tank.increaseRotation();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			m_tank.decreaseSpeed();
		}
	}
}

////////////////////////////////////////////////////////////
void Game::update(double dt)
{
	m_tank.update(dt);
}

////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));
	m_window.draw(m_bgSprite);
	m_tank.render(m_window);

	for (sf::Sprite& obstacle : m_sprites)
	{
		m_window.draw(obstacle);
	}

	m_window.display();
}





