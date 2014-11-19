#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <vector>
#include <UtH/UtHEngine.hpp>
#include <Caveman.h>
#include <PrefabObject.h>
#include <OxygenAffector.h>
#include <map>
#include <Statistics.h>
#include <Button.h>
#include <Club.h>
#include <fstream>

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
		bool DeleteObjects(GameObject* p_object);
		Vec2 GetRandomSpawnPosition();
		// Logic for gameobject that are hit by caveman.
		void ReactToHit(GameObject* a);
		void MaintainObjectList(float dt);
		void AddObjects();
		void UpdateBackground();
		void UpdateCameraMovement(float dt);
		void Input();
		void UpdateButtonPositions();
		void GameOverLay();

		bool paused;
		Button* p_pauseButton;
		Button* p_playButton;
		Caveman* p_caveman;
		Club* p_club;
		float particleTimer;
		GameObject* overlay;
		multimap<string, GameObject*> objectList;
		multimap<string, GameObject*>::reverse_iterator i_ObjectList;
		ParticleSystem* p_partsys;
		PhysicsContactListener contactListener;
		PhysicsWorld* p_world;
		PrefabObject prefabObject;
		Statistics stats;	
		GameObject* background; // Temporary background used for testing.
		GameObject* p_gameOverPlaque;

		std::fstream scorefile;
	};
}

#endif