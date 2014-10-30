#include "OxygenAffector.h"

using namespace uth;

OxygenAffector::OxygenAffector()
{

}
OxygenAffector::~OxygenAffector(){}

void OxygenAffector::InitParticle(uth::Particle& particle, const uth::ParticleTemplate& pt)
{
	// randomize direction
	particle.direction = RandomDirection();
	particle.direction.normalize();
	timeLeft = pt.lifetime;
	particle.color.a = 1;
	speed = Randomizer::GetFloat(pt.minSpeed, pt.maxSpeed);
}

void OxygenAffector::Update(float dt)
{

}

void OxygenAffector::UpdateParticle(uth::Particle& particle, const uth::ParticleTemplate& pt, float dt)
{
	//TODO: set fade to happen in the last half of lifetime
	timeLeft -= dt;
	if (timeLeft < pt.lifetime / 2 && particle.color.a > 0)
	{
		particle.color.a -= dt / (pt.lifetime/2);	
	}	
	
	particle.Move(particle.direction * dt * speed);
	
}

pmath::Vec2 OxygenAffector::RandomDirection()
{
	short randomNumber = Randomizer::GetInt(0, 4);
	//randomNumber = randomNumber % 4;
	switch (randomNumber)
	{
	case 0: return pmath::Vec2(Randomizer::GetFloat(-600, 600), Randomizer::GetFloat(500, 1000));
	case 1: return pmath::Vec2(Randomizer::GetFloat(-600, 600), Randomizer::GetFloat(-600, -1000));
	case 2: return pmath::Vec2(Randomizer::GetFloat(400, 1000), Randomizer::GetFloat(-600, 600));
	case 3: return pmath::Vec2(Randomizer::GetFloat(-400, -800), Randomizer::GetFloat(-600, 800));
	default: return pmath::Vec2(Randomizer::GetFloat(-600, 600), Randomizer::GetFloat(500, 1000));
	}
}