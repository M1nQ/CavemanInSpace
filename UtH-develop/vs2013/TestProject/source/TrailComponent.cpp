#include "TrailComponent.h"

void TrailComponent::Update(float dt)
{
	alpha -= 0.001f;
	parent->GetComponent<Sprite>()->SetColor(1, 1, 1, alpha);
}