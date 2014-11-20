#ifndef CLUB_H
#define CLUB_H

#include <UtH/UtHEngine.hpp>

using namespace uth;
using namespace pmath;

class Club : public GameObject
{
public:
	Club(Vec2 clubSize);
	~Club();

	void Init(PhysicsWorld *world);
	void update(float dt, Vec2 cavemanPos);
	void Hit(Vec2 cavemanPosition, Vec2 tapPosition);
	void HasHit();

private:
	Vec2 size;
	Rigidbody* clubColl;
	
	float timeFromHit;
	float reach;
	Vec2 hitDirection;
};

#endif