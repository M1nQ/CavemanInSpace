#include <Statistics.h>

Statistics::Statistics()
{
	ResetScore();

	p_oxygenBar = new GameObject();
	p_oxygenBar->AddComponent(new Sprite("Placeholders/oxygenbar_placeholder.png"));

	p_scoreText = new GameObject();
	p_scoreText->AddComponent(new Text("FreePixel.ttf", 50.f, "Score"));
	p_scoreText->GetComponent<Text>("Score")->AddText(to_string(score), color);
	p_scoreText->transform.SetPosition(0,0);
}
Statistics::~Statistics()
{
}
void Statistics::Update(float dt)
{
	UpdateOxygenBar(dt);
	UpdateScore();
	gameTime += dt;
}
void Statistics::Draw(RenderTarget& target, RenderAttributes attributes)
{
	p_oxygenBar->Draw(target, attributes);
	p_scoreText->Draw(uthEngine.GetWindow());
}
void Statistics::ResetScore()
{
	// Resets all scores.

	maxOxygen = 1;
	oxygenLeft = maxOxygen;
	gameTime = 0;
	score = 0;
	addScore = 0;
	addOxygen = 0;
	color = Vec4(1, 1, 1, 1);
	
}

void Statistics::UpdateOxygenBar(float dt)
{
	// Updates the amount of oxygen and the position and scale of the oxygen bar.

	if (addOxygen > 0 && addOxygen > 0.01f)
	{
		oxygenLeft += addOxygen * 0.05f;
		addOxygen -= addOxygen * 0.05f;
	}
	else if (addOxygen > 0)
	{
		oxygenLeft += addOxygen;
		addOxygen = 0;
	}
	else
	{
		// Percentual decrease of oxygen / frames per second
		oxygenLeft -= maxOxygen * 0.05f / ( 1 / dt);
	}

	if (oxygenLeft > maxOxygen)
		oxygenLeft = maxOxygen;
	else if (oxygenLeft <= 0)
	{
		oxygenLeft = 0;
		
	}
	p_oxygenBar->transform.SetScale(oxygenLeft, 1);
	p_oxygenBar->transform.SetPosition(
									   (uthEngine.GetWindow().GetCamera().GetPosition().x -
													   (uthEngine.GetWindowResolution().x *
																					0.5f) +
																				   170.f) -
								(p_oxygenBar->GetComponent<Sprite>("Sprite")->GetSize().x -
								(p_oxygenBar->GetComponent<Sprite>("Sprite")->GetSize().x *
																			 oxygenLeft)) *
																					 0.5f ,
										uthEngine.GetWindow().GetCamera().GetPosition().y -
													   (uthEngine.GetWindowResolution().y *
																					0.5f) +
																					50.f);
}
void Statistics::UpdateScore()
{
	// Updates the score and it's position.

	if (addScore >= 5)
	{
		addScore -= 5;
		score += 5;
	}
	else if (addScore > 0)
	{
		--addScore;
		++score;
	}

	p_scoreText->GetComponent<Text>("Score")->SetText(to_string(score), color);
	p_scoreText->transform.SetPosition(
									   uthEngine.GetWindow().GetCamera().GetPosition().x +
													   uthEngine.GetWindowResolution().x *
																					0.5f -
													  p_scoreText->transform.GetSize().x *
																					0.5f -
																				   300.f ,
												 p_oxygenBar->transform.GetPosition().y);
}

int Statistics::GetFinalScore()
{
	return score + (int)(gameTime / 10) * 100;
}

bool Statistics::IsDead()
{
	if (oxygenLeft <= 0)
		return true;
	return false;
}