#include <MenuScene.h>

MenuScene::MenuScene() {}
MenuScene::~MenuScene() {}

bool MenuScene::Init()
{
	return true;
}
bool MenuScene::DeInit()
{
	return true;
}
void MenuScene::Update(float dt)
{
	Scene::Update(dt);
}
void MenuScene::Draw(RenderTarget& target, RenderAttributes attributes)
{
	Scene::Draw(target, attributes);
}

// Private //

void ReadHighScores()
{
}