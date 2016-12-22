#include "RigidBodyComponent.hpp"



namespace ASSB
{
	// Constructor
	RigidBodyComponent::RigidBodyComponent(bool isStatic) 
		: static_(isStatic)
		, collidable_(true)
		, width_(1)
		, height_(1)
		, velocity_()
	{  }

	void RigidBodyComponent::SetWidth(float width)
	{
		width_ = width;
	}

	void RigidBodyComponent::SetHeight(float height)
	{
		height_ = height;
	}

	float RigidBodyComponent::GetWidth() const
	{
		return width_;
	}

	float RigidBodyComponent::GetHeight() const
	{
		return height_;
	}

	void RigidBodyComponent::SetCollidable(bool isCollidable)
	{
		collidable_ = isCollidable;
	}

	bool RigidBodyComponent::IsCollidable() const
	{
		return collidable_;
	}

	Graphics::Vector4  RigidBodyComponent::GetVelocity() const
	{
		return velocity_;
	}

	void RigidBodyComponent::SetVelocity(Graphics::Vector4 velocity)
	{
		velocity_ = velocity;
	}

	bool RigidBodyComponent::IsStatic() const
	{
		return static_;
	}

	void RigidBodyComponent::SetStatic(bool isStatic)
	{
		static_ = isStatic;
	}
}
