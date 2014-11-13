#ifndef CLUB_H
#define CLUB_H

#include <UtH/UtHEngine.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/Physics/Rigidbody.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>

using namespace uth;
using namespace pmath;

class Club : public GameObject
{
public:
	Club(Vec2 clubSize);
	~Club();

	void Init(PhysicsWorld *world);
	void update(float dt);
	void Hit(Vec2 cavemanPosition, Vec2 tapPosition);

private:
	Vec2 size;
	Rigidbody* clubColl;
	
	float timeFromHit;
	float reach;
	Vec2 hitDirection;
};

#endif