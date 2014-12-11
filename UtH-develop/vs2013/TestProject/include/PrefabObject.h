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

	// Creates a gameObject of specified type to given position with a randomized angle.
	GameObject* CreateGameObject(PhysicsWorld* world, Vec2 position, string spritePath, string nameTag);

private:
	// Sets the object's direction towards the center of the screen, and randomizes a speed.
	void Direct(GameObject* p_object);

	// Maximum speed used for randomizing the speed of objects in Direct method.
	int randomMaxSpeed;
};

#endif