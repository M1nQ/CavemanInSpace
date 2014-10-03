#include <GameScene.h>

GameScene::GameScene() {}
GameScene::~GameScene() {}

bool GameScene::Init()
{
	return true;
}
bool GameScene::DeInit()
{
	return true;
}
void GameScene::Update(float dt)
{
	Scene::Update(dt);
}
void GameScene::Draw(RenderTarget& target, RenderAttributes attributes)
{
	Scene::Draw(target, attributes);
}

// Private //

void GameScene::ReactToHit()
{
}