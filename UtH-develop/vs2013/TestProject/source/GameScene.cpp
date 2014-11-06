#include <GameScene.h>

GameScene::GameScene() {}
GameScene::~GameScene() {}

bool GameScene::Init()
{	
	Randomizer::SetSeed(time(NULL));
	p_world = new PhysicsWorld(0, 0);
	p_caveman = new Caveman();
	paused = false;
	AddChild<Caveman>(p_caveman);
	p_caveman->Init(p_world);
	prefabObject = PrefabObject();
	stats = Statistics();
	uthEngine.GetWindow().GetCamera().SetPosition(p_caveman->transform.GetPosition());

	// particle effect for astronaut kill (placeholder)

	p_partsys = new ParticleSystem(2000);
	auto oxypart = uthRS.LoadTexture("Placeholders/oxygenpix.png");

	ParticleTemplate pt;
	pt.SetTexture(oxypart);
	pt.SetLifetime(2.5f);
	pt.SetSpeed(30.f, 70.f);
	//pt.SetColor(1, 1, 1, 1);
	
	p_partsys->SetTemplate(pt);
	p_partsys->AddAffector(new OxygenAffector());
	p_partsys->SetEmitProperties(false);

	particleTimer = 0;

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
						p_partsys->SetEmitProperties(true, 0, 0.2f, 20, 40);
						particleTimer = 50;
					}
				}
			}
		};
	p_world->SetContactListener(&contactListener);

	p_pauseButton = new Button(uthEngine.GetWindow(), uthRS.LoadTexture("Placeholders/eimitn.png"));
	p_pauseButton->SetActive(true);
	p_pauseButton->setCallBack([this]() 
	{
		paused = true;
		p_playButton->SetActive(true);
		p_playButton->transform.SetPosition(uthEngine.GetWindow().GetCamera().GetPosition());
		overlay->SetActive(true);
		overlay->transform.SetPosition(uthEngine.GetWindow().GetCamera().GetPosition());
	});

	p_playButton = new Button(uthEngine.GetWindow(), uthRS.LoadTexture("Placeholders/eimitn.png"));
	p_playButton->SetActive(false);
	p_playButton->setCallBack([this]() 
	{
		paused = false;
		p_playButton->SetActive(false);
		overlay->SetActive(false);
	});

	overlay = new GameObject();
	overlay->AddComponent(new Sprite("Overlay.png"));
	overlay->transform.ScaleToSize(uthEngine.GetWindow().GetCamera().GetSize());
	overlay->SetActive(false);

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
	if (!paused)
	{
		Scene::Update(dt);
		p_world->Update();
		stats.Update(dt);

		if (particleTimer > 0)
		{
			particleTimer--;
		}
		else
		{
			p_partsys->SetEmitProperties(false);
			particleTimer = 0;
		}
		p_partsys->RaiseUpdateFlag();
		p_partsys->Update(dt);

		MaintainObjectList(dt);
		Input();
		UpdateCameraMovement(dt);
		p_pauseButton->Update(dt);
	}

	UpdateButtonPositions();
	p_playButton->Update(dt);
}
void GameScene::Draw(RenderTarget& target, RenderAttributes attributes)
{
	background->Draw(target, attributes); // Temporary background used for testing.
	Scene::Draw(target, attributes);
	p_partsys->Draw(target, attributes);
	for (i_ObjectList = objectList.rbegin(); i_ObjectList != objectList.rend(); ++i_ObjectList)
	{
		i_ObjectList->second->Draw(target, attributes);
	}
	p_pauseButton->Draw(target, attributes);
	stats.Draw(target, attributes);
	overlay->Draw(target, attributes);
	p_playButton->Draw(target, attributes);
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

	if (uthInput.Touch[0].Motion() == TouchMotion::RELEASE && Vec2::distance(uthInput.Touch[0].GetStartPosition(), uthInput.Touch[0].GetEndPosition()) > 10)
		p_caveman->ChangeDirection(uthInput.Common.Position());
	else if (uthInput.Touch[0].Motion() == TouchMotion::TAP)
	{ /* TODO: Call caveman's hit function. */ }

	// For testing.
	if (uthInput.Common.Event() == InputEvent::RELEASE)
		p_caveman->ChangeDirection(uthInput.Common.Position());
	if (uthInput.Common.Event() == InputEvent::TAP)
	{ /* TODO: Call caveman's hit function. */ }
}
void GameScene::UpdateButtonPositions()
{
	p_pauseButton->transform.SetPosition(
										 uthEngine.GetWindow().GetCamera().GetPosition().x +
														 uthEngine.GetWindowResolution().x *
																					  0.5f -
																					  50.f ,
										 uthEngine.GetWindow().GetCamera().GetPosition().y -
														 uthEngine.GetWindowResolution().y *
																					  0.5f + 
																					 20.f);
}