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
		void MaintainObjectList(float dt);
		void AddObjects();
		bool DeleteObjects(GameObject* p_object);
		Vec2 GetRandomSpawnPosition();
		void UpdateBackground();
		void UpdateCameraMovement(float dt);
		void Input();

		Caveman* p_caveman;
		GameObject* background; // Temporary background used for testing.
		PhysicsWorld* p_world;
		PhysicsContactListener contactListener;
		PrefabObject prefabObject;
		multimap<string, GameObject*> objectList;
		multimap<string, GameObject*>::reverse_iterator i_ObjectList;		
	};
}

#endif