#include <LoadScene.h>

bool LoadScene::Init()
{
	return true;
}
bool LoadScene::DeInit()
{
	return true;
}

void LoadScene::Update(float dt)
{
	if (LoadEverything())
		uthSceneM.GoToScene(1);
}
void LoadScene::Draw(RenderTarget& target, RenderAttributes attributes)
{

}

// Load all assets
bool LoadScene::LoadEverything()
{
	
	return true;
}