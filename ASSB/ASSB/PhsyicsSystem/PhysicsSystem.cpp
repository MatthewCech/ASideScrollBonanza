#include "PhysicsSystem.hpp"
#include "Globals.hpp"
#include "GameEngine\GameEngine.h"
#include <climits>
#include <memory>



namespace ASSB
{
	void PhysicsSystem::Update(
		std::unordered_map<ASSB::Globals::ObjectID, std::unique_ptr<RigidBodyComponent>> &input, const GameTime &g)
	{
		// Define map as vector
		std::vector<std::unordered_map<ASSB::Globals::ObjectID, std::unique_ptr<RigidBodyComponent>>::iterator> map;//
		for (auto iter{ input.begin() }; iter != input.end(); ++iter)
		{
			if (iter->second->GetCollisionType() == ASSB::NO_COLLISION)
				continue;
			else
				map.push_back(iter);
		}

		// Location updating
		for (unsigned int i{ 0 }; i < map.size(); ++i)
		{
			if (!map[i]->second->static_)
			{
				ComponentHandle<TransformComponent> t = GameEngine::Instance->GetComponent<TransformComponent>(map[i]->first);
				t->SetPosition(t->GetPosition() + map[i]->second->velocity_ * static_cast<float>(g.DT));
			}
		}

		//!TODO:Convert to not using full N^2 items in map!
		for (unsigned int i{ 0 }; i < map.size(); ++i)
		{
			for (unsigned int j{ i }; j < map.size(); ++j)
			{
				// If we're really just one person, don't bother.
				if (map[i]->first == map[j]->first)
					continue;

				// If we are both static, don't bother.
				if (map[i]->second->static_)
					if (map[j]->second->static_)
						continue;

				// If one of us is not static, care a bit only if we are colliding.
				CollisionInfo info = isCollidingAABB(*map[i], *map[j]);
				if (info == true)
				{
					if (!map[i]->second->static_)
					{
						if (!map[j]->second->static_)
							// Both pairs are dymanic
							resolveDynamicDynamicAABBCollision(*map[i], *map[j], info);
						else
							// Pair1 is dynamic
							resolveStaticAABBCollision(*map[i], *map[j], info);
					}
					else
						// Pair2 is dynamic
						resolveStaticAABBCollision(*map[j], *map[i], info);
				}
			}
		}
	}


	static void absFloat(float &toAbs)
	{
		if (toAbs < 0)
			toAbs = FLT_MAX;
	}

	// Check if two objects are colliding
	CollisionInfo PhysicsSystem::isCollidingAABB(
		std::pair<const Globals::ObjectID, std::unique_ptr<RigidBodyComponent>> &obj1,
		std::pair<const Globals::ObjectID, std::unique_ptr<RigidBodyComponent>> &obj2)
	{
		ComponentHandle<TransformComponent> o1t = GameEngine::Instance->GetComponent<TransformComponent>(obj1.first);
		ComponentHandle<TransformComponent> o2t = GameEngine::Instance->GetComponent<TransformComponent>(obj2.first);
		const Graphics::Vector4 p1 = o1t->GetPosition();
		const Graphics::Vector4 p2 = o2t->GetPosition();

		// Width and height
		const float w1 = obj1.second->width_ * o1t->GetScaleX();
		const float w2 = obj2.second->width_ * o2t->GetScaleY();
		const float h1 = obj1.second->height_ * o1t->GetScaleX();
		const float h2 = obj2.second->height_ * o2t->GetScaleY();

		// Sides
		const float l1 = p1.X - w1 / 2;
		const float l2 = p2.X - w2 / 2;
		const float r1 = p1.X + w1 / 2;
		const float r2 = p2.X + w2 / 2;
		const float t1 = p1.Y - h1 / 2;
		const float t2 = p2.Y - h2 / 2;
	  const float b1 = p1.Y + h1 / 2;
		const float b2 = p2.Y + h2 / 2;

		// Establish if we are colliding.
		if (r1 < l2) return CollisionInfo(false);
		if (l1 > r2) return CollisionInfo(false);
		if (b1 < t2) return CollisionInfo(false);
		if (t1 > b2) return CollisionInfo(false);

		// Offset into the other object:
		float offR = r1 - l2;
		float offL = l2 - r1;
		float offT = b1 - t2;
		float offB = b2 - t1;
		absFloat(offR);
		absFloat(offL);
		absFloat(offT);
		absFloat(offB);

		// Establish the side we collided on and get the normal and offset of collision
		Graphics::Vector4 normal;
		float finalOffset;
		if (offR <= offL && offR <= offT && offR <= offB)
		{
			normal = Graphics::Vector4(1, 0, 0);
			finalOffset = -offR;
		}
		else if (offL <= offT && offL <= offB)
		{
			normal = Graphics::Vector4(-1, 0, 0);
			finalOffset = -offL;
		}
		else if (offT <= offB)
		{
			normal = Graphics::Vector4(0, 1, 0);
			finalOffset = -offT;
		}
		else
		{
			normal = Graphics::Vector4(0, -1, 0);
			finalOffset = -offB;
		}

		// Return collisionInfo object. Realized after the fact I don't need
		// two normal variables.
		return CollisionInfo(true, finalOffset, normal);
	}

	static float dot(Graphics::Vector4 v1, Graphics::Vector4 v2)
	{
		return v1.X * v2.X + v1.Y * v2.Y;
	}
	// Misleading qualifiers, not actually const for the Game Objects.
	void PhysicsSystem::resolveStaticAABBCollision(
		std::pair<const Globals::ObjectID, std::unique_ptr<RigidBodyComponent>> &dynamicObj,
		std::pair<const Globals::ObjectID, std::unique_ptr<RigidBodyComponent>> &staticObj,
		CollisionInfo info)
	{
		UNUSED(staticObj);
		// Excecute: Impulse, apply only to 1 side.
		DEBUG_PRINT("Static Collision!");
		ComponentHandle<TransformComponent> t1 = GameEngine::Instance->GetComponent<TransformComponent>(dynamicObj.first);
		//ComponentHandle<TransformComponent> t2 = GameEngine::Instance->GetComponent<TransformComponent>(dynamicObj2.first);

		// Position Correction, using fake masses.
		// (masses included as dummy values to make sure I'm following correct steps)
		const float mass1 = 1, mass2 = 1;
		const float massTotal = mass1 + mass2;
		const Graphics::Vector4 OffsetVec = info.Normal * info.Offset;
		t1->SetPosition(t1->GetPosition() - OffsetVec);
		//t2->SetPosition(t2->GetPosition() - (OffsetVec * mass1 / massTotal));


		//const Graphics::Vector4 effectiveVelocity = dynamicObj.second->velocity_;
		// Velocity Correction (assumption: Same mass, of "1")
		const Graphics::Vector4 effectiveVelocity = dynamicObj.second->velocity_;
		const float normalMag = dot(effectiveVelocity, info.Normal);
		const float elasticity = 0.5f; //!TODO: Tweak Elasticity! Value: (0-1)

		if (normalMag > 0)
			return;

		// Calcualte and apply impulse. Normally: (-(1 + elasticity) * normalMag) / ((1/mass1) + (1/mass2).
		// However, we are assuming it's a mass of 1.
		float impScalar = -elasticity * normalMag;
		//impScalar /= 1 / mass1 + 1 / mass2;
		Graphics::Vector4 impulseVector = info.Normal * impScalar;
		dynamicObj.second->velocity_ += impulseVector;
		//dynamicObj2.second->velocity_ += impulseVector;
		DEBUG_PRINT("Static velocity correction A\applied!");
	}

	// Misleading qualifiers, not actually const for the Game Objects
	void PhysicsSystem::resolveDynamicDynamicAABBCollision(
		std::pair<const Globals::ObjectID, std::unique_ptr<RigidBodyComponent>> &dynamicObj1,
		std::pair<const Globals::ObjectID, std::unique_ptr<RigidBodyComponent>> &dynamicObj2,
		CollisionInfo info)
	{
		DEBUG_PRINT("Dynamic to Dynamic Collision!");
		ComponentHandle<TransformComponent> t1 = GameEngine::Instance->GetComponent<TransformComponent>(dynamicObj1.first);
		ComponentHandle<TransformComponent> t2 = GameEngine::Instance->GetComponent<TransformComponent>(dynamicObj2.first);
		
		// Position Correction, using fake masses.
		// (masses included as dummy values to make sure I'm following correct steps)
		const float mass1 = 1, mass2 = 1;
		const float massTotal = mass1 + mass2;
		const Graphics::Vector4 OffsetVec = info.Normal * info.Offset;
		t1->SetPosition(t1->GetPosition() + (OffsetVec * mass2 / massTotal));
		t2->SetPosition(t2->GetPosition() - (OffsetVec * mass1 / massTotal));
    
		// Velocity Correction (assumption: Same mass, of "1")
		const Graphics::Vector4 effectiveVelocity = dynamicObj2.second->velocity_ - dynamicObj1.second->velocity_;
		const float normalMag = dot(effectiveVelocity, info.Normal);
		const float elasticity = 1.0f ; //!TODO: Tweak Elasticity! Value: (0-1)

		// We don't care if we aren't going to collide.
		if (normalMag > 0) 
			return;

		// Calcualte and apply impulse. Normally: (-(1 + elasticity) * normalMag) / ((1/mass1) + (1/mass2).
		// However, we are assuming it's a mass of 1.
		float impScalar = -(1 + elasticity);
		impScalar *= normalMag;
		impScalar /= 1 / mass1 + 1 / mass2;
		Graphics::Vector4 impulseVector = info.Normal * impScalar;
		dynamicObj1.second->velocity_ -= impulseVector;
		dynamicObj2.second->velocity_ += impulseVector;
		DEBUG_PRINT("Impulse Applied!");
	}
}
