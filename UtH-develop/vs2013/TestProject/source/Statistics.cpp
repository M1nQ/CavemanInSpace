#include <Statistics.h>

Statistics::Statistics()
{
	ResetScore();

	p_oxygenBar = new GameObject();
	p_oxygenBar->AddComponent(new Sprite("Placeholders/oxygenbar_placeholder.png"));
	p_oxygenBar->transform.SetPosition(uthEngine.GetWindow().GetViewport().getLeft() + 100, uthEngine.GetWindow().GetViewport().getTop() + 20);

	p_scoreText = new GameObject();
	p_scoreText->AddComponent(new Text("FreePixel.ttf", 50, "Score"));
	p_scoreText->GetComponent<Text>("Score")->SetText(to_string(score));
	p_scoreText->transform.SetPosition(uthEngine.GetWindow().GetViewport().getRight() - 20, uthEngine.GetWindow().GetViewport().getTop() + 20);

	p_gameTimeText = new GameObject();
	p_gameTimeText->AddComponent(new Text("FreePixel.ttf", 50, "GameTime"));
	p_gameTimeText->GetComponent<Text>("GameTime")->SetText(to_string(gameTime));
	p_gameTimeText->transform.SetPosition(uthEngine.GetWindow().GetViewport().center().w, uthEngine.GetWindow().GetViewport().getTop() + 20);
}
Statistics::~Statistics()
{
	/*
	delete(p_oxygenBar);
	delete(p_scoreText);
	delete(p_gameTimeText);
	*/
}
void Statistics::Update(float dt)
{
	UpdateOxygenBar(dt);
	UpdateScore();
	UpdateGameTime(dt);
}
void Statistics::Draw(RenderTarget& target, RenderAttributes attributes)
{
	p_gameTimeText->Draw(target, attributes);
	p_scoreText->Draw(target, attributes);
	p_oxygenBar->Draw(target, attributes);
}
void Statistics::ResetScore()
{
	maxOxygen = 1;
	oxygenLeft = maxOxygen;
	gameTime = 0;
	score = 0;
}

void Statistics::UpdateOxygenBar(float dt)
{
	// Percentual decrease of oxygen / frames per second
	oxygenLeft -= maxOxygen * 0.01f / (1 / (dt * 0.001f));

	if (oxygenLeft > maxOxygen)
		oxygenLeft = maxOxygen;
	else if (oxygenLeft < 0)
		oxygenLeft = 0;

	p_oxygenBar->transform.SetPosition(uthEngine.GetWindow().GetViewport().getLeft() + 100, uthEngine.GetWindow().GetViewport().getTop() + 20);
	p_oxygenBar->transform.SetScale(oxygenLeft, 1);
	p_oxygenBar->transform.SetPosition(
										p_oxygenBar->transform.GetPosition().x -
					  p_oxygenBar->GetComponent<Sprite>("Sprite")->GetSize().x *
																	oxygenLeft ,
									   p_oxygenBar->transform.GetPosition().y);
}
void Statistics::UpdateScore()
{
	p_scoreText->transform.SetPosition(uthEngine.GetWindow().GetViewport().getRight() - 20, uthEngine.GetWindow().GetViewport().getTop() + 20);
}
void Statistics::UpdateGameTime(float dt)
{
	p_gameTimeText->transform.SetPosition(uthEngine.GetWindow().GetViewport().center().w, uthEngine.GetWindow().GetViewport().getTop() + 20);
	gameTime += dt;
}