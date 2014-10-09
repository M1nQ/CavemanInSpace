#include "PrefabObject.h"

GameObject* PrefabObject::CreateAstronaut(PhysicsWorld* world, Vec2 position, string tag)
{
	GameObject* p_astronaut = new GameObject(tag);
	p_astronaut->AddComponent(new Sprite("Placeholders/astronautPlaceHolder.png"));
	p_astronaut->AddComponent(new Rigidbody(*world, COLLIDER_BALL));
	p_astronaut->GetComponent<Rigidbody>("Rigidbody")->SetPosition(position);
	Direct(p_astronaut);
	return p_astronaut;
}
GameObject* PrefabObject::CreateAsteroid(PhysicsWorld world, Vec2 position, string tag)
{
	GameObject* p_asteroid = new GameObject(tag);
	p_asteroid->AddComponent(new Sprite(""));
	return p_asteroid;
}
// TODO: Implement functions defined below.
GameObject* PrefabObject::CreateCosmonaut(PhysicsWorld world, Vec2 position, string tag) { return nullptr; }
GameObject* PrefabObject::CreateTaikonaut(PhysicsWorld world, Vec2 position, string tag) { return nullptr; }
GameObject* PrefabObject::CreateMeteorite(PhysicsWorld world, Vec2 position, string tag) { return nullptr; }
GameObject* PrefabObject::CreateSatellite(PhysicsWorld world, Vec2 position, string tag) { return nullptr; }
GameObject* PrefabObject::CreateSpaceship(PhysicsWorld world, Vec2 position, string tag) { return nullptr; }
GameObject* PrefabObject::CreateUfo(PhysicsWorld world, Vec2 position, string tag) { return nullptr; }

void PrefabObject::Direct(GameObject* p_object)
{
	Vec2 direction = uthEngine.GetWindow().GetCamera().GetPosition() - p_object->GetComponent<Rigidbody>("Rigidbody")->GetPosition();
	direction.normalize();
	
	if (direction.x > 0)
		direction.x + Randomizer::GetFloat(0.f, 1 - direction.x);
	else
		direction.x - Randomizer::GetFloat(0.f, 1 + direction.x);

	if (direction.y > 0)
		direction.y + Randomizer::GetFloat(0.f, 1 - direction.y);
	else
		direction.y - Randomizer::GetFloat(0.f, 1 + direction.x);

	direction.normalize();
	p_object->GetComponent<Rigidbody>("Rigidbody")->SetVelocity(direction * Randomizer::GetFloat(0, 3));
}