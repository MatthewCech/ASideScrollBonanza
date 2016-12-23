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
		void Update(std::unordered_map<ASSB::Globals::ObjectID, std::unique_ptr<RigidBodyComponent>> &map, const GameTime &g);

	private:
		CollisionInfo isCollidingAABB(
			std::pair<const Globals::ObjectID, std::unique_ptr<RigidBodyComponent>> &obj1,
			std::pair<const Globals::ObjectID, std::unique_ptr<RigidBodyComponent>> &obj2);

		void resolveStaticAABBCollision(
			std::pair<const Globals::ObjectID, std::unique_ptr<RigidBodyComponent>> &dynamicObj,
			std::pair<const Globals::ObjectID, std::unique_ptr<RigidBodyComponent>> &staticObj,
			CollisionInfo info);

		void resolveDynamicDynamicAABBCollision(
			std::pair<const Globals::ObjectID, std::unique_ptr<RigidBodyComponent>> &dynamic1,
			std::pair<const Globals::ObjectID, std::unique_ptr<RigidBodyComponent>> &dynamic2,
			CollisionInfo info);
	};
}
