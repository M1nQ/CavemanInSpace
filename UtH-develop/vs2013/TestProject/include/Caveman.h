#ifndef CAVEMAN_H
#define CAVEMAN_H

#include <UtH/UtHEngine.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/Physics/Rigidbody.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>

using namespace uth;

class Caveman : public GameObject
{
public:
	Caveman();
	~Caveman();

	void Init(PhysicsWorld *world);
	//Input methods
	//Hit method calls reaction method in prefab class?
	void Hit();
	void ChangeDirection(pmath::Vec2 pullPosition);


private:

	float speed;
	float oxygen;
};

#endif