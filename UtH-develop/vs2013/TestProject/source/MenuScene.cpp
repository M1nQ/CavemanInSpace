#include <MenuScene.h>

MenuScene::MenuScene() 
{
	textColor = pmath::Vec4(0.1f,0.1f,0.1f,1);
}
MenuScene::~MenuScene() {}

bool MenuScene::Init()
{
	// Back button
	uthInput.SetAndroidBackFunction([]() { uthEngine.Exit(); });

	// Button textures
	startTex = uthRS.LoadTexture("Placeholders/Play.png");
	creditTex = uthRS.LoadTexture("Placeholders/credButton.png");
	scoreTex = uthRS.LoadTexture("Placeholders/HiScore.png");
	closeTex = uthRS.LoadTexture("Placeholders/Close.png");
	tutorialTex = uthRS.LoadTexture("Placeholders/Tutorial.png");

	/*buttonSound = uthRS.LoadSound("");*/
	music = uthRS.LoadSound("sounds/menumusic.ogg");
	music->Loop(true);
	music->Play();

	background = new GameObject("Background");
	background->AddComponent(new Sprite("Placeholders/Title_screen.png"));
	background->transform.ScaleToSize(uthEngine.GetWindow().GetCamera().GetSize());
	
	// credit screen specs
	credits = new GameObject("Credits");
	credits->AddComponent(new Sprite("Placeholders/credits.png"));
	credits->transform.ScaleToSize(uthEngine.GetWindow().GetCamera().GetSize());
	AddChild<GameObject>(credits);

	// high score screen specs
	hiscorebg = new GameObject("Hiscorebg");
	hiscorebg->AddComponent(new Sprite("Placeholders/Hiscorebg.png"));
	hiscorebg->transform.ScaleToSize(uthEngine.GetWindow().GetCamera().GetSize());
	AddChild<GameObject>(hiscorebg);

	// tutorial screen
	tutorial = new GameObject("Tutorial");
	tutorial->AddComponent(new Sprite("Placeholders/Tutorial_screen2.png"));
	// set size to fit screen height
	float scaleratio = uthEngine.GetWindow().GetCamera().GetSize().y / tutorial->transform.GetSize().y;
	Vec2 size = Vec2(tutorial->transform.GetSize().x * scaleratio, tutorial->transform.GetSize().y * scaleratio);

	tutorial->transform.ScaleToSize(size);
	AddChild<GameObject>(tutorial);

	// size & place


	ReadHighScores();
	SetScoreText();

	ButtonInit();

	CloseOverlayMode();

	return true;
}
bool MenuScene::DeInit()
{
	music->Stop();
	return true;
}
void MenuScene::Update(float dt)
{
	Scene::Update(dt);
	//credits->Update(dt);
}
void MenuScene::Draw(RenderTarget& target, RenderAttributes attributes)
{
	background->Draw(target);
	//credits->Draw(target);
	Scene::Draw(target);
	
}

// Private //

void MenuScene::ReadHighScores()
{
	FileManager files;

	files.OpenFile("highscores1.dat", FileManager::Location::INTERNAL);
	stringscores[0] = files.ReadText();
	files.CloseFile();
	files.OpenFile("highscores2.dat", FileManager::Location::INTERNAL);
	stringscores[1] = files.ReadText();
	files.CloseFile();
	files.OpenFile("highscores3.dat", FileManager::Location::INTERNAL);
	stringscores[2] = files.ReadText();
	files.CloseFile();
}


// TODO: Uncomment Play calls when sound is implemented!

void MenuScene::SetOverlayMode(GameObject* bgPic)
{
	//buttonSound->Play();
	// set overlay and closeOverlay active
	bgPic->SetActive(true);
	closeButton->SetActive(true);
	// disable menuscreen buttons
	startButton->SetActive(false);
	highScores->SetActive(false);
	creditsButton->SetActive(false);
	tutorialButton->SetActive(false);
}
void MenuScene::CloseOverlayMode()
{
	//buttonSound->Play();
	// disable overlay etc.
	tutorial->SetActive(false);
	credits->SetActive(false);
	hiscorebg->SetActive(false);
	closeButton->SetActive(false);
	Scores_SetActive(false);

	// set buttons active
	startButton->SetActive(true);
	creditsButton->SetActive(true);
	highScores->SetActive(true);
	tutorialButton->SetActive(true);
}

void MenuScene::SetScoreText()
{

	for (int i = 0; i < 3; ++i)
	{
		string text = to_string(i + 1) + ":   " + stringscores[i];
		leaderboard[i] = new GameObject();
		leaderboard[i]->AddComponent(new Text("KOMIKAX_.ttf", 50.f, "Score"));
		leaderboard[i]->GetComponent<Text>("Score")->AddText((text), textColor);
		leaderboard[i]->transform.SetPosition((uthEngine.GetWindow().GetCamera().GetPosition()) + pmath::Vec2(30, (70 * i)-50));
		AddChild<GameObject>(leaderboard[i]);
		leaderboard[i]->SetActive(false);
	}
}

void MenuScene::Scores_SetActive(bool active)
{
	for (int i = 0; i < 3; ++i)
	{
		leaderboard[i]->SetActive(active);
	}
}

void MenuScene::ButtonInit()
{
	Vec2 bsize = creditTex->GetSize();
	Vec2 scrsize = uthEngine.GetWindow().GetSize();
	float offsetX = scrsize.x / 9;
	// show credits -button
	creditsButton = new Button(uthEngine.GetWindow(), creditTex);
	creditsButton->setCallBack([this]()
	{
		SetOverlayMode(credits);
	});
	creditsButton->transform.SetPosition(offsetX * 3, scrsize.y/2 - bsize.y);
	AddChild<Button>(creditsButton);

	// show highscores -button
	highScores = new Button(uthEngine.GetWindow(), scoreTex);
	highScores->setCallBack([this]()
	{
		SetOverlayMode(hiscorebg);
		Scores_SetActive(true);
	});
	highScores->transform.SetPosition(-(offsetX * 3), scrsize.y / 2 - bsize.y);
	AddChild<Button>(highScores);

	// show tutorial -button
	tutorialButton = new Button(uthEngine.GetWindow(), tutorialTex);
	tutorialButton->setCallBack([this]()
	{
		SetOverlayMode(tutorial);
	});
	
	tutorialButton->transform.SetPosition(-offsetX, scrsize.y / 2 - bsize.y);
	AddChild<Button>(tutorialButton);

	// start game -button
	startButton = new Button(uthEngine.GetWindow(), startTex);
	startButton->setCallBack([]()
	{
		uthSceneM.GoToScene(1);
	});
	startButton->transform.SetPosition(offsetX, scrsize.y / 2 - bsize.y);
	AddChild<Button>(startButton);

	// close overlay -button
	closeButton = new Button(uthEngine.GetWindow(), closeTex);
	closeButton->setCallBack([this]()
	{
		CloseOverlayMode();
	});
	closeButton->transform.SetPosition((scrsize.x - bsize.x) / 2, -(scrsize.y - bsize.y) / 2);
	AddChild<Button>(closeButton);

}