#pragma once
//#include "RigidBodyComponent.hpp"
#include <unordered_map>
#include <utility>
//#include "Globals.hpp"



namespace ASSB
{
	//class GameEngine;
	class ObjectID;
	class PhysicsSystem
	{
	public:
		void Update(std::unordered_map<const ObjectID, int> &map);

	private:
		/*
		bool isCollidingAABB(GameEngine &g,
			std::pair<const Globals::ObjectID, RigidBodyComponent> &obj1,
			std::pair<const Globals::ObjectID, RigidBodyComponent> &obj2);

		void resolveStaticAABBCollision(GameEngine &g,
			std::pair<const Globals::ObjectID, RigidBodyComponent> &dynamicObj,
			std::pair<const Globals::ObjectID, RigidBodyComponent> &staticObj);

		void resolveDynamicDynamicAABBCollision(GameEngine &g,
			std::pair<const Globals::ObjectID, RigidBodyComponent> &dynamic1,
			std::pair<const Globals::ObjectID, RigidBodyComponent> &dynamic2);
			*/
	};
}
