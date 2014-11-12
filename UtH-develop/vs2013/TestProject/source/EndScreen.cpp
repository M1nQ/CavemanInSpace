#include "EndScreen.h"


EndScreen::EndScreen()
{
	p_finalScore = new GameObject();
	p_finalScore->AddComponent(new Text("FreePixel.ttf", 50.f, "Score"));
	p_finalScore->GetComponent<Text>("Score")->AddText(to_string(finalScore), color);
}

EndScreen::~EndScreen()
{
}

void EndScreen::Update(float dt)
{
	if (countScore >= 5)
	{
		countScore -= 5;
		finalScore += 5;
	}
	else if (countScore > 0)
	{
		--countScore;
		++finalScore;
	}

	p_finalScore->GetComponent<Text>("Score")->SetText(to_string(finalScore), color);
}

void EndScreen::SetFinalScore(Statistics stats)
{
	countScore = stats.GetFinalScore();
	finalScore = 0;
}