#include <GameScene.h>

GameScene::GameScene() {}
GameScene::~GameScene() {}

bool GameScene::Init()
{
	World = new PhysicsWorld(0, 0);

	caveman = new Caveman();
	caveman->Init(World);
	lastState = uth::TouchMotion::NONE;
	return true;
}
bool GameScene::DeInit()
{
	return true;
}
void GameScene::Update(float dt)
{
	
	Scene::Update(dt);
	World->Update();
	caveman->Update(dt);
	
	if (uthInput.Touch.Motion() == TouchMotion::NONE && lastState == TouchMotion::DRAG)
			caveman->ChangeDirection(uthInput.Common.Position());

	lastState = uthInput.Touch.Motion();
}
void GameScene::Draw(RenderTarget& target, RenderAttributes attributes)
{
	Scene::Draw(target, attributes);
	caveman->Draw(target, attributes);
}

// Private //

void GameScene::ReactToHit()
{
}