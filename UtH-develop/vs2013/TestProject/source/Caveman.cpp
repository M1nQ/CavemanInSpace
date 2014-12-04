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
	rotate = false;
}


void Caveman::Hit(const Vec2& hitPoint)
{
	//animation not done!!!!!

	if (hitPoint.length() != 0)
	{
		rotate = true;
		targetRotation = atan2(hitPoint.x - transform.GetPosition().x, (hitPoint.y - transform.GetPosition().y) * -1);
		targetRotation *= 180 / pi;
		targetRotation += -90;
	}
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
	speed = 5; // if resolution problems, calc as percentage of screen size
	temp.normalize();
	cavemanColl->SetVelocity(temp * speed);
}

void Caveman::update(float dt)
{
	if (rotate)
	{
		static float rotation = 0;
		rotation = (int)transform.GetRotation() % 360;

		if (rotation > 180) rotation -= 360;
		else if (rotation < -180) rotation += 360;

		if (abs(rotation - targetRotation) < 2.f)
		{
			rotate = false;

			if (rotation < targetRotation)
				GetComponent<Rigidbody>("Rigidbody")->Rotate((targetRotation - rotation) * 0.1f);
			else
				GetComponent<Rigidbody>("Rigidbody")->Rotate((rotation - targetRotation) * 0.1f);
		}
		else if (rotation < targetRotation)
		{
			GetComponent<Rigidbody>("Rigidbody")->Rotate((targetRotation - rotation) * 0.1f);
		}
		else
		{
			GetComponent<Rigidbody>("Rigidbody")->Rotate((rotation - targetRotation) * 0.1f);
		}
	}
}

Caveman::Caveman()
{
}
Caveman::~Caveman()
{
}