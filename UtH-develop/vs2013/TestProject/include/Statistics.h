#ifndef STATISTICS_H
#define STATISTICS_H

#include <UtH/UtHEngine.hpp>
#include <Caveman.h>
#include <pmath\Vector4.hpp>

using namespace std;
using namespace uth;
using namespace pmath;

namespace uth
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
	template < typename T > int stoi(const T& j)
	{
		std::istringstream ss(j);
		int i;
		ss >> i;
		return i;
	}
}
class Statistics
{
public:
	Statistics();
	~Statistics();

	void Update(float dt);
	void Draw(RenderTarget& target, RenderAttributes attributes);
	void ResetScore();
	inline float GetGameTime() { return gameTime; }

	int GetFinalScore();

	// Add to this variable to add overall score.
	int addScore;
	// Add to this variable to increase oxygen bar.
	float addOxygen;
	bool IsDead();

private:
	void UpdateOxygenBar(float dt);
	void UpdateScore();
		
	float maxOxygen;
	float oxygenLeft;
	float gameTime;
	int score;
	GameObject* p_oxygenBar;
	GameObject* p_scoreText;
	Vec4 color;
};

#endif