#ifndef STATISTICS_H
#define STATISTICS_H

#include <UtH/UtHEngine.hpp>
#include <Caveman.h>

using namespace std;
using namespace uth;

class Statistics
{
public:
	Statistics();
	~Statistics();

	void Update(float dt);
	void Draw(RenderTarget& target, RenderAttributes attributes);
	void ResetScore();

private:
	void UpdateOxygenBar(float dt);
	void UpdateScore();
	void UpdateGameTime(float dt);

	float maxOxygen;
	float oxygenLeft;
	float gameTime;
	int score;
	GameObject* p_oxygenBar;
	GameObject* p_scoreText;
	GameObject* p_gameTimeText;
};

#endif STATISTICS_H