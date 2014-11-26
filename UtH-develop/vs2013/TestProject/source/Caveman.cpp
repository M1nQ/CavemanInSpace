#include "Caveman.h"

void Caveman::Init(PhysicsWorld *world)
{
	speed = 4;
	this->AddComponent(new Sprite("Placeholders/caveman.png"));
	this->transform.SetPosition(0, 0);
	this->AddComponent(new Rigidbody(*world, COLLIDER_BALL));
	cavemanColl = this->GetComponent<Rigidbody>();
	cavemanColl->SetVelocity(pmath::Vec2(0, 0));
	cavemanColl->SetPhysicsGroup(-1);
	this->AddTag("Caveman");
	
}


void Caveman::Hit()
{
	//animation not done!!!!!
}
void Caveman::ChangeDirectionMouse(pmath::Vec2 arrowDirection, bool strongpull)
{
	// Calculates the vector between touch position and caveman's position.
	//pmath::Vec2 temp = (-1.f * pullPosition) + (uthEngine.GetWindow().GetSize() * 0.5f);
	//temp.normalize();
	if (strongpull)
		speed = 5;
	else
		speed = 3;

	cavemanColl->SetVelocity(arrowDirection * speed);
}

// works if touch getPosition methods return screen (camera) coordinates
void Caveman::ChangeDirectionTouch(pmath::Vec2 startPosition, pmath::Vec2 endPosition)
{
	pmath::Vec2 temp = cavemanColl->GetPosition() - endPosition;
	speed = temp.length() * 0.05f; // if resolution problems, calc as percentage of screen size
	temp.normalize();
	cavemanColl->SetVelocity(temp * speed);
}

Caveman::Caveman()
{
}
Caveman::~Caveman()
{
}