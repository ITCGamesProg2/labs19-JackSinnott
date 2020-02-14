#include "Game.h"
#include <iostream>

/// <summary>
/// Known bugs: The bullets will sometimes hit enemies even when they are not on screen and the application will bomb out.. This doesn't always happen though
/// </summary>
// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height, 32), "SFML Playground", sf::Style::Default)
	, m_tank(m_texture, m_wallSprites, m_enemySprites)
	, m_aiTank(m_texture, m_wallSprites)
	, m_hud(m_font) // Add this line
	
{
	m_window.setVerticalSyncEnabled(true);
	// --------------------------------------------------------------------------------------------------------------------
	// Invokes our level loader to read the YAML data - will generate an exception if level loading fails.
	int currentLevel = 1;

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
	// --------------------------------------------------------------------------------------------------------------------
	// Timer initalisations 
	// --------------------------------------------------------------------------------------------------------------------
	m_gameOverTimer = sf::seconds(60.f);
	m_enemySpawnTime = sf::milliseconds(8000);
	m_stopWatch.start();
	m_time.reset(m_gameOverTimer);
	m_enemySpawn.reset(m_enemySpawnTime);
	// --------------------------------------------------------------------------------------------------------------------
	// Loading from files
	// --------------------------------------------------------------------------------------------------------------------
	if (!all_Purpose_Font.loadFromFile("./resources/fonts/calibri.ttf"))
	{
		std::cout << "problem loading font file" << std::endl;
	}
	if (!m_bgTexture.loadFromFile(m_level.m_background.m_fileName))
	{
		std::cout << "Error loading background image" << std::endl;
	}
	if (!m_texture.loadFromFile("./resources/images/SpriteSheet.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	// --------------------------------------------------------------------------------------------------------------------

	// Assign loaded data from files to values
	// --------------------------------------------------------------------------------------------------------------------
	HUD_Text.setFont(all_Purpose_Font);
	scoreText.setFont(all_Purpose_Font);
	m_bgSprite.setTexture(m_bgTexture);
	// --------------------------------------------------------------------------------------------------------------------
	// Give loaded values a set of parameters
	// --------------------------------------------------------------------------------------------------------------------
	sf::Vector2f HUD_Center = sf::Vector2f(HUD_Text.getLocalBounds().width / 2.0f, HUD_Text.getLocalBounds().height / 2.0f);
	HUD_Text.setOrigin(HUD_Center);
	HUD_Text.setPosition(m_window.getSize().x * 0.4f, 20.f);
	scoreText.setPosition(50, 100);
	HUD_Text.setFillColor(sf::Color::Black);
	scoreText.setFillColor(sf::Color::Black);

	sf::Vector2f score_Center = sf::Vector2f(scoreText.getLocalBounds().width / 2.0f, scoreText.getLocalBounds().height / 2.0f);
	scoreText.setOrigin(score_Center);
	// --------------------------------------------------------------------------------------------------------------------
	// Functions we want called upon creation
	// --------------------------------------------------------------------------------------------------------------------
	generateWalls();
	generateEnemies();
	randomTankSpawn();
	// Populate the obstacle list and set the AI tank position
	m_aiTank.init(m_level.m_aiTank.m_position);
	// --------------------------------------------------------------------------------------------------------------------

	if (!m_font.loadFromFile("./resources/fonts/calibri.ttf"))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
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
	
	}
}

////////////////////////////////////////////////////////////
void Game::generateWalls()
{

	sf::IntRect wallRect(2, 129, 33, 23);
	// Create the Walls 
	for (ObstacleData const& obstacle : m_level.m_obstacles)
	{
		wallSprite.setTexture(m_texture);
		wallSprite.setTextureRect(wallRect);
		wallSprite.setOrigin(wallRect.width / 2.0, wallRect.height / 2.0);
		wallSprite.setPosition(obstacle.m_position);
		wallSprite.setRotation(obstacle.m_rotation);
		m_wallSprites.push_back(wallSprite);
	}
}

////////////////////////////////////////////////////////////
void Game::generateEnemies()
{
	//sf::IntRect enemyRect(107, 42, 77, 43);
	// Create the enemies
	//for (EnemyData const& enemy : m_level.m_enemies)
	//{
	//	enemySprite.setTexture();
	//	//enemySprite.setTextureRect(enemyRect);
	//	enemySprite.setScale(.05, .05);
	//	
	//}
}

///////////////////////////////////////////////////////
void Game::enemyUpdatedPosition()
{
	int sign = rand() % 2;
	if (sign == 0)
	{
		sign = -1;
	}
	// Set Positions of enemies
	for (EnemyData const& enemy : m_level.m_enemies)
	{	
		enemySprite.setPosition(sf::Vector2f(enemy.m_position.x + (enemy.m_offset.x * sign), enemy.m_position.y + (enemy.m_offset.y * sign)));
		m_enemySprites.push_back(enemySprite);
	}
	// Change position of enemies so they respawn elsewhere
	if (enemySprite.getPosition() == enemySprite.getPosition())
	{
		enemySprite.setPosition(enemySprite.getPosition().x + (m_level.m_enemies.at(0).m_offset.x * sign),
			enemySprite.getPosition().y + (m_level.m_enemies.at(0).m_offset.y * sign));
	}
	switchEnemy = false;
}

	/// <summary>
	/// @brief switch statement to spawn tank in random corner and set its rotation to be
	/// facing the middle of the screen
	/// </summary>
void Game::randomTankSpawn()
{
	int spawnCorner = (rand() % 4) + 1;
	switch (spawnCorner)
	{
	case 1: spawnCorner == 1;
		m_tank.setPosition(30, 30);
		m_tank.m_rotation = 45;
		m_tank.m_turretRotation = 45;
		break;
	case 2: spawnCorner == 2;
		m_tank.setPosition(1410, 30);
		m_tank.m_rotation = 136;
		m_tank.m_turretRotation = 136;
		break;
	case 3: spawnCorner == 3;
		m_tank.setPosition(30, 870);
		m_tank.m_rotation = 313;
		m_tank.m_turretRotation = 313;
		break;
	case 4: spawnCorner == 4;
		m_tank.setPosition(1410, 870);
		m_tank.m_rotation = 225;
		m_tank.m_turretRotation = 225;
		break;
	default:
		break;
	}
}







////////////////////////////////////////////////////////////
void Game::update(double dt)
{
	m_time.start();
	
	m_hud.update(m_gameState);

	if (m_aiTank.getHealth() == 0)
	{
		m_gameState = GameState::GAME_WIN;
	}
	switch (m_gameState)
	{
	case GameState::GAME_RUNNING:
		m_tank.update(dt, m_aiTank);
		m_aiTank.update(m_tank, dt);
		break;
	case GameState::GAME_WIN:
		break;
	case GameState::GAME_LOSE:
		timeForGameRestart += dt;
		if (timeForGameRestart >= 600)
		{
			randomTankSpawn();
			m_aiTank.init(m_level.m_aiTank.m_position);
			m_gameState = GameState::GAME_RUNNING;
			timeForGameRestart = 0;
		}
		break;
	default:
		break;
	}
	
	if (switchEnemy)
	{
		enemyUpdatedPosition();
	}
	
	if (m_aiTank.collidesWithPlayer(m_tank))
	{
		m_gameState = GameState::GAME_LOSE;
	}

	if (m_stopWatch.getElapsedTime().asMilliseconds() > 8000)
	{
		if (m_nextTarget == m_enemySprites.size())
		{
			m_nextTarget = 0;
		}
		m_nextTarget = (m_nextTarget + 1) % m_enemySprites.size();
		switchEnemy = true;
	}

	//if (m_time.isExpired())
	//{
	//	m_window.close();
	//}
	
}

////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));

	m_window.draw(m_bgSprite);
	m_tank.render(m_window);
	m_aiTank.render(m_window);

	m_pool.render(m_window);
	m_window.draw(HUD_Text);
	m_hud.render(m_window);
	for (sf::Sprite& wall : m_wallSprites)
	{
		m_window.draw(wall);
	}
	

	m_window.draw(m_enemySprites.at(m_nextTarget));
	m_window.draw(scoreText);

	m_window.display();
}
