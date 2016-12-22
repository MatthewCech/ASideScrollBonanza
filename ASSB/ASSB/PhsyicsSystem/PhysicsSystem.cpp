#include "PhysicsSystem.hpp"
#include "Globals.hpp"
#include "GameEngine\GameEngine.h"


namespace ASSB
{
	void PhysicsSystem::Update(GameEngine &g,
		std::unordered_map<ASSB::Globals::ObjectID, RigidBodyComponent> &map)
	{
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
						if (!pair2.second.static_)
							// Both pairs are dymanic
							resolveDynamicDynamicAABBCollision(g, pair1, pair2);
						else
							// Pair1 is dynamic
							resolveStaticAABBCollision(g, pair1, pair2);
					}
					else
						// Pair2 is dynamic
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
		const Graphics::Vector4 pos1{ o1t->GetPosition() };
		const Graphics::Vector4 pos2{ o2t->GetPosition() };
		const float Half_Obj1Width{ obj1.second.width_ / 2 };
		const float Half_Obj1Height{ obj1.second.height_ / 2 };
		const float Half_Obj2Width{ obj2.second.width_ / 2 };
		const float Half_Obj2Height{ obj2.second.height_ / 2 };

		// Case: Right side object 1 past left side object 2
		if (pos1.X + Half_Obj1Width > pos2.X - Half_Obj2Width)
		{
			// Case: Right side object 2 is past left side object 1
			if (pos2.X + Half_Obj1Width > pos1.X - Half_Obj1Width)
			{
				// Case: Bottom side object 1 is past top side object 2
				if (pos1.Y + Half_Obj1Height > pos2.Y - Half_Obj2Height)
				{
					// Case: Bottom side object 2 is past top side object 1
					if (pos2.Y + Half_Obj2Height > pos1.Y - Half_Obj1Height)
					{
						// Colliding
						return true;
					}
				}
			}
		}

		return false;
	}


	// Misleading qualifiers, not actually const for the Game Objects.
	void PhysicsSystem::resolveStaticAABBCollision(GameEngine &g,
		std::pair<const Globals::ObjectID, RigidBodyComponent> &dynamicObj,
		std::pair<const Globals::ObjectID, RigidBodyComponent> &staticObj)
	{
		// Consider: Impulse?
		DEBUG_PRINT("Dynamic to Static Collision!");
		UNUSED(g);
		UNUSED(dynamicObj);
		UNUSED(staticObj);
	}


	// Misleading qualifiers, not actually const for the Game Objects
	void PhysicsSystem::resolveDynamicDynamicAABBCollision(GameEngine &g,
		std::pair<const Globals::ObjectID, RigidBodyComponent> &dynamicObj1,
		std::pair<const Globals::ObjectID, RigidBodyComponent> &dynamicObj2)
	{
		// Consider: Impulse?
		DEBUG_PRINT("Dynamic to Dynamic Collision!");
		UNUSED(g);
		UNUSED(dynamicObj1);
		UNUSED(dynamicObj2);
	}
}
