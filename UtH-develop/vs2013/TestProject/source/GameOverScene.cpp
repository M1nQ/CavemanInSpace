#include <GameOverScene.h>

GameOverScene::GameOverScene() {}
GameOverScene::~GameOverScene() {}

bool GameOverScene::Init()
{
	return true;
}
bool GameOverScene::DeInit()
{
	return true;
}
void GameOverScene::Update(float dt)
{
	Scene::Update(dt);
}
void GameOverScene::Draw(RenderTarget& target, RenderAttributes attributes)
{
	Scene::Draw(target, attributes);
}

// Private //

void GameOverScene::CountFinalScore()
{
}
void GameOverScene::SaveHighScores()
{
}