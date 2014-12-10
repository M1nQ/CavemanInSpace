#include <GameOverScene.h>

GameOverScene::GameOverScene() {}
GameOverScene::~GameOverScene() {}

bool GameOverScene::Init()
{
	background = new GameObject();
	background->AddComponent(new Sprite("Placeholders/endBg.png"));
	background->transform.ScaleToSize(uthEngine.GetWindow().GetCamera().GetSize());
	background->transform.SetPosition(uthEngine.GetWindow().GetCamera().GetPosition());
	
	startTex = uthRS.LoadTexture("Placeholders/Play.png");

	music = uthRS.LoadSound("sounds/C64_feels.ogg");
	music->Loop(true);

	// fill in the scores array so that newest is last
	FindOldScores();
	GetFinalScore();

	end = EndScreen();
	end.SetFinalScore(allscores[3]);
	int newScore = allscores[3]; // because SaveHighScores will change list order
	
	SaveHighScores();
	end.SetHighScores(allscores[0], allscores[1], allscores[2], newScore);

	startButton = new Button(uthEngine.GetWindow(), startTex);	
	startButton->setCallBack([]()
	{
		uthSceneM.GoToScene(1);
	});

	Vec2 offset = Vec2(350, 160);
	startButton->transform.SetPosition(uthEngine.GetWindow().GetCamera().GetPosition() + offset);
	AddChild<Button>(startButton);

	return true;
}
bool GameOverScene::DeInit()
{
	return true;
}
void GameOverScene::Update(float dt)
{
	Scene::Update(dt);
	end.Update(dt);
}
void GameOverScene::Draw(RenderTarget& target, RenderAttributes attributes)
{
	background->Draw(target, attributes);
	Scene::Draw(target, attributes);
	end.Draw(target, attributes);
}

// Private //

void GameOverScene::GetFinalScore()
{
	files.OpenFile("newscore.dat");
	stringscores[3] = files.ReadText();
	files.CloseFile();
	allscores[3] = stoi(stringscores[3]);

	/*savefile.open("newscore.dat", std::ios::binary | std::ios::in);
	if (savefile)
	{
		savefile.read((char*)&allscores[3], sizeof(int));
	}
	savefile.close();*/

	
}

void GameOverScene::FindOldScores()
{
	// read higscores
	/*savefile.open("highscores.dat", std::ios::binary | std::ios::in);
	if (savefile)
	{*/
	files.OpenFile("highscores1.dat");
	stringscores[0] = files.ReadText();
	files.CloseFile();
	files.OpenFile("highscores2.dat");
	stringscores[1] = files.ReadText();
	files.CloseFile();
	files.OpenFile("highscores3.dat");
	stringscores[2] = files.ReadText();
	files.CloseFile();

	for (int i = 0; i < 3; ++i)
	{
		allscores[i] = stoi(stringscores[i]);
	}
	/*}
	savefile.close();	*/
}

void GameOverScene::SaveHighScores()
{
	// sort scores
	int temp;
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 3; i > j; --i)
		{
			if (allscores[i] > allscores[i - 1])
			{
				temp = allscores[i];
				allscores[i] = allscores[i - 1];
				allscores[i - 1] = temp;				
			}
		}
	}
	for (int i = 0; i < 3; ++i)
	{
		stringscores[i] = to_string(allscores[i]);
	}

	// write new highscore list, 3 biggest scores

	files.OpenFile("highscores1.dat", FileManager::Location::ASSET, true);
	files.WriteString(stringscores[0]);
	files.CloseFile();
	files.OpenFile("highscores2.dat", FileManager::Location::ASSET, true);
	files.WriteString(stringscores[1]);
	files.CloseFile();
	files.OpenFile("highscores3.dat", FileManager::Location::ASSET, true);
	files.WriteString(stringscores[2]);
	files.CloseFile();


	/*savefile.open("highscores.dat", std::ios::binary | std::ios::out);
	if (savefile)
	{
		
		savefile.write((char*)&allscores[0], sizeof(int));
		savefile.write((char*)&allscores[1], sizeof(int));
		savefile.write((char*)&allscores[2], sizeof(int));
		
	}
	savefile.close();*/
}