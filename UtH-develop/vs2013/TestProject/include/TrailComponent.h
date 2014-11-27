#ifndef TRAILCOMPONENT_H
#define TRAILCOMPONENT_H

#include <CavemanGame.h>

class TrailComponent : public Component
{
public:
	inline TrailComponent() { alpha = 1; }
	inline ~TrailComponent() {}

	inline void Update(float dt) override final { alpha -= 0.1f; parent->GetComponent<Sprite>()->SetColor(1, 1, 1, alpha); }
	inline bool isTransparent() { if (alpha <= 0) return true; return false; }

private:
	float alpha;
};

#endif TRAILCOMPONENT_H