#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	emitter.setEmissionRate(30);
	emitter.setParticleLifetime(thor::Distributions::uniform(sf::seconds(5), sf::seconds(7)));
	system.addEmitter(emitter);
	
	// Emit particles in given circle
	//emitter.setParticlePosition(thor::Distributions::circle(center, radius));   
	// Emit towards direction with deviation of 15°
	//emitter.setParticleVelocity(thor::Distributions::deflect(direction, 15.f)); 
	// Rotate randomly
	//emitter.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));      
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::update(sf::Time dt)
{
}

void ParticleSystem::draw(sf::RenderWindow& t_window)
{
}
