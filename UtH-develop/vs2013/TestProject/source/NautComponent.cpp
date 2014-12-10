#include <NautComponent.h>

void NautComponent::Update(float dt)
{
	if (hp <= 0 && parent->GetComponent<Sprite>()->GetColor().a > 0)
	{
		// Substaracts from alpha: Alpha - precentage in seconds
		parent->GetComponent<Sprite>()->SetColor(1, 1, 1, (parent->GetComponent<Sprite>()->GetColor().a) - 1 / (1 / dt));
		parent->GetComponent<Rigidbody>()->SetKinematic(true);
	}
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
	//if (hp <= 0)
	//{
	//	parent->GetComponent<Rigidbody>("Rigidbody")->SetKinematic(true);
	//}
}