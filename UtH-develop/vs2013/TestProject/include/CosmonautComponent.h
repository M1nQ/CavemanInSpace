#ifndef COSMONAUTCOMPONENT_H
#define COSMONAUTCOMPONENT_H

#include <UtH\UtHEngine.hpp>
#include <NautComponent.h>

class CosmonautComponent : public NautComponent
{
public:
	inline CosmonautComponent(const string &name, float oxygen, int hp, GameObject* caveman) : NautComponent(name, oxygen, hp) { this->caveman = caveman; }
	inline ~CosmonautComponent() {}

	inline void Update(float dt) override final {}

private:
	GameObject* caveman;
};

#endif