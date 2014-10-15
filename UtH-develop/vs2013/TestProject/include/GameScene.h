#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <vector>
#include <UtH/UtHEngine.hpp>
#include <Caveman.h>
#include <PrefabObject.h>

using namespace uth;
using namespace std;

namespace uth
{
	class GameScene : public Scene
	{
	public:
		GameScene();
		~GameScene() override;

		bool Init() override;
		bool DeInit() override;

		void Update(float dt) override;
		void Draw(RenderTarget& target, RenderAttributes attributes = RenderAttributes()) override;

	private:
		// TODO:
		// Logic for gameobject that are hit by caveman.
		void ReactToHit();

		Caveman* p_caveman;
		GameObject* background; // Temporary background used for testing.
		PhysicsWorld* p_world;
		PrefabObject prefabObject;
		vector<GameObject*> objectList;

		// For testing with pc. Can be deleted later.
		InputEvent lastStatePC;
	};
}

#endif