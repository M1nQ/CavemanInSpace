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
void Caveman::ChangeDirection(pmath::Vec2 pullPosition)
{
	// Calculates the vector between touch position and caveman's position.
	// caveman - (touch + camera + (caveman - camera)) + (windowSize / 2)
	pmath::Vec2 temp = 
						 this->GetComponent<Rigidbody>()->GetPosition() - 
														  (pullPosition + 
						uthEngine.GetWindow().GetCamera().GetPosition() +
						(this->GetComponent<Rigidbody>()->GetPosition() - 
					  uthEngine.GetWindow().GetCamera().GetPosition())) +
									   (uthEngine.GetWindow().GetSize() /
																	 2);
	temp.normalize();
	this->GetComponent<Rigidbody>()->SetVelocity(temp * speed);
}


Caveman::Caveman()
{
}
Caveman::~Caveman()
{
}

/*
pmath::Vec2 temp =
					this->GetComponent<Rigidbody>()->GetPosition() - (
													  pullPosition +
				   uthEngine.GetWindow().GetCamera().GetPosition() + (
					this->GetComponent<Rigidbody>()->GetPosition() -
				   uthEngine.GetWindow().GetCamera().GetPosition() )) + (
								   uthEngine.GetWindow().GetSize() /
																 2 );
*/