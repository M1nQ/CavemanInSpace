#include <Statistics.h>

void Statistics::update(float dt)
{
	if (oxygenLeft > maxOxygen)
		oxygenLeft = maxOxygen;

	oxygenLeft -= maxOxygen * 0.01f / 60;
	gameTime += dt;
}

void Statistics::ResetScore()
{
	maxOxygen = 1;
	oxygenLeft = maxOxygen;
	gameTime = 0;
	score = 0;
}