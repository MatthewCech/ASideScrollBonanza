#pragma once
#include "Components\RigidBodyComponent.hpp"
#include <unordered_map>
#include <utility>
#include "Globals.hpp"
#include "CollisionInfo.hpp"
#include "GameEngine/GameTime.h"
#include "EventSystem/ObjectEventManager.hpp"


namespace ASSB
{
	class PauseToggleEvent;
	class PhysicsSystem : public EventSystem::ObjectEventManager
	{
	public:
		PhysicsSystem();
		void Update(std::unordered_map<ASSB::Globals::ObjectID, std::unique_ptr<RigidBodyComponent>> &map, const GameTime &g);

	private:
		bool enabled_;
		void pausedUpdate(PauseToggleEvent *e);

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

		// Omit
		PhysicsSystem(const PhysicsSystem &rhs) = delete;
		PhysicsSystem &operator=(const PhysicsSystem &rhs) = delete;

	};
}
