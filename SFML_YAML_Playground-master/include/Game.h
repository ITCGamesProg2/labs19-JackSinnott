#pragma once

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "LevelLoader.h"
#include "Tank.h"
#include "Thor/Time.hpp"
#include <string.h>
#include "Projectile.h"
#include "ProjectilePool.h"
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <tankAI.h>
#include <GameState.h>
#include <HUD.h>


/// <summary>
/// @author Jack Sinnott
/// @date November 2019
/// @version 1.0
/// 
/// </summary>

/// <summary>
/// @brief Main class for the SFML Playground project.
/// 
/// This example illustrates how to parse YAML data inside an SFML environment. 
/// Example usage:
///		Game game;
///		game.run();
/// </summary>

class Game
{
public:
	/// <summary>
	/// @brief Default constructor that initialises the SFML window, 
	///   and sets vertical sync enabled. 
	/// </summary>
	Game();

	/// <summary>
	/// @brief the main game loop.
	/// 
	/// A complete loop involves processing SFML events, updating and drawing all game objects.
	/// The actual elapsed time for a single game loop results (lag) is stored. If this value is 
	///  greater than the notional time for one loop (MS_PER_UPDATE), then additional updates will be 
	///  performed until the lag is less than the notional time for one loop.
	/// The target is one update and one render cycle per game loop, but slower PCs may 
	///  perform more update than render operations in one loop.
	/// </summary>
	void run();
	
protected:
	/// <summary>
	/// @brief Placeholder to perform updates to all game objects.
	/// </summary>
	/// <param name="time">update delta time</param>
	void update(double dt);

	/// <summary>
	/// @brief Draws the background and foreground game objects in the SFML window.
	/// The render window is always cleared to black before anything is drawn.
	/// </summary>
	void render();

	/// <summary>
	/// @brief Checks for events.
	/// Allows window to function and exit. 
	/// Events are passed on to the Game::processGameEvents() method.
	/// </summary>	
	void processEvents();

	/// <summary>
	/// @brief Handles all user input.
	/// </summary>
	/// <param name="event">system event</param>
	void processGameEvents(sf::Event & event);

	/// <summary>
	/// @brief Creates the wall sprites and loads them into a vector.
	/// Note that sf::Sprite is considered a light weight class, so 
	///  storing copies (instead of pointers to sf::Sprite) in std::vector is acceptable.
	/// </summary>
	void generateWalls();

	/// <summary>
	/// @brief Creates enemy tank Sprites and loads them into a vector
	/// </summary>
	void generateEnemies();

	/// <summary>
	/// ~brief sets position in window for enemies and also moves them upon respawn
	/// </summary>
	void enemyUpdatedPosition();

	/// <summary>
	/// @brief A random number between 1 and 4 to control which corner of window to start in.
	/// </summary>
	/// <returns></returns>
	void randomTankSpawn();

	/// <summary>
	/// @brief Function to have enemy flash when timealmost up
	/// </summary>
	void EnemyTimeOut();

	/// <summary>
	/// @brief Controls any sf::text for the hud in game
	/// </summary>
	void scoreOutput();


private:
	// main window
	sf::RenderWindow m_window;

	// Background image 
	sf::Sprite m_bgSprite;
	sf::Texture m_bgTexture;

	// A texture for the sprite sheet
	sf::Texture m_texture;

	sf::Texture m_targetTexture;

	// An instance representing the player controlled tank.
	Tank m_tank;

	// An instance representing the ai Tank
	TankAi m_aiTank;

	// An instance representing the tanks bullets
	Projectile m_bullets;

	// To store the game level data.
	LevelData m_level;

	// Wall sprites
	std::vector<sf::Sprite> m_wallSprites;
	sf::Sprite wallSprite;
	std::vector<sf::Sprite> m_enemySprites;
	sf::Sprite enemySprite;
	sf::Sprite enemyTurretSprite;

	// Set up timer variables
	// Hud clock
	// --------------------------------
	sf::Time m_gameOverTimer;
	sf::Time m_enemySpawnTime;
	thor::Timer m_enemySpawn;
	thor::Timer m_time;
	// --------------------------------
	// Enemy draw clock
	thor::StopWatch m_stopWatch;

	// Set up string for displaying HUD
	sf::Text HUD_Text;
	sf::Text scoreText;
	sf::Font all_Purpose_Font;
	
	// Enemy vector index
	int m_nextTarget{ 0 };

	// Player's score count
	int score = 0;

	ProjectilePool m_pool;

	// Controls sprites near end of there lifetime
	bool enemyNearlyTimedOut = false;

	// Needed a bool to stop enemyUpdatedPosition() being called every loop as it caused game to lag horribly
	bool switchEnemy = true;

	// Changes screen to display your final score
	bool gameOver = false;

	sf::Text getPlayerName;

	// The initial game state set to GAME_RUNNING
	GameState m_gameState{ GameState::GAME_RUNNING };

	// The font to be used for the HUD.
	sf::Font m_font;

	// The game HUD instance.
	HUD m_hud;
};
