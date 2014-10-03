#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <UtH/UtHEngine.hpp>

using namespace uth;

namespace uth
{
	class MenuScene : public Scene
	{
	public:
		MenuScene();
		~MenuScene() override;

		bool Init() override;
		bool DeInit() override;

		void Update(float dt) override;
		void Draw(RenderTarget& target, RenderAttributes attributes = RenderAttributes()) override;

	private:

		// TODO:
		// Buttons

		// Top three scores are read from a safe file. May be moved to TitleScene.
		void ReadHighScores();

		GameObject* credits;

		GameObject* leaderBoard;
	};
}

#endif