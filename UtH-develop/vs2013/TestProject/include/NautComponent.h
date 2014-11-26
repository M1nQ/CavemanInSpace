#ifndef NAUTCOMPONENT_H
#define NAUTCOMPONENT_H

#include <UtH\UtHEngine.hpp>

using namespace uth;
using namespace std;
using namespace pmath;

class NautComponent : public Component
{
public:
	inline NautComponent(const string& name = "NautComponent", float oxygen = 0.3f, int hp = 1) : Component(name) { this->oxygen = oxygen; this->hp = hp; }
	inline virtual ~NautComponent() {}

	virtual void Update(float dt);
	inline bool isDead() { if (hp <= 0) return true; return false; }
	inline bool hasMoved() { if (Vec2::distance(lastIndicatorPosition, parent->transform.GetPosition())) return true; return false; }

	// Subtracts from hp and sets direction away from the given position.
	virtual void Hit(Vec2 position);
	virtual GameObject* addTrail();

	float oxygen;

protected:
	int hp;
	Vec2 lastIndicatorPosition;
};

#endif NAUTCOMPONENT_H