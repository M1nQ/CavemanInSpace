#ifndef STATISTICS_H
#define STATISTICS_H

#include <UtH/UtHEngine.hpp>
#include <Caveman.h>

using namespace uth;

class Statistics : public GameObject
{
public:
	inline Statistics() { ResetScore(); }
	inline ~Statistics() {}

	void update(float dt) override final;
	void ResetScore();

private:
	float maxOxygen;
	float oxygenLeft;
	float gameTime;
	int score;
};

#endif STATISTICS_H