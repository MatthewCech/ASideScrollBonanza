#include "PhysicsSystem.hpp"
#include "Globals.hpp"
#include "GameEngine\GameEngine.h"


namespace ASSB
{
	void PhysicsSystem::Update(GameEngine &g,
		std::unordered_map<ASSB::Globals::ObjectID, RigidBodyComponent> &map)
	{
		UNUSED(g);
		UNUSED(map);

		//!TODO:Convert to not using full N^2 items in map!
		for (auto &pair1 : map)
		{
			// If we are not collidable, don't bother for the entier loop.
			if (!pair1.second.collidable_)
				continue;

			for (auto &pair2 : map)
			{
				// If we're not collidable, don't bother.
				if (!pair2.second.collidable_)
					continue;

				// If we are both static, don't bother.
				if (pair1.second.static_)
					if (pair2.second.static_)
						continue;
				
				// If one of us is not static, care a bit only if we are colliding.
				if (isCollidingAABB(g, pair1, pair2))
				{
					if (!pair1.second.static_)
					{
						// both dymanic
						if (!pair2.second.static_)
							resolveDynamicDynamicAABBCollision(g, pair1, pair2);
						// pair1 is dynamic
						else
							resolveStaticAABBCollision(g, pair1, pair2);
					}
					else
						// pair2 is dynamic
						resolveStaticAABBCollision(g, pair2, pair1);
				}
			}
		}

	}

	// Check if two objects are colliding
	bool PhysicsSystem::isCollidingAABB(GameEngine &g,
		std::pair<const Globals::ObjectID, RigidBodyComponent> &obj1,
		std::pair<const Globals::ObjectID, RigidBodyComponent> &obj2)
	{
		ComponentHandle<TransformComponent> o1t = g.GetComponent<TransformComponent>(obj1.first);
		ComponentHandle<TransformComponent> o2t = g.GetComponent<TransformComponent>(obj1.first);
		UNUSED(obj1);
		UNUSED(obj2);
		UNUSED(g);

		return false;
		//if(o1t->GetPosition().X)
	}

	// Misleading qualifiers, not actually const for the Game Objects.
	void PhysicsSystem::resolveStaticAABBCollision(GameEngine &g,
		std::pair<const Globals::ObjectID, RigidBodyComponent> &dynamicObj,
		std::pair<const Globals::ObjectID, RigidBodyComponent> &staticObj)
	{
		UNUSED(g);
		UNUSED(dynamicObj);
		UNUSED(staticObj);
	}

	// Misleading qualifiers, not actually const for the Game Objects
	void PhysicsSystem::resolveDynamicDynamicAABBCollision(GameEngine &g,
		std::pair<const Globals::ObjectID, RigidBodyComponent> &dynamicObj1,
		std::pair<const Globals::ObjectID, RigidBodyComponent> &dynamicObj2)
	{
		UNUSED(g);
		UNUSED(dynamicObj1);
		UNUSED(dynamicObj2);
	}
}
