#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include <UtH/UtHEngine.hpp>

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
		void CountFinalScore();
		void SaveHighScores();
	};
}
#endif