#pragma once
#include "Component.hpp"
#include "Graphics\Vector4.h"



namespace ASSB
{
	// A rigid body for an object! By default, the objects are dynamic.
	// This can be changed with a bool in the constructor.
	class RigidBodyComponent : public Component
	{
		// frieeeeeend
		friend class PhysicsSystem;
	public:
		// Consructor
		RigidBodyComponent(bool isStatic = false);
	
		// Member functions - Set
		void SetWidth(float width);
		void SetHeight(float height);
		void SetStatic(bool isStatic);
		void SetCollidable(bool isCollidable);
		void SetVelocity(Graphics::Vector4 velocity);

		// Member functions - Get
		float GetWidth() const;
		float GetHeight() const;
		bool IsStatic() const;
		bool IsCollidable() const;
		Graphics::Vector4 GetVelocity() const;

	private:
		// Variables
		bool static_;
		bool collidable_;
		float width_;
		float height_;
		Graphics::Vector4 velocity_;

		// Omit
		RigidBodyComponent *operator=(const RigidBodyComponent &rhs) = delete;
	};
}
