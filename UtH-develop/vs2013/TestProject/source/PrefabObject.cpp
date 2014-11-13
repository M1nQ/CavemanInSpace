#include "PrefabObject.h"

GameObject* PrefabObject::CreateAstronaut(PhysicsWorld* world, Vec2 position, string tag)
{
	// Creates an astronaut to the given position, heading towards the center of the screen
	// with a sligthly randomized angle.

	GameObject* p_astronaut = new GameObject(tag);
	p_astronaut->AddComponent(new Sprite("Placeholders/astronautPlaceHolder.png"));
	p_astronaut->AddComponent(new Rigidbody(*world, COLLIDER_BALL));
	p_astronaut->GetComponent<Rigidbody>("Rigidbody")->SetPosition(position);
	Direct(p_astronaut);
	return p_astronaut;
}
GameObject* PrefabObject::CreateAsteroid(PhysicsWorld* world, Vec2 position, string tag)
{
	// Creates an asteroid to the given position, heading towards the center of the screen
	// with a sligthly randomized angle.

	GameObject* p_asteroid = new GameObject(tag);
	p_asteroid->AddComponent(new Sprite("Placeholders/Asteroid_3.png"));
	p_asteroid->AddComponent(new Rigidbody(*world, COLLIDER_BALL));
	p_asteroid->GetComponent<Rigidbody>("Rigidbody")->SetPosition(position);
	Direct(p_asteroid);
	return p_asteroid;
}
GameObject* PrefabObject::CreateCosmonaut(PhysicsWorld* world, Vec2 position, string tag) 
{ 
	// Creates a cosmonaut to the given position, heading towards the center of the screen
	// with a sligthly randomized angle.

	GameObject* p_cosmonaut = new GameObject(tag);
	p_cosmonaut->AddComponent(new Sprite("Placeholders/Cosmonaut.png"));
	p_cosmonaut->AddComponent(new Rigidbody(*world, COLLIDER_BALL));
	p_cosmonaut->GetComponent<Rigidbody>("Rigidbody")->SetPosition(position);
	Direct(p_cosmonaut);
	return p_cosmonaut;
}
// TODO: Implement functions defined below.
GameObject* PrefabObject::CreateTaikonaut(PhysicsWorld* world, Vec2 position, string tag) { return nullptr; }
GameObject* PrefabObject::CreateMeteorite(PhysicsWorld* world, Vec2 position, string tag) { return nullptr; }
GameObject* PrefabObject::CreateSatellite(PhysicsWorld* world, Vec2 position, string tag) { return nullptr; }
GameObject* PrefabObject::CreateSpaceship(PhysicsWorld* world, Vec2 position, string tag) { return nullptr; }
GameObject* PrefabObject::CreateUfo(PhysicsWorld* world, Vec2 position, string tag) { return nullptr; }

void PrefabObject::Direct(GameObject* p_object)
{
	// Sets the object's direction towards the center of the screen, 
	// and randomizes a speed using the randomMaxSpeed.

	Vec2 direction = uthEngine.GetWindow().GetCamera().GetPosition() - p_object->GetComponent<Rigidbody>("Rigidbody")->GetPosition();
	direction.normalize();

	if (direction.x > 0)
		direction.x += Randomizer::GetFloat(0.f, 10 - direction.x);
	else
		direction.x -= Randomizer::GetFloat(0.f, 10 + direction.x);

	if (direction.y > 0)
		direction.y += Randomizer::GetFloat(0.f, 10 - direction.y);
	else
		direction.y -= Randomizer::GetFloat(0.f, 10 + direction.x);

	direction.normalize();

	if (direction.x != 0 && direction.y != 0)
		p_object->GetComponent<Rigidbody>("Rigidbody")->SetVelocity(direction * Randomizer::GetFloat(0, randomMaxSpeed));
}