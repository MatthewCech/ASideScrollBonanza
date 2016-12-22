#include "PhysicsSystem.hpp"
#include "Globals.hpp"
#include "GameEngine\GameEngine.h"



namespace ASSB
{
	void PhysicsSystem::Update(GameEngine &g,
		std::unordered_map<ASSB::Globals::ObjectID, RigidBodyComponent> &map)
	{
		// Location updating
		for (auto &pair : map)
		{
			if (!pair.second.static_)
			{
				ComponentHandle<TransformComponent> t = GameEngine::Instance->GetComponent<TransformComponent>(pair.first);
				t->SetPosition(t->GetPosition() + pair.second.velocity_);
			}
		}

		//!TODO:Convert to not using full N^2 items in map!
		for (auto &pair1 : map)
		{
			// If we are not collidable, don't bother for the entier loop.
			if (!pair1.second.collidable_)
				continue;

			for (auto &pair2 : map)
			{
				// If we're really just one person, don't bother.
				if (pair1.first == pair2.first)
					continue;

				// If we're not collidable, don't bother.
				if (!pair2.second.collidable_)
					continue;

				// If we are both static, don't bother.
				if (pair1.second.static_)
					if (pair2.second.static_)
						continue;
				
				// If one of us is not static, care a bit only if we are colliding.
				CollisionInfo info = isCollidingAABB(g, pair1, pair2);
				if (info == true)
				{
					if (!pair1.second.static_)
					{
						if (!pair2.second.static_)
							// Both pairs are dymanic
							resolveDynamicDynamicAABBCollision(g, pair1, pair2, info);
						else
							// Pair1 is dynamic
							resolveStaticAABBCollision(g, pair1, pair2, info);
					}
					else
						// Pair2 is dynamic
						resolveStaticAABBCollision(g, pair2, pair1, info);
				}
			}
		}
	}

	// Check if two objects are colliding
	CollisionInfo PhysicsSystem::isCollidingAABB(GameEngine &g,
		std::pair<const Globals::ObjectID, RigidBodyComponent> &obj1,
		std::pair<const Globals::ObjectID, RigidBodyComponent> &obj2)
	{
		ComponentHandle<TransformComponent> o1t = g.GetComponent<TransformComponent>(obj1.first);
		ComponentHandle<TransformComponent> o2t = g.GetComponent<TransformComponent>(obj2.first);
		const Graphics::Vector4 pos1{ o1t->GetPosition() };
		const Graphics::Vector4 pos2{ o2t->GetPosition() };
		const float Half_Obj1Width{ obj1.second.width_ / 2 };
		const float Half_Obj1Height{ obj1.second.height_ / 2 };
		const float Half_Obj2Width{ obj2.second.width_ / 2 };
		const float Half_Obj2Height{ obj2.second.height_ / 2 };
		const float left_o1 = pos1.X - Half_Obj1Width;
		const float left_o2 = pos2.X - Half_Obj2Width;
		const float right_o1 = pos1.X + Half_Obj1Width;
		const float right_o2 = pos2.X + Half_Obj2Width;
		const float top_o1 = pos1.Y - Half_Obj1Height;
		const float top_o2 = pos2.Y - Half_Obj2Height;
	  const float bottom_o1 = pos1.Y + Half_Obj1Height;
		const float bottom_o2 = pos2.Y + Half_Obj2Height;

		//const float LeftOffset = 
		// Case: Right side object 1 past left side object 2
		if (right_o1 >= left_o2)
		{
			//DEBUG_PRINT_VAR(pos1.X + Half_Obj1Width);
			//DEBUG_PRINT_VAR(pos2.X - Half_Obj2Width);
			//DEBUG_PRINT(">= Right 1 past Left 2 ^");
			// Case: Right side object 2 is past left side object 1
			if (right_o2 >= left_o1)
			{
				//DEBUG_PRINT_VAR(pos2.X + Half_Obj2Width);
				//DEBUG_PRINT_VAR(pos1.X - Half_Obj1Width);
				//DEBUG_PRINT(">= Right 2 past left 1 ^");
				// Case: Bottom side object 1 is past top side object 2
				if (bottom_o1 >= top_o2)
				{
					//DEBUG_PRINT_VAR(pos1.Y + Half_Obj1Height);
					//DEBUG_PRINT_VAR(pos2.Y - Half_Obj2Height);
					//DEBUG_PRINT(">= Bottom 1 past top 2 ^");
					// Case: Bottom side object 2 is past top side object 1
					if (bottom_o2 >= top_o1)
					{
						//DEBUG_PRINT_VAR(pos2.Y + Half_Obj2Height);
						//DEBUG_PRINT_VAR(pos1.Y - Half_Obj1Height);
						//DEBUG_PRINT(">= Bottom 2 past top 1 ^");
						// Colliding

						const float tb = bottom_o1 - top_o2;
						const float bt = bottom_o2 - top_o1;
						const float lr = right_o1 - left_o2;
						const float rl = right_o2 - left_o1;
						Graphics::Vector4 normal;
						float offset;

						if (tb <= bt && tb <= lr && tb <= rl)
							normal = Graphics::Vector4(0, 1, 0), offset = -tb;
						else if (bt <= lr && bt <= rl)
							normal = Graphics::Vector4(0, -1, 0), offset = -bt;
						else if (lr <= rl)
							normal = Graphics::Vector4(1, 0, 0), offset = -lr;
						else
							normal = Graphics::Vector4(-1, 0, 0), offset = -rl;

						return CollisionInfo(true, offset, normal, -normal);
					}
				}
			}
		}

		return CollisionInfo(false, 0, {}, {});
	}


	// Misleading qualifiers, not actually const for the Game Objects.
	void PhysicsSystem::resolveStaticAABBCollision(GameEngine &g,
		std::pair<const Globals::ObjectID, RigidBodyComponent> &dynamicObj,
		std::pair<const Globals::ObjectID, RigidBodyComponent> &staticObj,
		CollisionInfo info)
	{
		// Consider: Impulse?
		DEBUG_PRINT("Dynamic to Static Collision!");
		UNUSED(g);
		UNUSED(dynamicObj);
		UNUSED(staticObj);
		UNUSED(info);
	}

	static float dot(Graphics::Vector4 v1, Graphics::Vector4 v2)
	{
		return v1.X * v2.X + v1.Y * v2.Y;
	}
	// Misleading qualifiers, not actually const for the Game Objects
	void PhysicsSystem::resolveDynamicDynamicAABBCollision(GameEngine &g,
		std::pair<const Globals::ObjectID, RigidBodyComponent> &dynamicObj1,
		std::pair<const Globals::ObjectID, RigidBodyComponent> &dynamicObj2,
		CollisionInfo info)
	{
		DEBUG_PRINT("Dynamic to Dynamic Collision!");
		ComponentHandle<TransformComponent> t1 = GameEngine::Instance->GetComponent<TransformComponent>(dynamicObj1.first);
		ComponentHandle<TransformComponent> t2 = GameEngine::Instance->GetComponent<TransformComponent>(dynamicObj2.first);
		
		// Position Correction (assumption: Same mass, of "1")
		t1->SetPosition(t1->GetPosition() + info.Normal1 * info.Offset / 2);
		t2->SetPosition(t2->GetPosition() - info.Normal2 * info.Offset / 2);
    
		// Velocity Correction (assumption: Same mass, of "1")
		const Graphics::Vector4 effectiveVelocity{ dynamicObj2.second.velocity_ - dynamicObj1.second.velocity_ };
		const float normalMag{ dot(effectiveVelocity, info.Normal1) };
		const float elasticity{ 1.0f }; //!TODO: Tweak Elasticity! :D

		// We don't care if we aren't going to collide.
		if (normalMag > 0) 
			return;

		// Calcualte and apply impulse. Normally: (-(1 + elasticity) * normalMag) / ((1/mass1) + (1/mass2).
		// However, we are assuming it's a mass of 1.
		Graphics::Vector4 impulseVector = -(1 + elasticity) * normalMag;
		dynamicObj1.second.velocity_ -= impulseVector;
		dynamicObj2.second.velocity_ += impulseVector;
		DEBUG_PRINT("Impulse Applied!");
	}
}
