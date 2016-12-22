#pragma once
#include "Component.hpp"
#include "Graphics\Vector4.h"



namespace ASSB
{
	class RigidBodyComponent : public Component
	{
		// frieeeeeend
		friend class PhysicsSystem;
	public:
		// Consructor
		RigidBodyComponent(bool isStatic);
	
		// Member functions
		void SetWidth(float width);
		void SetHeight(float height);
		float GetWidth() const;
		float GetHeight() const;
		void SetCollidable(bool isCollidable);
		bool IsCollidable() const;
		Graphics::Vector4 GetVelocity() const;
		void SetVelocity(Graphics::Vector4 velocity);

	private:
		bool static_;
		bool collidable_;
		float width_;
		float height_;
		Graphics::Vector4 velocity_;

		RigidBodyComponent(const RigidBodyComponent &rhs) = delete;
		RigidBodyComponent *operator=(const RigidBodyComponent &rhs) = delete;
	};
}
