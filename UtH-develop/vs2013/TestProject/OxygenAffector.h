#ifndef OXYGENAFFECTOR_H
#define OXYGENAFFECTOR_H

#include "UtH\Engine\Particles\Affector.hpp"

class OxygenAffector : public uth::Affector
{
public:
	OxygenAffector();
	~OxygenAffector() override;

	void InitParticle(uth::Particle& particle, const uth::ParticleTemplate& pt) override;
	void Update(float dt) override;
	void UpdateParticle(uth::Particle& particle, const uth::ParticleTemplate& pt, float dt) override;
};
#endif
