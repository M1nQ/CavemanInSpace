#include <PrefabObject.h>
#include <NautComponent.h>

GameObject* PrefabObject::CreateAstronaut(PhysicsWorld* world, Vec2 position, string tag)
{
	// Creates an astronaut to the given position, heading towards the center of the screen
	// with a sligthly randomized angle.

	GameObject* p_astronaut = new GameObject(tag);
	p_astronaut->transform.SetPosition(position);
	p_astronaut->AddComponent(new Sprite("Placeholders/astronautPlaceHolder.png"));
	p_astronaut->AddComponent(new Rigidbody(*world, COLLIDER_BALL));
	p_astronaut->AddComponent(new NautComponent());
	p_astronaut->AddTag("Naut");
	Direct(p_astronaut);
	return p_astronaut;
}
GameObject* PrefabObject::CreateCosmonaut(PhysicsWorld* world, Vec2 position, string tag)
{
	// Creates a cosmonaut to the given position, heading towards the center of the screen
	// with a sligthly randomized angle.

	GameObject* p_cosmonaut = new GameObject(tag);
	p_cosmonaut->transform.SetPosition(position);
	p_cosmonaut->AddComponent(new Sprite("Placeholders/Cosmonaut.png"));
	p_cosmonaut->AddComponent(new Rigidbody(*world, COLLIDER_BALL));
	p_cosmonaut->AddComponent(new NautComponent("NautComponent", 0.4f, 2));
	p_cosmonaut->AddTag("Naut");
	Direct(p_cosmonaut);
	return p_cosmonaut;
}
GameObject* PrefabObject::CreateAsteroid(PhysicsWorld* world, Vec2 position, string tag)
{
	// Creates an asteroid to the given position, heading towards the center of the screen
	// with a sligthly randomized angle.

	GameObject* p_asteroid = new GameObject(tag);
	p_asteroid->transform.SetPosition(position);
	p_asteroid->AddComponent(new Sprite("Placeholders/Asteroid_3.png"));
	p_asteroid->AddComponent(new Rigidbody(*world, COLLIDER_BALL));
	Direct(p_asteroid);
	return p_asteroid;
}
// TODO: Implement functions defined below.
GameObject* PrefabObject::CreateTaikonaut(PhysicsWorld* world, Vec2 position, string tag) { return nullptr; }
GameObject* PrefabObject::CreateMeteorite(PhysicsWorld* world, Vec2 position, string tag) { return nullptr; }
GameObject* PrefabObject::CreateSatellite(PhysicsWorld* world, Vec2 position, string tag) { return nullptr; }
GameObject* PrefabObject::CreateSpaceship(PhysicsWorld* world, Vec2 position, string tag) { return nullptr; }
GameObject* PrefabObject::CreateUfo(PhysicsWorld* world, Vec2 position, string tag) { return nullptr; }

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