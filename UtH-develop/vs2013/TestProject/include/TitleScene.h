#ifndef TITLESCENE_H
#define TITLESCENE_H

#include <UtH/UtHEngine.hpp>
#include <UtH/Engine/SceneManager.hpp>

using namespace uth;

namespace uth
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		~TitleScene() override;

		// TODO:
		// Read high scores from save file?
		bool Init() override;
		bool DeInit() override;

		void Update(float dt) override;
		void Draw(RenderTarget& target, RenderAttributes attributes = RenderAttributes()) override;

	private:

	};
}
#endif