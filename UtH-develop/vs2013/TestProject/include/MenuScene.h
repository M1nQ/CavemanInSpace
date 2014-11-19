#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <UtH/UtHEngine.hpp>
#include <fstream>
#include "Button.h"

using namespace uth;
using namespace std;

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
		void SetScoreText();
		void SetOverlayMode();
		void CloseOverlayMode();
		void Scores_SetActive(bool active);

		//Window wnd;

		Button* startButton;
		Button* creditsButton;
		Button* highScores;
		Button* closeButton;

		Texture* startTex;
		Texture* creditTex;
		Texture* scoreTex;
		Texture* closeTex;

		GameObject* background;
		GameObject* credits;

		GameObject* leaderboard[3];

		std::fstream highscorefile;

		int scores[3];
		pmath::Vec4 textColor;
	};
}

#endif