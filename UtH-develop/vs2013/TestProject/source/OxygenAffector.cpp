#include "OxygenAffector.h"

OxygenAffector::OxygenAffector()
{

}
OxygenAffector::~OxygenAffector(){}

void OxygenAffector::InitParticle(uth::Particle& particle, const uth::ParticleTemplate& pt)
{
	// TODO: randomize direction
}

void OxygenAffector::Update(float dt)
{

}

void OxygenAffector::UpdateParticle(uth::Particle& particle, const uth::ParticleTemplate& pt, float dt)
{
	//TODO: set fade to happen in the last half of lifetime
}