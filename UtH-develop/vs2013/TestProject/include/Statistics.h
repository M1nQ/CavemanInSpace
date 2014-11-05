#ifndef STATISTICS_H
#define STATISTICS_H

#include <UtH/UtHEngine.hpp>
#include <Caveman.h>
#include <pmath\Vector4.hpp>

using namespace std;
using namespace uth;
using namespace pmath;

class Statistics
{
public:
	Statistics();
	~Statistics();

	void Update(float dt);
	void Draw(RenderTarget& target, RenderAttributes attributes);
	void ResetScore();

	// Add to this variable to add overall score.
	int addScore;
	// Add to this variable to increase oxygen bar.
	float addOxygen;

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
	Vec4 color;
};

#endif STATISTICS_H