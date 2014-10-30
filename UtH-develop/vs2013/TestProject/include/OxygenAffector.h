#ifndef OXYGENAFFECTOR_H
#define OXYGENAFFECTOR_H

#include "UtH/Engine/Particles/Affector.hpp"
#include "UtH/Core/Randomizer.hpp"
#include "UtH/Engine/Particles/Particle.hpp"
#include "UtH/Engine/Particles/ParticleTemplate.hpp"


class OxygenAffector : public uth::Affector
{
public:
	OxygenAffector();
	~OxygenAffector() override;

	void InitParticle(uth::Particle& particle, const uth::ParticleTemplate& pt) override;
	void Update(float dt) override;
	void UpdateParticle(uth::Particle& particle, const uth::ParticleTemplate& pt, float dt) override;

private:
	pmath::Vec2 RandomDirection();
	float timeLeft;
	float speed;
};
#endif
