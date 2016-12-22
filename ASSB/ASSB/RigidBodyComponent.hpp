#pragma once
#include "Component.hpp"
//#include "Globals.hpp"



namespace ASSB
{
	class ASSBFloat3 
	{ 
	public: 
		ASSBFloat3() : X(0), Y(0), Z(0)
		{ }
		float X;
		float Y;
		float Z;
	};

	class RigidBodyComponent : public Component
	{
		// frieeeeeend
		//friend class PhysicsSystem;
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
		ASSBFloat3 GetVelocity() const;
		void SetVelocity(ASSBFloat3 velocity);

	private:
		bool static_;
		bool collidable_;
		float width_;
		float height_;
		ASSBFloat3 velocity_;

		RigidBodyComponent(const RigidBodyComponent &rhs) = delete;
		RigidBodyComponent *operator=(const RigidBodyComponent &rhs) = delete;
	};
}
