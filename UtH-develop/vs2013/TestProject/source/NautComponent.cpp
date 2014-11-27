#include <NautComponent.h>
#include <TrailComponent.h>

void NautComponent::Update(float dt)
{
	if (hp <= 0 && parent->GetComponent<Sprite>()->GetColor().a > 0)
	{
		// Substaracts from alpha: Alpha - precentage in seconds
		parent->GetComponent<Sprite>()->SetColor(1, 1, 1, (parent->GetComponent<Sprite>()->GetColor().a) - 1 / (1 / dt));
		parent->GetComponent<Rigidbody>()->SetKinematic(true);
	}

	lastPosition[1] = lastPosition[0];
	lastPosition[0] = parent->transform.GetPosition();
}
void NautComponent::Hit(Vec2 position)
{
	// Subtracts from hp and sets direction away from the given position.

	if (hp > 0)
	{
		Vec2 newDirection = parent->transform.GetPosition() - position;
		if (newDirection.length() > 0) newDirection.normalize();
		parent->GetComponent<Rigidbody>("Rigidbody")->SetVelocity(newDirection * 3);
		--hp;
	}
}
GameObject* NautComponent::addTrail()
{
	// Returns a gameObject pointing to the direction the naut is going.

	lastIndicatorPosition = parent->transform.GetPosition();
	GameObject* trailObject = new GameObject("Trail");
	trailObject->transform.SetPosition(lastIndicatorPosition);
	trailObject->transform.Rotate((lastPosition[0] - lastPosition[1]).angle());
	trailObject->AddComponent(new Sprite(uthRS.LoadTexture("Placeholders/Indicator.png")));
	trailObject->AddComponent(new TrailComponent());
	return trailObject;
}