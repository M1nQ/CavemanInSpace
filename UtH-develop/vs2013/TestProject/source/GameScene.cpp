#include <GameScene.h>

GameScene::GameScene() {}
GameScene::~GameScene() {}

bool GameScene::Init()
{
	p_world = new PhysicsWorld(0, 0);
	p_caveman = new Caveman();
	p_caveman->Init(p_world);
	prefabObject = PrefabObject();

	// Used for PC input.
	lastStatePC = InputEvent::NONE;

	// Test
	objectList.push_back(prefabObject.CreateAstronaut(p_world, Vec2(0, 300)));
	objectList.push_back(prefabObject.CreateAstronaut(p_world, Vec2(-150, 700)));
	objectList.push_back(prefabObject.CreateAstronaut(p_world, Vec2(-500, -200)));
	objectList.push_back(prefabObject.CreateAstronaut(p_world, Vec2(140, -500)));
	objectList.push_back(prefabObject.CreateAstronaut(p_world, Vec2(-340, 250)));

	objectList.push_back(prefabObject.CreateAsteroid(p_world, Vec2(-220, -300)));
	objectList.push_back(prefabObject.CreateAsteroid(p_world, Vec2(210, 500)));
	objectList.push_back(prefabObject.CreateAsteroid(p_world, Vec2(750, -270)));
	objectList.push_back(prefabObject.CreateAsteroid(p_world, Vec2(400, -170)));

	return true;
}
bool GameScene::DeInit()
{
	return true;
}
void GameScene::Update(float dt)
{
	Scene::Update(dt);
	p_world->Update();
	p_caveman->Update(dt);
	uthEngine.GetWindow().GetCamera().Update(dt);

	for each (GameObject* object in objectList)
	{
		object->Update(dt);
	}

	//uthEngine.GetWindow().GetCamera().SetPosition(p_caveman->transform.GetPosition());

	// Android Input
	/*
	if (uthInput.Touch.Motion() == TouchMotion::RELEASE)
			p_caveman->ChangeDirection(uthInput.Common.Position());
	*/

	// PC Input for testing.
	if (uthInput.Common.Event() != InputEvent::DRAG && lastStatePC == InputEvent::DRAG)
		p_caveman->ChangeDirection(uthInput.Common.Position());

	lastStatePC = uthInput.Common.Event();
}
void GameScene::Draw(RenderTarget& target, RenderAttributes attributes)
{
	Scene::Draw(target, attributes);
	p_caveman->Draw(target, attributes);

	for each (GameObject* object in objectList)
	{
		object->Draw(target, attributes);
	}
}

// Private //

void GameScene::ReactToHit()
{
}