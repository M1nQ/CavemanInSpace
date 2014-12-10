#include "Caveman.h"

void Caveman::Init(PhysicsWorld *world)
{
	speed = 4;
	this->AddComponent(new AnimatedSprite(uthRS.LoadTexture("Placeholders/caveman_animation_attack2.png"), 5, Vec2(150,154), 5,0U,false,false));
	//this->transform.ScaleToSize(this->transform.GetSize() / 7);
	this->transform.SetPosition(0, 0);
	this->AddComponent(new Rigidbody(*world, COLLIDER_BALL));
	cavemanColl = this->GetComponent<Rigidbody>();
	cavemanColl->SetVelocity(pmath::Vec2(0, 0));
	cavemanColl->SetPhysicsGroup(-1);
	this->AddTag("Caveman");
	this->GetComponent<AnimatedSprite>()->ChangeAnimation(0, 1);
	rotate = false;
}


void Caveman::Hit(const Vec2& hitPoint)
{
	//animation not done!!!!!
	this->GetComponent<AnimatedSprite>()->ChangeAnimation(0, 5, 0,10);
	animTime = 0.5f;
	// Sets the caveman to turn towards the click
	if (hitPoint.length() != 0)
	{
		rotate = true;
		targetRotation = atan2(hitPoint.x - transform.GetPosition().x, (hitPoint.y - transform.GetPosition().y) * -1);
		targetRotation *= 180 / pi;
		targetRotation -= 90;
		GetComponent<Rigidbody>("Rigidbody")->SetAngularVelocity(0);

		if (targetRotation > 180) targetRotation -= 360;
		else if (targetRotation < -180) targetRotation += 360;

		if (abs(targetRotation - transform.GetRotation()) > 180)
		{
			if (transform.GetRotation() > 0)
				rotatePositive = true;
			else
				rotatePositive = false;
		}
		else
		{
			if (targetRotation > transform.GetRotation())
				rotatePositive = true;
			else
				rotatePositive = false;
		}
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
	if (animTime > 0) animTime -= dt;
	else this->GetComponent<AnimatedSprite>()->ChangeAnimation(0, 1);

	// Turns the caveman gradually towards the hit position.

	if (transform.GetRotation() > 180)
		GetComponent<Rigidbody>("Rigidbody")->SetAngle(transform.GetRotation() - 360);
	if (transform.GetRotation() < -180)
		GetComponent<Rigidbody>("Rigidbody")->SetAngle(transform.GetRotation() + 360);

	if (rotate)
	{
		if (abs(targetRotation - transform.GetRotation()) < 4)
		{
			rotate = false;

			if (rotatePositive) GetComponent<Rigidbody>("Rigidbody")->SetAngularVelocity(-0.2f);
			else GetComponent<Rigidbody>("Rigidbody")->SetAngularVelocity(0.2f);
		}
		else
		{
			if (abs(targetRotation - transform.GetRotation()) < 180)
			{
				if (rotatePositive)
					GetComponent<Rigidbody>("Rigidbody")->Rotate(abs(targetRotation - transform.GetRotation()) * 0.07f);
				else
					GetComponent<Rigidbody>("Rigidbody")->Rotate(abs(targetRotation - transform.GetRotation()) * -0.07f);
			}
			else
			{
				if (rotatePositive)
					GetComponent<Rigidbody>("Rigidbody")->Rotate((360 - abs(targetRotation - transform.GetRotation())) * 0.07f);
				else
					GetComponent<Rigidbody>("Rigidbody")->Rotate((360 - abs(targetRotation - transform.GetRotation())) * -0.07f);
			}
		}
	}
}

Caveman::Caveman()
{
}
Caveman::~Caveman()
{
}