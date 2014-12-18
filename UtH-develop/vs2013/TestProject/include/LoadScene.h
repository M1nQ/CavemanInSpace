#ifndef LOADSCENE_H
#define LOADSCENE_H

#include <UtH/UtHEngine.hpp>

using namespace uth;
using namespace std;

namespace uth
{
	class LoadScene : public Scene
	{
	public:
		LoadScene(){}
		~LoadScene(){}

		bool Init() override;
		bool DeInit() override;

		void Update(float dt) override;
		void Draw(RenderTarget& target, RenderAttributes attributes = RenderAttributes()) override;

		bool LoadEverything();

		GameObject* loadbg;
		Texture* textures[20];
	};
}

#endif