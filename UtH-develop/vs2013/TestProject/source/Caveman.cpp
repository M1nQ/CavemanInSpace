#include "Caveman.h"

void Caveman::Init(PhysicsWorld *world)
{
	speed = 3;
	this->AddComponent(new Sprite("Placeholders/caveman.png"));
	this->transform.SetPosition(0, 0);
	this->AddComponent(new Rigidbody(*world, COLLIDER_BALL));
	this->GetComponent<Rigidbody>()->SetVelocity(pmath::Vec2(0, 0));
	this->AddTag("Caveman");
}

void Caveman::Hit()
{
	//animation not done!!!!!
}
void Caveman::ChangeDirectionMouse(pmath::Vec2 pullPosition)
{
	// Calculates the vector between touch position and caveman's position.
	pmath::Vec2 temp = (-1.f * pullPosition) + (uthEngine.GetWindow().GetSize() * 0.5f);
	temp.normalize();
	this->GetComponent<Rigidbody>()->SetVelocity(temp * speed);
}

// works if touch get position methods return screen (camera) coordinates
void Caveman::ChangeDirectionTouch(pmath::Vec2 startPosition, pmath::Vec2 endPosition)
{
	pmath::Vec2 temp = startPosition - endPosition;
	temp.normalize();
	this->GetComponent<Rigidbody>()->SetVelocity(temp * speed);
}

Caveman::Caveman()
{
}
Caveman::~Caveman()
{
}