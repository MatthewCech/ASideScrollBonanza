#pragma once
#include "Components\RigidBodyComponent.hpp"
#include <unordered_map>
#include <utility>
#include "Globals.hpp"
#include "CollisionInfo.hpp"



namespace ASSB
{
	class GameEngine;
	class PhysicsSystem
	{
	public:
		void Update(GameEngine &g, std::unordered_map<ASSB::Globals::ObjectID, RigidBodyComponent> &map);

	private:
		CollisionInfo isCollidingAABB(GameEngine &g,
			std::pair<const Globals::ObjectID, RigidBodyComponent> &obj1,
			std::pair<const Globals::ObjectID, RigidBodyComponent> &obj2);

		void resolveStaticAABBCollision(GameEngine &g,
			std::pair<const Globals::ObjectID, RigidBodyComponent> &dynamicObj,
			std::pair<const Globals::ObjectID, RigidBodyComponent> &staticObj,
			CollisionInfo info);

		void resolveDynamicDynamicAABBCollision(GameEngine &g,
			std::pair<const Globals::ObjectID, RigidBodyComponent> &dynamic1,
			std::pair<const Globals::ObjectID, RigidBodyComponent> &dynamic2,
			CollisionInfo info);
	};
}
