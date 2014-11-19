#include <Club.h>

Club::Club(Vec2 clubSize)
{
	size = clubSize;
	reach = 1.5f * clubSize.x;
}
Club::~Club()
{}

void Club::Init(PhysicsWorld *world)
{
	//this->AddComponent(new Sprite("Placeholders/clubHolder.png"));
	//this->transform.SetPosition(cavemanColl->GetPosition());
	this->transform.ScaleToSize(size);
	this->AddComponent(new Rigidbody(*world, COLLIDER_BALL, size));
	this->AddTag("Club");
	clubColl = this->GetComponent<Rigidbody>();

	clubColl->SetActive(false);
}

void Club::update(float dt)
{
	Vec2 campos = uthEngine.GetWindow().GetCamera().GetPosition();
	if (timeFromHit > 0)
	{
		clubColl->SetPosition(campos + (hitDirection * reach));
		timeFromHit -= dt;
	}
	else if (timeFromHit <= 0)
	{
		timeFromHit = 0;
		clubColl->SetPosition(campos);
		if (clubColl->IsActive())
			clubColl->SetActive(false);
		//
	}
	else
		clubColl->SetPosition(campos);
}

void Club::Hit(Vec2 cavemanPosition, Vec2 tapPosition)
{
	Vec2 temp = tapPosition - cavemanPosition;
	temp.normalize();
	hitDirection = temp;
	timeFromHit = 5;
	clubColl->SetActive(true);
}