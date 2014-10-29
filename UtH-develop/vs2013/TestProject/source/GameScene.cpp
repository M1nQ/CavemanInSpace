#include <GameScene.h>

GameScene::GameScene() {}
GameScene::~GameScene() {}

bool GameScene::Init()
{	
	Randomizer::SetSeed(time(NULL));
	p_world = new PhysicsWorld(0, 0);
	p_caveman = new Caveman();
	AddChild<Caveman>(p_caveman);
	p_caveman->Init(p_world);
	prefabObject = PrefabObject();
	uthEngine.GetWindow().GetCamera().SetPosition(p_caveman->transform.GetPosition());

	// particle effect for astronaut kill (placeholder)

	p_partsys = new ParticleSystem(100.0f);
	auto oxypart = uthRS.LoadTexture("oxygenpix");

	ParticleTemplate pt;
	pt.SetTexture(oxypart);
	pt.SetLifetime(4.f);
	pt.SetSpeed(20.f);

	p_partsys->SetTemplate(pt);
	p_partsys->AddAffector(new OxygenAffector());
	

	// contact reaction logic
	contactListener = PhysicsContactListener();
	contactListener.onBeginContact = [&](b2Contact* contact, GameObject* a, GameObject* b)
		{
			if (a->HasTag("Caveman"))
			{
				for (i_ObjectList = objectList.rbegin(); i_ObjectList != objectList.rend(); ++i_ObjectList)
				{
					if (i_ObjectList->second == b && i_ObjectList->first == "Astronaut")
					{
						//kill astronaut
						p_caveman->Hit();
						//particles!
						p_partsys->transform.SetPosition(b->GetComponent<Rigidbody>()->GetPosition());
					}
				}
			}
		};
	p_world->SetContactListener(&contactListener);

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
	MaintainObjectList(dt);
	UpdateCameraMovement(dt);
	Input();
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
void GameScene::MaintainObjectList(float dt)
{
	// Updates, deletes and instantiates objects.

	AddObjects();

	if (objectList.size() > 0)
	{
		for (i_ObjectList = objectList.rbegin(); i_ObjectList != objectList.rend(); ++i_ObjectList)
		{
			i_ObjectList->second->Update(dt);

			if (DeleteObjects(i_ObjectList->second))
				objectList.erase(--(i_ObjectList.base()));
		}
	}
}
void GameScene::AddObjects()
{
	// Maintains the objectlist so, that it always holds a certain amount of specified objects.
	
	while (objectList.count("Astronaut") < 20)
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
void GameScene::UpdateBackground()
{
	// TODO: Make a "scrolling" background.
}
void GameScene::UpdateCameraMovement(float dt)
{
	// Makes the camera smoothly follow the player.
	
	Vec2 movement = p_caveman->transform.GetPosition() - uthEngine.GetWindow().GetCamera().GetPosition();

	if (movement.length() != 0)
		movement.normalize();

	if (Vec2::distance(p_caveman->transform.GetPosition(), uthEngine.GetWindow().GetCamera().GetPosition()) >= 0.5f)
		uthEngine.GetWindow().GetCamera().Scroll(movement * Vec2::distance(p_caveman->transform.GetPosition(), uthEngine.GetWindow().GetCamera().GetPosition()) / 50.f);
	else
		uthEngine.GetWindow().GetCamera().SetPosition(p_caveman->transform.GetPosition());

	uthEngine.GetWindow().GetCamera().Update(dt);
}
void GameScene::Input()
{
	// Handles input.

	if (uthInput.Common.Event() == InputEvent::RELEASE)
		p_caveman->ChangeDirection(uthInput.Common.Position());
}