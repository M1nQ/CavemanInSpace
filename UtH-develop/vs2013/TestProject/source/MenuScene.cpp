#include <MenuScene.h>

MenuScene::MenuScene() 
{
	std:: fstream highscorefile("highscores.dat");
}
MenuScene::~MenuScene() {}

bool MenuScene::Init()
{
	startTex = uthRS.LoadTexture("Placeholders/caveman.png");
	creditTex = uthRS.LoadTexture("Placeholders/credButton.png");
	scoreTex = uthRS.LoadTexture("Placeholders/HiScore.png");
	closeTex = uthRS.LoadTexture("Placeholders/eimitn.png");

	background = new GameObject("Background");
	background->AddComponent(new Sprite("Placeholders/Title_screen.png"));
	background->transform.ScaleToSize(uthEngine.GetWindow().GetCamera().GetSize());
	
	credits = new GameObject("Credits");
	credits->AddComponent(new Sprite("Placeholders/credits.png"));
	credits->transform.ScaleToSize(uthEngine.GetWindow().GetCamera().GetSize());

	
	ReadHighScores();

	creditsButton = new Button(uthEngine.GetWindow(), creditTex);
	creditsButton->setCallBack([this]()
	{
		SetOverlayMode();
	});
	creditsButton->transform.SetPosition(250, 250);
	AddChild<Button>(creditsButton);

	highScores = new Button(uthEngine.GetWindow(), scoreTex);
	highScores->setCallBack([this]()
	{
		SetOverlayMode();
	});
	highScores->transform.SetPosition(-250, 250);
	AddChild<Button>(highScores);

	startButton = new Button(uthEngine.GetWindow(), startTex);
	// TODO: credits, highscores
	startButton->setCallBack([]()
	{
		uthSceneM.GoToScene(1);
	});

	startButton->transform.SetPosition(0, 250);
	AddChild<Button>(startButton);

	closeButton = new Button(uthEngine.GetWindow(), closeTex);
	closeButton->setCallBack([this]()
	{
		CloseOverlayMode();
	});
	closeButton->transform.SetPosition(250, -250);
	AddChild<Button>(closeButton);
	
	CloseOverlayMode();

	return true;
}
bool MenuScene::DeInit()
{
	return true;
}
void MenuScene::Update(float dt)
{
	Scene::Update(dt);
	credits->Update(dt);

	/*if (credits->IsActive() == true && uthInput.Common.Event() == uth::InputEvent::TAP)
	{
		credits->SetActive(false);
	}*/
	
}
void MenuScene::Draw(RenderTarget& target, RenderAttributes attributes)
{
	background->Draw(target, attributes);
	credits->Draw(target, attributes);
	Scene::Draw(target, attributes);
	
}

// Private //

void MenuScene::ReadHighScores()
{
	highscorefile.open("highscores.dat", std::ios::binary | std::ios::in);
	if (highscorefile)
	{
		while (highscorefile.peek() != EOF)
		{
			for (int i = 0; i < 3; ++i)
				highscorefile.read((char*)&scores[i], sizeof(int));
		}
	}
	highscorefile.close();
}

void MenuScene::SetOverlayMode()
{
	credits->SetActive(true);
	closeButton->SetActive(true);
	startButton->SetActive(false);
	highScores->SetActive(false);
	creditsButton->SetActive(false);
}
void MenuScene::CloseOverlayMode()
{
	credits->SetActive(false);
	closeButton->SetActive(false);
	startButton->SetActive(true);
	creditsButton->SetActive(true);
	highScores->SetActive(true);
}