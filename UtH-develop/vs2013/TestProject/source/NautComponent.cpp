#include <NautComponent.h>

void NautComponent::Update(float dt)
{
	// Makes dead nauts fade away.

	if (hp <= 0 && parent->GetComponent<Sprite>()->GetColor().a > 0)
		parent->GetComponent<Sprite>()->SetColor(1, 1, 1, (parent->GetComponent<Sprite>()->GetColor().a) - 0.01 * (1 / dt));
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