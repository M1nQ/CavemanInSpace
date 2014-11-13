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
	~NautComponent();

	inline virtual void Init() {}
	inline virtual void Draw(RenderTarget&) {}
	inline virtual void Update(float) {}
	virtual void Hit(Vec2 playerPosition);

	float oxygen;

protected:
	virtual void Die();

	int hp;
};

#endif NAUTCOMPONENT_H