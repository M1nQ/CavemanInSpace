#ifndef NAUTCOMPONENT_H
#define NAUTCOMPONENT_H

#include <UtH\UtHEngine.hpp>

using namespace uth;
using namespace std;
using namespace pmath;

class NautComponent : public Component
{
public:
	inline NautComponent(const string& name) : Component(name) {}
	inline virtual ~NautComponent() {}

	inline virtual void Init() {}
	inline virtual void Draw(RenderTarget&) {}
	inline bool isDead() { if (hp <= 0) return true; return false; }
	virtual void Update(float dt);

	// Subtracts from hp and sets direction away from the given position.
	virtual void Hit(Vec2 position);

	float oxygen;

protected:
	int hp;
};

#endif NAUTCOMPONENT_H