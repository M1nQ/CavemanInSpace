#ifndef ARROW_H
#define ARROW_H

#include <UtH/UtHEngine.hpp>

using namespace uth;
using namespace pmath;

class Arrow :
	public GameObject
{
public:
	Arrow(){}
	~Arrow(){}

	void Init();
	void update(Vec2 cavemanPos);
	void DrawArrow(Vec2 startPos);
	void DisableArrow();

private:
	Texture* arrowPic;
	Vec2 direction;
	Vec2 start;
	
	float scale;

};
#endif
