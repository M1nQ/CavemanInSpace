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
	//background = new GameObject("Background");
	//background->AddComponent(new Sprite("Placeholders/Big_Background.png"));

	// Used for PC input.
	lastStatePC = InputEvent::NONE;

	// Temporary objects
	for (int i = 0; i < 10; ++i)
		objects.push_back(prefabObject.CreateAstronaut(p_world, GetRandomSpawnPosition()));

	for (int i = 0; i < 10; ++i)
		objects.push_back(prefabObject.CreateAsteroid(p_world, GetRandomSpawnPosition()));

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

	// Maintaining the list of objects.
	/*
	if (objectList.size() > 0)
	{
		for (i_ObjectList = objectList.rbegin(); i_ObjectList != objectList.rend(); i_ObjectList--)
		{
			if (DeleteObjects(i_ObjectList->second))
				objectList.erase(--(i_ObjectList.base()));

			i_ObjectList->second->Update(dt);
		}
	}
	AddObjects();
	*/

	// Test objects update
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Update(dt);

	// Android Input
	if (uthInput.Touch.Motion() == TouchMotion::RELEASE)
			p_caveman->ChangeDirection(uthInput.Common.Position());

	// PC Input for testing.
	if (uthInput.Common.Event() != InputEvent::DRAG && lastStatePC == InputEvent::DRAG)
		p_caveman->ChangeDirection(uthInput.Common.Position());

	lastStatePC = uthInput.Common.Event();
	uthEngine.GetWindow().GetCamera().SetPosition(p_caveman->transform.GetPosition());
}
void GameScene::Draw(RenderTarget& target, RenderAttributes attributes)
{
	Scene::Draw(target, attributes);
	//background->Draw(target, attributes); // Temporary background used for testing.
	p_caveman->Draw(target, attributes);

	/*
	for (i_ObjectList = objectList.rbegin(); i_ObjectList != objectList.rend(); i_ObjectList--)
	{
		i_ObjectList->second->Draw(target, attributes);
	}
	*/

	// Test objects update
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Draw(target, attributes);
}

// Private //

void GameScene::ReactToHit()
{
}
void GameScene::AddObjects()
{
	// Maintains the objectlist so, that it always holds a certain amount of specified objects.

	/*
	while (objectList.count("Astronaut") < 10)
	{
		objectList.insert(make_pair("Astronaut", prefabObject.CreateAstronaut(p_world, GetRandomSpawnPosition())));
	}
	while (objectList.count("Asteroid") < 15)
	{
		objectList.insert(make_pair("Asteroid", prefabObject.CreateAsteroid(p_world, GetRandomSpawnPosition())));
	}
	*/
}
bool GameScene::DeleteObjects(GameObject* p_object)
{
	if (Vec2::distance(p_object->transform.GetPosition(), p_caveman->transform.GetPosition()) >= 2000)
	{
		delete(p_object);
		return true;
	}
	return false;
}
void GameScene::UpdateBackground()
{
	// TODO: Make a "scrolling" background.
}
Vec2 GameScene::GetRandomSpawnPosition()
{
	short randomNumber = Randomizer::GetInt(0, 4);

	switch (randomNumber)
	{
	case 0: return Vec2(Randomizer::GetFloat(1000, 1500), Randomizer::GetFloat(600, 1100)) + p_caveman->transform.GetPosition();
	case 1: return Vec2(Randomizer::GetFloat(1000, -1500), Randomizer::GetFloat(600, -1100)) + p_caveman->transform.GetPosition();
	case 2: return Vec2(Randomizer::GetFloat(-1000, 1500), Randomizer::GetFloat(-600, 1100)) + p_caveman->transform.GetPosition();
	case 3: return Vec2(Randomizer::GetFloat(-1000, -1500), Randomizer::GetFloat(-600, -1100)) + p_caveman->transform.GetPosition();
	default: return Vec2(Randomizer::GetFloat(1000, 1500), Randomizer::GetFloat(600, 1100)) + p_caveman->transform.GetPosition();
	}
}