#include <Club.h>

Club::Club(Vec2 clubSize)
	: hitDelay(0),
	timeFromHit(0),
	hitDirection()
{
	size = Vec2(clubSize.x, 1);
	reach = 1.f * clubSize.x;
}
Club::~Club()
{}

void Club::Init(PhysicsWorld *world)
{
	this->transform.ScaleToSize(size);
	this->AddComponent(new Rigidbody(*world, COLLIDER_BALL, size));
	this->AddTag("Club");
	clubColl = this->GetComponent<Rigidbody>();
	clubColl->SetPhysicsGroup(-1);
	clubColl->SetActive(false);
}

void Club::update(float dt, Vec2 cavemanPos)
{
	hitDelay -= dt;

	if (hitDelay <= 0)
	{
		clubColl->SetActive(true);

		if (timeFromHit > 0)
		{
			clubColl->SetPosition(cavemanPos + (hitDirection * reach));
			timeFromHit -= dt;
		}
		else if (timeFromHit <= 0)
		{
			timeFromHit = 0;
			clubColl->SetPosition(cavemanPos);
			if (clubColl->IsActive())
				clubColl->SetActive(false);
			//
		}
		else
			clubColl->SetPosition(cavemanPos);
	}
}

void Club::Hit(Vec2 cavemanPosition, Vec2 tapPosition)
{
	Vec2 temp = tapPosition - cavemanPosition;
	temp.normalize();
	hitDirection = temp;
	hitDelay = 1.f;
	timeFromHit = 0.5f;
}

void Club::HasHit()
{
	timeFromHit = 0;
}
bool Club::isHitting()
{
	if (hitDelay > 0)
		return true;
	return false;
}