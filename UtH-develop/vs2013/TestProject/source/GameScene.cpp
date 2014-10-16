#include <GameScene.h>

GameScene::GameScene() {}
GameScene::~GameScene() {}

bool GameScene::Init()
{	
	Randomizer::SetSeed(3425934636);
	p_world = new PhysicsWorld(0, 0);
	p_caveman = new Caveman();
	AddChild<Caveman>(p_caveman);
	p_caveman->Init(p_world);
	prefabObject = PrefabObject();
	uthEngine.GetWindow().GetCamera().SetPosition(p_caveman->transform.GetPosition());

	// Temporary background used for testing.
	background = new GameObject("Background");
	background->AddComponent(new Sprite("Placeholders/Big_Background.png"));

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
	uthEngine.GetWindow().GetCamera().Update(dt);
	uthEngine.GetWindow().GetCamera().SetPosition(p_caveman->transform.GetPosition());

	// Maintaining the list of objects.
	if (objectList.size() > 0)
	{
		for (i_ObjectList = objectList.rbegin(); i_ObjectList != objectList.rend(); ++i_ObjectList)
		{
			i_ObjectList->second->Update(dt);

			if (DeleteObjects(i_ObjectList->second))
				objectList.erase(--(i_ObjectList.base()));
		}
	}
	AddObjects();

	// Input
	if (uthInput.Common.Event() == InputEvent::RELEASE)
		p_caveman->ChangeDirection(uthInput.Common.Position());
}
void GameScene::Draw(RenderTarget& target, RenderAttributes attributes)
{
	background->Draw(target, attributes); // Temporary background used for testing.
	Scene::Draw(target, attributes);

	for (i_ObjectList = objectList.rbegin(); i_ObjectList != objectList.rend(); ++i_ObjectList)
	{
		i_ObjectList->second->Draw(target, attributes);
	}
}

// Private //

void GameScene::ReactToHit()
{
}
void GameScene::AddObjects()
{
	// Maintains the objectlist so, that it always holds a certain amount of specified objects.

	while (objectList.count("Astronaut") < 25)
	{
		objectList.insert(make_pair("Astronaut", prefabObject.CreateAstronaut(p_world, GetRandomSpawnPosition())));
	}
	while (objectList.count("Asteroid") < 20)
	{
		objectList.insert(make_pair("Asteroid", prefabObject.CreateAsteroid(p_world, GetRandomSpawnPosition())));
	}
}
bool GameScene::DeleteObjects(GameObject* p_object)
{
	// Deletes objects that are too far away from the player. (Return's true if the object was deleted.)

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
	// Returns a random position outside the field of view, but not too far away.

	short randomNumber = Randomizer::GetInt(0, 4);

	switch (randomNumber)
	{
	case 0: return Vec2(Randomizer::GetFloat(-1000, 1000), Randomizer::GetFloat(600, 1600)) + p_caveman->transform.GetPosition();
	case 1: return Vec2(Randomizer::GetFloat(-1000, 1000), Randomizer::GetFloat(-600, -1600)) + p_caveman->transform.GetPosition();
	case 2: return Vec2(Randomizer::GetFloat(1000, 2000), Randomizer::GetFloat(-600, 600)) + p_caveman->transform.GetPosition();
	case 3: return Vec2(Randomizer::GetFloat(-1000, -2000), Randomizer::GetFloat(-600, 600)) + p_caveman->transform.GetPosition();
	default: return Vec2(Randomizer::GetFloat(-1000, 1000), Randomizer::GetFloat(600, 1600)) + p_caveman->transform.GetPosition();
	}
}