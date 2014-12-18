#include <LoadScene.h>

bool LoadScene::Init()
{
	loadbg = new GameObject("loader");
	loadbg->AddComponent(new Sprite("Placeholders/title_screen.png"));
	loadbg->transform.ScaleToSize(uthEngine.GetWindow().GetCamera().GetSize());
	return true;
}
bool LoadScene::DeInit()
{
	return true;
}

void LoadScene::Update(float dt)
{
	if (LoadEverything())
		uthSceneM.GoToScene(1);
}
void LoadScene::Draw(RenderTarget& target, RenderAttributes attributes)
{
	loadbg->Draw(target, attributes);
}

// Load all assets
bool LoadScene::LoadEverything()
{
	
	uthRS.LoadTexture("Placeholders/Play.png");
	uthRS.LoadTexture("Placeholders/credButton.png");
	uthRS.LoadTexture("Placeholders/HiScore.png");
	uthRS.LoadTexture("Placeholders/Close.png");
	uthRS.LoadTexture("Placeholders/Tutorial.png");
	uthRS.LoadTexture("Placeholders/Title_screen.png");
	uthRS.LoadTexture("Placeholders/credits.png");
	uthRS.LoadTexture("Placeholders/Hiscorebg.png");
	uthRS.LoadTexture("Placeholders/Tutorial_screen2.png");
	uthRS.LoadTexture("Big_Background.png");
	uthRS.LoadTexture("Overlay.png");
	uthRS.LoadTexture("Placeholders/Pause.png");
	uthRS.LoadTexture("Placeholders/Replay.png");
	uthRS.LoadTexture("Placeholders/oxypart.png");
	uthRS.LoadTexture("Placeholders/rockpart.png");
	uthRS.LoadTexture("AstronautAnim.png");
	uthRS.LoadTexture("CosmonautAnim.png");
	uthRS.LoadTexture("Placeholders/Asteroid_3.png");
	uthRS.LoadTexture("Placeholders/Asteroid_4.png");
	uthRS.LoadTexture("caveman_animations.png");
	uthRS.LoadTexture("Placeholders/endBg.png");
	uthRS.LoadTexture("Placeholders/Pointer.png");
	uthRS.LoadTexture("Placeholders/oxygenbar_placeholder.png");

	uthRS.LoadSound("sounds/menumusic.ogg");
	uthRS.LoadSound("sounds/gamemusic.ogg");
	uthRS.LoadSound("sounds/astronaut_dying_groan.wav");
	uthRS.LoadSound("sounds/astronaut_hit.wav");
	uthRS.LoadSound("sounds/astronaut_panic_voice_1.wav");
	uthRS.LoadSound("sounds/astronaut_panic_voice_2.wav");
	uthRS.LoadSound("sounds/caveman_club_attack.wav");
	uthRS.LoadSound("sounds/caveman_move.wav");
	uthRS.LoadSound("sounds/hit_sound_metal.wav");
	uthRS.LoadSound("sounds/hit_sound_rock.wav");

	return true;
}