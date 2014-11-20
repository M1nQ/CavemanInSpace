#include "Arrow.h"

void Arrow::Init()
{
	arrowPic = uthRS.LoadTexture("Placeholders/nuoli.png");
	this->AddComponent(new Sprite(arrowPic));
	this->transform.SetOrigin(6);
	this->SetActive(false);
}

void Arrow::update(float dt)
{
	if (this->IsActive() == true)
	{
		direction = start - uthInput.Common.Position();
		scale = direction.length;
		direction.normalize();
		this->transform.ScaleToSize(scale, 24);
		this->transform.SetRotation(pmath::atan2(direction.y, direction.x));
		this->transform.SetPosition(uthEngine.GetWindow().GetCamera().GetPosition() - (direction * 50));
	}
}

void Arrow::DrawArrow(Vec2 startPos)
{	
	start = startPos;
	this->SetActive(true);
}

void Arrow::DisableArrow()
{
	this->SetActive(false);
}


