#include <GameScene.h>

GameScene::GameScene() {}
GameScene::~GameScene() {}

bool GameScene::Init()
{	p_world = new PhysicsWorld(0, 0);
	p_caveman = new Caveman();
	p_caveman->Init(p_world);
	prefabObject = PrefabObject();
	uthEngine.GetWindow().GetCamera().SetPosition(p_caveman->transform.GetPosition());

	// Temporary background used for testing.
	background = new GameObject("Background");
	background->AddComponent(new Sprite("Placeholders/Big_Background.png"));

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

	objectList[0]->Update(dt);
	objectList[1]->Update(dt);
	objectList[2]->Update(dt);
	objectList[3]->Update(dt);
	objectList[4]->Update(dt);
	objectList[5]->Update(dt);
	objectList[6]->Update(dt);
	objectList[7]->Update(dt);
	objectList[8]->Update(dt);

	// Android Input
	///*
	if (uthInput.Touch.Motion() == TouchMotion::RELEASE)
			p_caveman->ChangeDirection(uthInput.Common.Position());
	//*/

	// PC Input for testing.
	uthEngine.GetWindow().GetCamera().SetPosition(p_caveman->transform.GetPosition());

	if (uthInput.Common.Event() != InputEvent::DRAG && lastStatePC == InputEvent::DRAG)
		p_caveman->ChangeDirection(uthInput.Common.Position());

	lastStatePC = uthInput.Common.Event();
}
void GameScene::Draw(RenderTarget& target, RenderAttributes attributes)
{
	Scene::Draw(target, attributes);
	background->Draw(target, attributes); // Temporary background used for testing.
	p_caveman->Draw(target, attributes);

	objectList[0]->Draw(target, attributes);
	objectList[1]->Draw(target, attributes);
	objectList[2]->Draw(target, attributes);
	objectList[3]->Draw(target, attributes);
	objectList[4]->Draw(target, attributes);
	objectList[5]->Draw(target, attributes);
	objectList[6]->Draw(target, attributes);
	objectList[7]->Draw(target, attributes);
	objectList[8]->Draw(target, attributes);
}

// Private //

void GameScene::ReactToHit()
{
}