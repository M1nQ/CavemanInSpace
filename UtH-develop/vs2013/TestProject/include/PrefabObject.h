#ifndef PREFABOBJECT_H
#define PREFABOBJECT_H

#include <string>
#include <UtH/UtHEngine.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/Physics/Rigidbody.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>

using namespace uth;
using namespace std;
using namespace pmath;

class PrefabObject
{
public:
	PrefabObject() { }
	~PrefabObject() { }

	GameObject* CreateAstronaut(PhysicsWorld* world, Vec2 position, string tag = "Astronaut");
	GameObject* CreateAsteroid(PhysicsWorld* world, Vec2 position, string tag = "Asteroid");
	// TODO:
	GameObject* CreateCosmonaut(PhysicsWorld* world, Vec2 position, string tag = "Cosmonaut");
	GameObject* CreateTaikonaut(PhysicsWorld* world, Vec2 position, string tag = "Taikonaut");
	GameObject* CreateMeteorite(PhysicsWorld* world, Vec2 position, string tag = "Meteorite");
	GameObject* CreateSatellite(PhysicsWorld* world, Vec2 position, string tag = "Satellite");
	GameObject* CreateSpaceship(PhysicsWorld* world, Vec2 position, string tag = "Spaceship");
	GameObject* CreateUfo(PhysicsWorld* world, Vec2 position, string tag = "Ufo");

private:
	// Sets the objects direction towards the center of the screen, and randomizes a speed.
	void Direct(GameObject* p_object);
};

#endif