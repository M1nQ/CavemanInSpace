#ifndef SCORES_H
#define SCORES_H

#include <UtH/UtHEngine.hpp>

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