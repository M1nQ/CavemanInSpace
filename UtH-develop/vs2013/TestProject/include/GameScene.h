#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <vector>
#include <UtH/UtHEngine.hpp>
#include <Caveman.h>
#include <PrefabObject.h>
#include <map>

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
		void AddObjects();
		bool DeleteObjects(GameObject* p_object);
		void UpdateBackground();
		Vec2 GetRandomSpawnPosition();

		Caveman* p_caveman;
		GameObject* background; // Temporary background used for testing.
		PhysicsWorld* p_world;
		PrefabObject prefabObject;
		//multimap<string, GameObject*> objectList;
		//multimap<string, GameObject*>::reverse_iterator i_ObjectList;
		vector<GameObject*> objects; // Temporary object list for testing.

		// For testing with pc. Can be deleted later.
		InputEvent lastStatePC;
	};
}

#endif