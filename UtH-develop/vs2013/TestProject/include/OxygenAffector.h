#ifndef OXYGENAFFECTOR_H
#define OXYGENAFFECTOR_H

#include <UtH/UtHEngine.hpp>


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
