#include "EndScreen.h"


EndScreen::EndScreen()
{
	color = Vec4(1, 1, 1, 1);
	p_finalScore = new GameObject();
	p_finalScore->AddComponent(new Text("FreePixel.ttf", 50.f, "Score"));
	p_finalScore->GetComponent<Text>("Score")->AddText(to_string(finalScore), color);
	p_finalScore->transform.SetPosition((uthEngine.GetWindow().GetCamera().GetPosition()) + Vec2(-250, 50));

	// High scores as separate objects. TODO: change to array or (if possible) one object?
	p_first = new GameObject();
	p_first->AddComponent(new Text("FreePixel.ttf", 50.f, "Score"));
	p_first->transform.SetPosition((uthEngine.GetWindow().GetCamera().GetPosition()) + Vec2(-250, 150));
	p_second = new GameObject();
	p_second->AddComponent(new Text("FreePixel.ttf", 50.f, "Score"));
	p_second->transform.SetPosition((uthEngine.GetWindow().GetCamera().GetPosition()) + Vec2(-250, 200));
	p_third = new GameObject();
	p_third->AddComponent(new Text("FreePixel.ttf", 50.f, "Score"));
	p_third->transform.SetPosition((uthEngine.GetWindow().GetCamera().GetPosition()) + Vec2(-250, 250));
}

EndScreen::~EndScreen()
{
}

void EndScreen::Update(float dt)
{
	if (countScore >= 50)
	{
		countScore -= 50;
		finalScore += 50;
	}
	else if (countScore > 0)
	{
		--countScore;
		++finalScore;
	}

	p_finalScore->GetComponent<Text>("Score")->SetText(to_string(finalScore), color);
}

void EndScreen::Draw(RenderTarget& target, RenderAttributes attributes)
{
	p_finalScore->Draw(target, attributes);
	p_first->Draw(target, attributes);
	p_second->Draw(target, attributes);
	p_third->Draw(target, attributes);
}

void EndScreen::SetFinalScore(int score)
{
	countScore = score;
	finalScore = 0;
}

void EndScreen::SetHighScores(int first, int second, int third, int current)
{
	p_first->GetComponent<Text>("Score")->AddText(to_string(first), Highlight(first, current));
	p_second->GetComponent<Text>("Score")->AddText(to_string(second), Highlight(second, current));
	p_third->GetComponent<Text>("Score")->AddText(to_string(third), Highlight(third, current));
}

// Ugly code for highlighting current score in leaderboard!
// TODO: make prettier.

Vec4 EndScreen::Highlight(int score, int newscore)
{
	Vec4 col = Vec4(1, 1, 1, 1);
	if (score == newscore)
	{
		col = Vec4(1, 0, 1, 1);
	}
	return col;
}