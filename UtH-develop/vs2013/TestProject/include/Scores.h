#ifndef SCORES_H
#define SCORES_H

#include <UtH/UtHEngine.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/Physics/Rigidbody.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>

using namespace uth;

class Scores : public GameObject
{
public:
	Scores();
	~Scores();

	void SetPoints();
	void SetOxygen();
	//called if oxygen runs out
	void Die();

private:
	float time;
	float oxygen;
	int points;
};

#endif