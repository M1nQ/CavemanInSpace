#include "PrefabObject.h"

// Public //

GameObject* PrefabObject::CreateAstronaut(PhysicsWorld world, pmath::Vec2 position, string tag)
{
	GameObject* astronaut = new GameObject(tag);
	astronaut->AddComponent(new Sprite(""));
	astronaut->AddComponent(new Rigidbody(world));
	astronaut->GetComponent<Rigidbody>("Rigidbody")->SetPosition(position);

	Direct(astronaut);
	return astronaut;
}
GameObject* PrefabObject::CreateAsteroid(PhysicsWorld world, pmath::Vec2 position, string tag)
{
	GameObject* asteroid = new GameObject(tag);
	asteroid->AddComponent(new Sprite(""));
	return asteroid;
}
// TODO: Implement functions defined below.
GameObject* PrefabObject::CreateCosmonaut(PhysicsWorld world, pmath::Vec2 position, string tag) { return nullptr; }
GameObject* PrefabObject::CreateTaikonaut(PhysicsWorld world, pmath::Vec2 position, string tag) { return nullptr; }
GameObject* PrefabObject::CreateMeteorite(PhysicsWorld world, pmath::Vec2 position, string tag) { return nullptr; }
GameObject* PrefabObject::CreateSatellite(PhysicsWorld world, pmath::Vec2 position, string tag) { return nullptr; }
GameObject* PrefabObject::CreateSpaceship(PhysicsWorld world, pmath::Vec2 position, string tag) { return nullptr; }
GameObject* PrefabObject::CreateUfo(PhysicsWorld world, pmath::Vec2 position, string tag) { return nullptr; }

// Private //

void PrefabObject::Direct(const GameObject* object)
{
	// TODO:
	// Calculate a direction for the object and assign it's velocity.
	// Note: Use vector from object's position to middle of the screen.
}