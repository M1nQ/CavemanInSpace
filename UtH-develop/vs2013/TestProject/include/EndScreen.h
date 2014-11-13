#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <UtH/UtHEngine.hpp>
#include <Caveman.h>
#include <pmath\Vector4.hpp>
#include <Statistics.h>

using namespace std;
using namespace uth;
using namespace pmath;

class EndScreen
	
{
public:
	EndScreen();
	~EndScreen();

	void Update(float dt);
	void Draw(RenderTarget& target, RenderAttributes attributes);
	
	void SetFinalScore(int score);
	void SetHighScores(int first, int second, int third);

private:
	int countScore;
	int finalScore;

	GameObject* p_finalScore;
	GameObject* p_first;
	GameObject* p_second;
	GameObject* p_third;

	Vec4 color;
};

#endif

