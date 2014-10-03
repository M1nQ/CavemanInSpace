#include "Caveman.h"

void Caveman::Init(PhysicsWorld *world)
{
	speed = 3;
	this->AddComponent(new Sprite("caveman.png"));
	this->transform.SetPosition(0, 0);
	this->AddComponent(new Rigidbody(*world, COLLIDER_BALL));
	this->GetComponent<Rigidbody>()->SetVelocity(pmath::Vec2(0, 0));
}

void Caveman::Hit()
{
	//animation


}
void Caveman::ChangeDirection(pmath::Vec2 pullPosition)
{
	pmath::Vec2 temp = this->transform.GetPosition() - pullPosition;
	temp.normalize();
	this->GetComponent<Rigidbody>()->SetVelocity(temp * speed);
}


Caveman::Caveman()
{
}
Caveman::~Caveman()
{
}