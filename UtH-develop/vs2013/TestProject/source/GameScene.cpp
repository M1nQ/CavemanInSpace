#include <GameScene.h>

GameScene::GameScene() {}
GameScene::~GameScene() {}

bool GameScene::Init()
{
	World = new PhysicsWorld(0, 0);

	caveman = new Caveman();
	caveman->Init(World);
	lastState = uth::InputEvent::NONE;
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
	
	//caveman->ChangeDirection(pmath::Vec2(-100, -100));
	if (uthInput.Common == uth::InputEvent::CLICK)
	{
		if (lastState == uth::InputEvent::DRAG)
		{
			caveman->ChangeDirection(uthInput.Common.Position());
		}
	}
	lastState = uthInput.Common.Event();
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