#pragma once
#include "Components\RigidBodyComponent.hpp"
#include <unordered_map>
#include <utility>
#include "Globals.hpp"
#include "CollisionInfo.hpp"
#include "GameEngine/GameTime.h"



namespace ASSB
{
	class PhysicsSystem
	{
	public:
		void Update(std::unordered_map<ASSB::Globals::ObjectID, RigidBodyComponent> &map, const GameTime &g);

	private:
		CollisionInfo isCollidingAABB(
			std::pair<const Globals::ObjectID, RigidBodyComponent> &obj1,
			std::pair<const Globals::ObjectID, RigidBodyComponent> &obj2);

		void resolveStaticAABBCollision(
			std::pair<const Globals::ObjectID, RigidBodyComponent> &dynamicObj,
			std::pair<const Globals::ObjectID, RigidBodyComponent> &staticObj,
			CollisionInfo info);

		void resolveDynamicDynamicAABBCollision(
			std::pair<const Globals::ObjectID, RigidBodyComponent> &dynamic1,
			std::pair<const Globals::ObjectID, RigidBodyComponent> &dynamic2,
			CollisionInfo info);
	};
}
