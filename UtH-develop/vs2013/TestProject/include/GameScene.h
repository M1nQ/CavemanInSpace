#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <UtH/UtHEngine.hpp>
#include "Caveman.h"

using namespace uth;

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
		Caveman* caveman;
		TouchMotion lastState;
		PhysicsWorld* World;
	};
}

#endif