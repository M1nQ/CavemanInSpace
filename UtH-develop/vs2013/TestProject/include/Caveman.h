#ifndef CAVEMAN_H
#define CAVEMAN_H

#include <UtH/UtHEngine.hpp>
#include <math.h>
#include <iostream>

using namespace uth;
using namespace pmath;

class Caveman : public GameObject
{
public:
	Caveman();
	~Caveman();

	void Init(PhysicsWorld *world);
	//void update(float dt);
	//Input methods
	//Hit method calls reaction method in prefab class?
	void Hit(const Vec2& hitPoint);
	// For testing input
	void ChangeDirectionMouse(pmath::Vec2 arrowDirection, bool strongpull);
	void ChangeDirectionTouch(pmath::Vec2 startPosition, pmath::Vec2 endPosition);
	void update(float dt) override;

private:
	bool rotate;
	int timeFromHit;
	float speed;
	float targetRotation;
	
	Vec2 hitDirection;
	Rigidbody* cavemanColl;
	
};

#endif