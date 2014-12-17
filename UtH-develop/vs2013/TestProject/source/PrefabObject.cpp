#include <PrefabObject.h>
#include <NautComponent.h>

GameObject* PrefabObject::CreateGameObject(PhysicsWorld* world, Vec2 position, string spritePath, string nameTag)
{
	// Creates a gameObject of specified type to given position with a randomized angle.

	GameObject* p_object = new GameObject(nameTag);
	p_object->transform.SetPosition(position);

	if (nameTag == "Astronaut")
	{
		p_object->AddComponent(new NautComponent());
		p_object->AddComponent(new AnimatedSprite(uthRS.LoadTexture(spritePath), 22, Vec2(100, 100), 5.f, 12));
		p_object->GetComponent<AnimatedSprite>()->ChangeAnimation(12, 10, 12, 5, true, false);
	}
	else if (nameTag == "Cosmonaut")
	{
		p_object->AddComponent(new NautComponent("NautComponent", 0.4f, 2));
		p_object->AddComponent(new Sprite(uthRS.LoadTexture(spritePath)));
	}

	p_object->AddComponent(new Rigidbody(*world, COLLIDER_BALL));

	if (nameTag.find("naut") != string::npos)
		p_object->AddTag("Naut");

	Direct(p_object);
	return p_object;
}

void PrefabObject::Direct(GameObject* p_object)
{
	// Sets the object's direction at most 90 degrees away from the center of the sceen,
	// and randomizes a speed using the randomMaxSpeed.

	Vec2 direction = uthEngine.GetWindow().GetCamera().GetPosition() - p_object->GetComponent<Rigidbody>("Rigidbody")->GetPosition();
	direction.normalize();
	float randomNumber = Randomizer::GetInt(0, 90) * 180 / pi;

	if (Randomizer::GetInt(0, 1) == 0)
	{
		Matrix2<float> rotation = Matrix2<float>(cos(randomNumber), -sin(randomNumber),
												 sin(randomNumber), cos(randomNumber));
		direction *= rotation;
	}
	else
	{
		Matrix2<float> rotation = Matrix2<float>(cos(randomNumber), sin(randomNumber),
												 -sin(randomNumber), cos(randomNumber));
		direction *= rotation;
	}

	p_object->GetComponent<Rigidbody>("Rigidbody")->SetVelocity(direction * Randomizer::GetFloat(0, randomMaxSpeed));
}