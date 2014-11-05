#include <MenuScene.h>

MenuScene::MenuScene() {}
MenuScene::~MenuScene() {}

bool MenuScene::Init()
{
	startTex = uthRS.LoadTexture("Placeholders/caveman.png");
	creditTex = uthRS.LoadTexture("Placeholders/astronautPlaceHolder.png");
	closeTex = uthRS.LoadTexture("Placeholders/eimitn.png");

	background = new GameObject("Background");
	background->AddComponent(new Sprite("Placeholders/Title_screen.png"));
	background->transform.ScaleToSize(uthEngine.GetWindow().GetCamera().GetSize());
	
	credits = new GameObject("Credits");
	credits->AddComponent(new Sprite("Placeholders/credits.png"));
	credits->transform.ScaleToSize(uthEngine.GetWindow().GetCamera().GetSize());
	credits->SetActive(false);

	creditsButton = new Button(uthEngine.GetWindow(), creditTex);
	creditsButton->setCallBack([this]()
	{
		credits->SetActive(true);
		closeButton->SetActive(true);
		startButton->SetActive(false);
		creditsButton->SetActive(false);
	});
	creditsButton->transform.SetPosition(250, 250);
	AddChild<Button>(creditsButton);

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
		credits->SetActive(false);
		closeButton->SetActive(false);
		startButton->SetActive(true);
		creditsButton->SetActive(true);
	});
	closeButton->transform.SetPosition(250, -250);
	AddChild<Button>(closeButton);
	closeButton->SetActive(false);

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

void ReadHighScores()
{
}