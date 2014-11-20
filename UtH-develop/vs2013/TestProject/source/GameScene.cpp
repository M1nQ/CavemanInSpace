#include <GameScene.h>

GameScene::GameScene() {}
GameScene::~GameScene() {}

bool GameScene::Init()
{	
	VariableInit();
	ParticleInit();
	ContactLogicInit();
	ButtonsInit();
	PauseInit();
	BackgroundInit();

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
		p_club->update(dt, p_caveman->transform.GetPosition());
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
	if (stats.IsDead())
			GameOverLogic();
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
	p_playButton->Draw(target, attributes);
}

// Private //

void GameScene::ReactToHit(GameObject* a)
{
	for (i_ObjectList = objectList.rbegin(); i_ObjectList != objectList.rend(); ++i_ObjectList)
	{
		if (i_ObjectList->second == a)
		{
			if (i_ObjectList->first == "Astronaut")
			{
				a->GetComponent<NautComponent>()->Hit(p_club->transform.GetPosition());

				//kill astronaut
				if (a->GetComponent<NautComponent>()->isDead() && a->GetComponent<NautComponent>()->oxygen > 0)
				{
					stats.addOxygen += a->GetComponent<NautComponent>()->oxygen;
					a->GetComponent<NautComponent>()->oxygen = 0;
					stats.addScore += 100;
					//particles!
					p_partsys->transform.SetPosition(a->GetComponent<Rigidbody>()->GetPosition());
					p_partsys->SetEmitProperties(true, 0, 0.2f, 20, 40);
					particleTimer = 50;
				}
			}
			else if (i_ObjectList->first == "Cosmonaut")
			{
				a->GetComponent<NautComponent>()->Hit(p_club->transform.GetPosition());

				if (a->GetComponent<NautComponent>()->isDead() && a->GetComponent<NautComponent>()->oxygen > 0)
				{
					stats.addOxygen += a->GetComponent<NautComponent>()->oxygen;
					a->GetComponent<NautComponent>()->oxygen = 0;
					stats.addScore += 200;
					//particles!
					p_partsys->transform.SetPosition(a->GetComponent<Rigidbody>()->GetPosition());
					p_partsys->SetEmitProperties(true, 0, 0.2f, 20, 40);
					particleTimer = 50;
				}
			}
			else if (i_ObjectList->first == "Asteroid")
			{
				stats.addScore += 10;
				p_partsys->transform.SetPosition(a->GetComponent<Rigidbody>()->GetPosition());
				p_partsys->SetEmitProperties(true, 0, 0.2f, 20, 40);
				
				particleTimer = 50;
				// TODO: destroy object, change particles to animation?
				a->SetActive(false);
			}
			else {}
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

	if (stats.GetGameTime() > 60)
	{
		asteroidAmount = 30;
		astronautAmount = 10;
		cosmonautAmount = 5;
	}
	else if (stats.GetGameTime() > 50)
	{
		asteroidAmount = 40;
		astronautAmount = 15;
		cosmonautAmount = 10;
	}
	else if (stats.GetGameTime() > 40)
	{
		asteroidAmount = 40;
		astronautAmount = 20;
		cosmonautAmount = 10;
	}
	else if (stats.GetGameTime() > 30)
	{
		asteroidAmount = 50;
		astronautAmount = 20;
		cosmonautAmount = 15;
	}
	else if (stats.GetGameTime() > 20)
	{
		asteroidAmount = 40;
		astronautAmount = 30;
		cosmonautAmount = 20;
	}
	else if (stats.GetGameTime() > 10)
	{
		asteroidAmount = 30;
		astronautAmount = 30;
		cosmonautAmount = 30;
	}
}
void GameScene::AddObjects()
{
	// Maintains the objectlist so, that it always holds a certain amount of specified objects.
	
	while (objectList.count("Astronaut") < astronautAmount)
	{
		objectList.insert(make_pair("Astronaut", prefabObject.CreateAstronaut(p_world, GetRandomSpawnPosition())));
	}
	while (objectList.count("Cosmonaut") < cosmonautAmount)
	{
		objectList.insert(make_pair("Cosmonaut", prefabObject.CreateCosmonaut(p_world, GetRandomSpawnPosition())));
	}
	while (objectList.count("Asteroid") < asteroidAmount)
	{
		objectList.insert(make_pair("Asteroid", prefabObject.CreateAsteroid(p_world, GetRandomSpawnPosition())));
	}
}
bool GameScene::DeleteObjects(GameObject* p_object)
{
	// Deletes objects that are too far away from the player. (Return's true if the object was deleted.)
	if (p_object->HasTag("Naut"))
	{
		if ((p_object->GetComponent<NautComponent>()->isDead() && p_object->GetComponent<Sprite>()->GetColor().a <= 0))
		{
			delete(p_object);
			return true;
		}
	}
	else if (Vec2::distance(p_object->transform.GetPosition(), p_caveman->transform.GetPosition()) >= screenDiameter)
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
		if (p_background[i]->transform.GetPosition().x - uthEngine.GetWindow().GetCamera().GetPosition().x < p_background[1]->GetComponent<Sprite>()->GetSize().x * -1)
			p_background[i]->transform.SetPosition(p_background[i]->transform.GetPosition().x + p_background[1]->GetComponent<Sprite>()->GetSize().x * 2, p_background[i]->transform.GetPosition().y);
		else if (p_background[i]->transform.GetPosition().x - uthEngine.GetWindow().GetCamera().GetPosition().x > p_background[1]->GetComponent<Sprite>()->GetSize().x)
			p_background[i]->transform.SetPosition(p_background[i]->transform.GetPosition().x - p_background[1]->GetComponent<Sprite>()->GetSize().x * 2, p_background[i]->transform.GetPosition().y);

		if (p_background[i]->transform.GetPosition().y - uthEngine.GetWindow().GetCamera().GetPosition().y < p_background[1]->GetComponent<Sprite>()->GetSize().y * -1)
			p_background[i]->transform.SetPosition(p_background[i]->transform.GetPosition().x, p_background[i]->transform.GetPosition().y + p_background[1]->GetComponent<Sprite>()->GetSize().y * 2);
		else if (p_background[i]->transform.GetPosition().y - uthEngine.GetWindow().GetCamera().GetPosition().y > p_background[1]->GetComponent<Sprite>()->GetSize().y)
			p_background[i]->transform.SetPosition(p_background[i]->transform.GetPosition().x, p_background[i]->transform.GetPosition().y - p_background[1]->GetComponent<Sprite>()->GetSize().y * 2);
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
	// Handles touch input.
	if (uthInput.Touch[0].Motion() == TouchMotion::DRAG && Vec2::distance(uthInput.Touch[0].GetStartPosition(), uthInput.Common.Position()) > 10)
	{
		if (p_arrow->IsActive() == false)
			p_arrow->DrawArrow(uthInput.Touch[0].GetStartPosition());
		else p_arrow->update(p_caveman->transform.GetPosition());
	}
	if (uthInput.Touch[0].Motion() == TouchMotion::RELEASE && Vec2::distance(uthInput.Touch[0].GetStartPosition(), uthInput.Touch[0].GetEndPosition()) > 10)
	{
		p_arrow->DisableArrow();
		p_caveman->ChangeDirectionTouch(uthInput.Touch[0].GetStartPosition(), uthInput.Touch[0].GetEndPosition());
	}
	else if (uthInput.Touch[0].Motion() == TouchMotion::TAP)
	{  
		Vec2 hitPoint = uthEngine.GetWindow().PixelToCoords(uthInput.Common.Position());
		p_club->Hit(p_caveman->transform.GetPosition(), hitPoint);
	}

	// Mouse input for testing.
	if (uthInput.Mouse.IsButtonDown(Mouse::MButton::LEFT) == true && p_arrow->IsActive() == false)
		p_arrow->DrawArrow(uthInput.Common.Position());
	if (uthInput.Common.Event() == InputEvent::DRAG)
	{
		p_arrow->update(p_caveman->transform.GetPosition());
	}
	if (uthInput.Common.Event() == InputEvent::RELEASE)
	{
		p_caveman->ChangeDirectionMouse(uthInput.Common.Position());
		p_arrow->DisableArrow();
	}
	if (uthInput.Common.Event() == InputEvent::TAP)
	{  
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
void GameScene::GameOverLogic()
{
	int newscore = stats.GetFinalScore();

	scorefile.open("newscore.dat", std::ios::binary | std::ios::out);
	if (scorefile)
	{
		scorefile.write((char*)&newscore, sizeof(int));
	}
	scorefile.close();
	uthSceneM.GoToScene(2);
}

// Initialization

void GameScene::BackgroundInit()
{
	for (int i = 0; i < 4; ++i)
	{
		p_background[i] = new GameObject("Background");
		p_background[i]->AddComponent(new Sprite("Big_Background.png"));
	}
	p_background[1]->transform.SetPosition(Vec2(p_background[1]->GetComponent<Sprite>()->GetSize().x, 0));
	p_background[2]->transform.SetPosition(Vec2(0, p_background[1]->GetComponent<Sprite>()->GetSize().y));
	p_background[3]->transform.SetPosition(p_background[1]->GetComponent<Sprite>()->GetSize());
}
void GameScene::PauseInit()
{
	// Game paused overlay
	overlay = new GameObject();
	overlay->AddComponent(new Sprite("Overlay.png"));
	overlay->transform.ScaleToSize(uthEngine.GetWindow().GetCamera().GetSize());
	overlay->SetActive(false);
}
void GameScene::ButtonsInit()
{
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
}
void GameScene::ContactLogicInit()
{
	contactListener = PhysicsContactListener();
	contactListener.onBeginContact = [this](b2Contact* contact, GameObject* a, GameObject* b)
	{
		if (b->HasTag("Club"))
		{
			ReactToHit(a);
			p_club->HasHit();
		}
		else if (a->HasTag("Club"))
		{
			ReactToHit(b);
			p_club->HasHit();
		}
		else {}
	};
	p_world->SetContactListener(&contactListener);
}
void GameScene::ParticleInit()
{
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
}
void GameScene::VariableInit()
{
	asteroidAmount = 40;
	astronautAmount = 40;
	cosmonautAmount = 25;

	paused = false;
	screenDiameter = sqrt(pow(uthEngine.GetWindowResolution().x, 2) + pow(uthEngine.GetWindowResolution().y, 2));

	Randomizer::SetSeed(time(NULL));
	p_world = new PhysicsWorld(0, 0);

	p_caveman = new Caveman();
	AddChild<Caveman>(p_caveman);
	p_caveman->Init(p_world);

	p_club = new Club(p_caveman->transform.GetSize());
	p_club->Init(p_world);
	AddChild<Club>(p_club);

	p_arrow = new Arrow();
	p_arrow->Init();
	AddChild<Arrow>(p_arrow);

	prefabObject = PrefabObject();
	stats = Statistics();

	uthEngine.GetWindow().GetCamera().SetPosition(p_caveman->transform.GetPosition());
}