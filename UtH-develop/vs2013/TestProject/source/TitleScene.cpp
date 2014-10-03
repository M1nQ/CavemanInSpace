#include <TitleScene.h>

TitleScene::TitleScene() {}
TitleScene::~TitleScene() {}

bool TitleScene::Init()
{
	return true;
}
bool TitleScene::DeInit()
{
	return true;
}
void TitleScene::Update(float dt)
{
	Scene::Update(dt);

	if (uthInput.Common == uth::InputEvent::CLICK)
		uthSceneM.GoToScene(2);
}
void TitleScene::Draw(RenderTarget& target, RenderAttributes attributes)
{
	Scene::Draw(target, attributes);
}