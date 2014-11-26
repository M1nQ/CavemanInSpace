#ifndef PREFABOBJECT_H
#define PREFABOBJECT_H

#include <string>
#include <UtH/UtHEngine.hpp>
#include <pmath\Matrix2.hpp>

using namespace uth;
using namespace std;
using namespace pmath;

class PrefabObject
{
public:
	inline PrefabObject() { randomMaxSpeed = 3; }
	~PrefabObject() { }

	GameObject* CreateGameObject(PhysicsWorld* world, Vec2 position, string spritePath, string nameTag);
	// Creates an astronaut to the given position, heading towards the center of the screen.
	GameObject* CreateAstronaut(PhysicsWorld* world, Vec2 position, string tag = "Astronaut");
	// Creates an asteroid to the given position, heading towards the center of the screen.
	GameObject* CreateAsteroid(PhysicsWorld* world, Vec2 position, string tag = "Asteroid");
	// Creates a cosmonaut to the given position, heading towards the center of the screen.
	GameObject* CreateCosmonaut(PhysicsWorld* world, Vec2 position, string tag = "Cosmonaut");
	// TODO:
	GameObject* CreateTaikonaut(PhysicsWorld* world, Vec2 position, string tag = "Taikonaut");
	GameObject* CreateMeteorite(PhysicsWorld* world, Vec2 position, string tag = "Meteorite");
	GameObject* CreateSatellite(PhysicsWorld* world, Vec2 position, string tag = "Satellite");
	GameObject* CreateSpaceship(PhysicsWorld* world, Vec2 position, string tag = "Spaceship");
	GameObject* CreateUfo(PhysicsWorld* world, Vec2 position, string tag = "Ufo");

private:
	// Sets the object's direction towards the center of the screen, and randomizes a speed.
	void Direct(GameObject* p_object);

	// Maximum speed used for randomizing the speed of objects in Direct method.
	int randomMaxSpeed;
};

#endif