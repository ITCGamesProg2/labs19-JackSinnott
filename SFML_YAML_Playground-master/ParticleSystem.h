#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Math.hpp>
#include <Thor/Particles.hpp>

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void update(sf::Time t_dt);
	void draw(sf::RenderWindow& t_window);

private:
	sf::Texture particleTexture;
	thor::ParticleSystem system;
	thor::UniversalEmitter emitter;

};

