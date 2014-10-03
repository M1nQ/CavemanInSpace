#ifndef SCENES_H
#define SCENES_H
#define UTHDefaultScene -1

// Enumeration of scenes, giving name for each scene number
enum SceneName
{
	DEFAULT = UTHDefaultScene,
	TITLE,
	MENU,
	GAME,
	GAMEOVER,
	COUNT // Keep this last, it tells how many scenes there are
};

#endif //SCENES_H

#ifdef NEWSCENEFUNC
#undef NEWSCENEFUNC

#include <TitleScene.h>
#include <MenuScene.h>
#include <GameScene.h>
#include <GameOverScene.h>

using namespace uth;

// Create function for a new scene, having a case for every user made scene
Scene* NewSceneFunc(int SceneID)
{
	switch (SceneID)
	{
	case TITLE:		return new TitleScene();
	case MENU:		return new MenuScene();
	case GAME:		return new GameScene();
	case GAMEOVER:	return new GameOverScene();
	default:		return nullptr;
	}
}

#endif // NEWSCENEFUNC