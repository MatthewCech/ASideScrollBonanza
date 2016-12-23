#pragma once
#include "Component.hpp"
#include "Graphics/Vector4.h"
#include "EventSystem/EventCarrier.hpp"
#include  <vector>


namespace ASSB
{
	// A rigid body for an object! By default, the objects are dynamic.
	// This can be changed with a bool in the constructor.
	enum CollisionType { COLLIDABLE, GHOSTING, NO_COLLISION };
	class RigidBodyComponent : public Component
	{
		// frieeeeeend
		friend class PhysicsSystem;
	public:
		// Consructor
		RigidBodyComponent(Globals::ObjectID owner);
	
		// Member functions - Set
		void SetWidth(float width);
		void SetHeight(float height);
		void SetStatic(bool isStatic);
		void SetCollisionType(CollisionType type);
		void SetVelocity(Graphics::Vector4 velocity);

		// Event binding
		template<typename EventType>
		void AddDispatchOnCollision(EventType *e);

		// Member functions - Get
		bool IsStatic() const;
		float GetWidth() const;
		float GetHeight() const;
		Graphics::Vector4 GetVelocity() const;
		CollisionType GetCollisionType() const;

	private:
		// Variables
		CollisionType colType_;
		bool static_;
		float width_;
		float height_;
		Graphics::Vector4 velocity_;

		// Omit
		RigidBodyComponent *operator=(const RigidBodyComponent &rhs) = delete;
		std::vector<EventSystem::ECBase *> dispatchables_;
		void dispatchAll();
	};
}

#include "RigidBodyComponent.tpp"
