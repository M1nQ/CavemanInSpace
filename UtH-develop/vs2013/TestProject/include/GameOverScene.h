#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include <UtH/UtHEngine.hpp>
#include <Button.h>
#include <EndScreen.h>
#include <fstream>
#include <Statistics.h>

using namespace uth;

namespace uth
{
	class GameOverScene : public Scene
	{
	public:
		GameOverScene();
		~GameOverScene() override;

		bool Init() override;
		bool DeInit() override;

		void Update(float dt) override;
		void Draw(RenderTarget& target, RenderAttributes attributes = RenderAttributes()) override;
		
	private:
		void GetFinalScore();
		void FindOldScores();
		void SaveHighScores();

		Texture* startTex;
		Button* startButton;
		GameObject* background;

		Sound* music;
		EndScreen end;

		std::fstream savefile;

		FileManager files;

		//working copy of scores, should be changed into a multimap if names needed
		int allscores[4];
		string stringscores[4];
		int finalscore;
	};
}
#endif