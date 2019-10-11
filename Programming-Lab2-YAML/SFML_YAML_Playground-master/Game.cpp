#include "Game.h"
#include <iostream>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_height, ScreenSize::s_width, 32), "SFML Playground", sf::Style::Default)
{
	m_window.setVerticalSyncEnabled(true);

	m_level.m_tank.m_position = { 850, 100 };
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

	if (!m_bgTexture.loadFromFile("Background.jpg"))
	{
		std::cout << "Error loading background image" << std::endl;
	}
	m_bgSprite.setTexture(m_bgTexture);

	if (!m_tankTexture.loadFromFile("E-100.png"))
	{
		std::cout << "Error loading tank image" << std::endl;
	}
	m_tankSprite.setTexture(m_tankTexture);
	if (!m_spriteSheetTexture.loadFromFile("SpriteSheet.png"))
	{
		std::string errorMsg("Error loading texture");
		throw std::exception(errorMsg.c_str());
	}

	// Extract the wall image from the spritesheet.
	sf::Sprite sprite;
	sf::IntRect wallRect(2, 129, 33, 23);
	sprite.setTexture(m_spriteSheetTexture);
	sprite.setTextureRect(wallRect);
	// Loop through each Obstacle instance - recall that Obstacles are structs
	for (auto& obstacle : m_level.m_obstacles)
	{
		// Position the wall sprite using the obstacle data
		sprite.setPosition(obstacle.m_position);
		sprite.rotate(obstacle.m_rotation);
		m_sprites.push_back(sprite);
	}

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
		case sf::Keyboard::Up:
			// Up key was pressed...
			break;
		default:
			break;
		}
	}
}

////////////////////////////////////////////////////////////
void Game::update(double dt)
{

}

////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));
	m_window.draw(m_bgSprite);
	m_window.draw(m_tankSprite);

	for (sf::Sprite& sprite : m_sprites)
	{
		m_window.draw(sprite);
	}
	/*for (int i = 0; i < 3; i++)
	{
		m_window.draw(m_sprites.at(i)); throws exception in boundary errors
	}*/
	m_window.display();
}





