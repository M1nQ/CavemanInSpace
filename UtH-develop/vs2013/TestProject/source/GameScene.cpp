#include <GameScene.h>

GameScene::GameScene() {}
GameScene::~GameScene() {}

bool GameScene::Init()
{	
	Randomizer::SetSeed(time(NULL));
	p_world = new PhysicsWorld(0, 0);
	p_caveman = new Caveman();
	paused = false;
	screenDiameter = sqrt(pow(uthEngine.GetWindowResolution().x, 2) + pow(uthEngine.GetWindowResolution().y, 2));
	AddChild<Caveman>(p_caveman);
	p_caveman->Init(p_world);
	p_club = new Club(p_caveman->transform.GetSize());
	p_club->Init(p_world);
	AddChild<Club>(p_club);
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
	contactListener.onBeginContact = [this](b2Contact* contact, GameObject* a, GameObject* b)
		{
			if (b->HasTag("Club"))
			{
				ReactToHit(a);
			}
			else if (a->HasTag("Club"))
			{
				ReactToHit(b);
			}
			else {}
		};
	p_world->SetContactListener(&contactListener);
	
	// Buttons
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

	p_playButton = new Button(uthEngine.GetWindow(), uthRS.LoadTexture("Placeholders/Play.png"));
	p_playButton->SetActive(false);
	p_playButton->setCallBack([this]() 
	{
		paused = false;
		p_playButton->SetActive(false);
		overlay->SetActive(false);
	});

	// Game paused overlay
	overlay = new GameObject();
	overlay->AddComponent(new Sprite("Overlay.png"));
	overlay->transform.ScaleToSize(uthEngine.GetWindow().GetCamera().GetSize());
	overlay->SetActive(false);

	// Background initialization
	for (int i = 0; i < 4; ++i)
	{
		p_background[i] = new GameObject("Background");
		p_background[i]->AddComponent(new Sprite("Placeholders/Big_Background.png"));
		p_background[i]->transform.ScaleToSize(uthEngine.GetWindow().GetCamera().GetSize());
	}
	p_background[1]->transform.SetPosition(Vec2 (uthEngine.GetWindowResolution().x , 0));
	p_background[2]->transform.SetPosition(Vec2(0, uthEngine.GetWindowResolution().y));
	p_background[3]->transform.SetPosition(uthEngine.GetWindowResolution());

	// Game over overlay
	p_gameOverPlaque = new GameObject();
	p_gameOverPlaque->AddComponent(new Sprite("Placeholders/gameOver.png"));
	// p_gameOverPlaque->transform.ScaleToSize(uthEngine.GetWindow().GetCamera().GetSize());
	p_gameOverPlaque->SetActive(false);

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
		
		UpdateBackground();
		p_world->Update(dt);
		p_club->update(dt);
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
		UpdateCameraMovement(dt);
		p_pauseButton->Update(dt);
		Input();
		
	}

	UpdateButtonPositions();
	p_playButton->Update(dt);
	/*if (stats.IsDead())
			GameOverLay();*/
}
void GameScene::Draw(RenderTarget& target, RenderAttributes attributes)
{
	for (int i = 0; i < 4; ++i)
	{
		p_background[i]->Draw(target, attributes);
	}

	Scene::Draw(target, attributes);
	p_club->Draw(target, attributes);
	p_partsys->Draw(target, attributes);

	for (i_ObjectList = objectList.rbegin(); i_ObjectList != objectList.rend(); ++i_ObjectList)
	{
		i_ObjectList->second->Draw(target, attributes);
	}

	p_pauseButton->Draw(target, attributes);
	stats.Draw(target, attributes);
	overlay->Draw(target, attributes);
	p_gameOverPlaque->Draw(target, attributes);
	p_playButton->Draw(target, attributes);
}

// Private //

void GameScene::ReactToHit(GameObject* a)
{
	for (i_ObjectList = objectList.rbegin(); i_ObjectList != objectList.rend(); ++i_ObjectList)
	{
		if (i_ObjectList->second == a && i_ObjectList->first == "Astronaut")
		{
			//kill astronaut
			p_caveman->Hit();
			stats.addOxygen += 0.3f;
			stats.addScore += 100;
			//particles!
			p_partsys->transform.SetPosition(a->GetComponent<Rigidbody>()->GetPosition());
			p_partsys->SetEmitProperties(true, 0, 0.2f, 20, 40);
			particleTimer = 50;
		}
	}
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
	while (objectList.count("Cosmonaut") < 10)
	{
		objectList.insert(make_pair("Cosmonaut", prefabObject.CreateCosmonaut(p_world, GetRandomSpawnPosition())));
	}
	while (objectList.count("Asteroid") < 20)
	{
		objectList.insert(make_pair("Asteroid", prefabObject.CreateAsteroid(p_world, GetRandomSpawnPosition())));
	}
}
bool GameScene::DeleteObjects(GameObject* p_object)
{
	// Deletes objects that are too far away from the player. (Return's true if the object was deleted.)

	if (Vec2::distance(p_object->transform.GetPosition(), p_caveman->transform.GetPosition()) >= screenDiameter + 200)
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
	Vec2 temp;

	do {
		switch (randomNumber)
		{
		case 0: temp = Vec2(Randomizer::GetFloat(0, 1), Randomizer::GetFloat(0, 1)); break;
		case 1: temp = Vec2(Randomizer::GetFloat(0, 1), Randomizer::GetFloat(-1, 0)); break;
		case 2: temp = Vec2(Randomizer::GetFloat(-1, 0), Randomizer::GetFloat(-1, 0)); break;
		case 3: temp = Vec2(Randomizer::GetFloat(-1, 0), Randomizer::GetFloat(0, 1)); break;
		default: temp = Vec2(Randomizer::GetFloat(0, 1), Randomizer::GetFloat(0, 1)); break;
		}
	} while (temp.length() == 0);

	temp.normalize();
	temp *= screenDiameter;
	return temp + p_caveman->transform.GetPosition();
}
void GameScene::UpdateBackground()
{
	// Moves the background objects according to the player's movement to create an illusion of an endless background.

	for (int i = 0; i < 4; ++i)
	{
		if (p_background[i]->transform.GetPosition().x - uthEngine.GetWindow().GetCamera().GetPosition().x < uthEngine.GetWindowResolution().x * -1)
			p_background[i]->transform.SetPosition(p_background[i]->transform.GetPosition().x + uthEngine.GetWindowResolution().x * 2, p_background[i]->transform.GetPosition().y);
		else if (p_background[i]->transform.GetPosition().x - uthEngine.GetWindow().GetCamera().GetPosition().x > uthEngine.GetWindowResolution().x)
			p_background[i]->transform.SetPosition(p_background[i]->transform.GetPosition().x - uthEngine.GetWindowResolution().x * 2, p_background[i]->transform.GetPosition().y);

		if (p_background[i]->transform.GetPosition().y - uthEngine.GetWindow().GetCamera().GetPosition().y < uthEngine.GetWindowResolution().y * -1)
			p_background[i]->transform.SetPosition(p_background[i]->transform.GetPosition().x, p_background[i]->transform.GetPosition().y + uthEngine.GetWindowResolution().y * 2);
		else if (p_background[i]->transform.GetPosition().y - uthEngine.GetWindow().GetCamera().GetPosition().y > uthEngine.GetWindowResolution().y)
			p_background[i]->transform.SetPosition(p_background[i]->transform.GetPosition().x, p_background[i]->transform.GetPosition().y - uthEngine.GetWindowResolution().y * 2);
	}
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
		p_caveman->ChangeDirectionTouch(uthInput.Touch[0].GetStartPosition(), uthInput.Touch[0].GetEndPosition());
	else if (uthInput.Touch[0].Motion() == TouchMotion::TAP)
	{ /* TODO: Call caveman's hit function. */ 
	
	}

	// For testing.
	if (uthInput.Common.Event() == InputEvent::RELEASE)
		p_caveman->ChangeDirectionMouse(uthInput.Common.Position());
	if (uthInput.Common.Event() == InputEvent::TAP)
	{ /* TODO: Call caveman's hit function. */ 
		Vec2 hitPoint = uthEngine.GetWindow().PixelToCoords(uthInput.Common.Position());
		p_club->Hit(p_caveman->transform.GetPosition(), hitPoint);
	}
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

void GameScene::GameOverLay()
{
	// Gameover overlay in the same scene
	//paused = true;
	//p_gameOverPlaque->transform.SetPosition(uthEngine.GetWindow().GetCamera().GetPosition());
	//p_gameOverPlaque->SetActive(true);
	//p_playButton->transform.SetPosition(uthEngine.GetWindow().GetCamera().GetPosition() + (Vec2)(300, 100)); //// TODO: define final position!
	//p_playButton->SetActive(true);

	// OR: new scene!
	//saving score
	int newscore = stats.GetFinalScore();

	scorefile.open("newscore.dat", std::ios::binary | std::ios::out);
	if (scorefile)
	{
		scorefile.write((char*)&newscore, sizeof(int));
	}
	scorefile.close();
	uthSceneM.GoToScene(2);
}