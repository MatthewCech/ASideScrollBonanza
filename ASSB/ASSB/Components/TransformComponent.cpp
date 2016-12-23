#include "TransformComponent.h"



namespace ASSB
{
	// Default constructor 
	TransformComponent::TransformComponent(Globals::ObjectID owner) : Component(owner), Position(), ScaleX(1), ScaleY(1), Rotation(0)
	{  }


	// Copy constructor
	TransformComponent::TransformComponent(const TransformComponent &rhs)
		: Component(rhs.Owner)
		, Position(rhs.Position)
		, ScaleX(rhs.ScaleX)
		, ScaleY(rhs.ScaleY)
		, Rotation(rhs.Rotation)
	{  }


	// Assignment Operator
	TransformComponent &TransformComponent::operator=(const TransformComponent &rhs)
	{
		if (this != &rhs)
		{
			Position = rhs.Position;
			ScaleX = rhs.ScaleX;
			ScaleY = rhs.ScaleY;
			Rotation = rhs.Rotation;
		}

		return *this;
	}


	Graphics::Vector4 TransformComponent::GetPosition()
	{
		return Position;
	}

	float TransformComponent::GetScaleX()
	{
		return ScaleX;
	}

	float TransformComponent::GetScaleY()
	{
		return ScaleY;
	}

	float TransformComponent::GetRotation()
	{
		return Rotation;
	}

	void TransformComponent::SetPosition(const Graphics::Vector4 & position)
	{
		Position = position;
	}

	void ASSB::TransformComponent::SetScale(float x, float y)
	{
		ScaleX = x;
		ScaleY = y;
	}

	void ASSB::TransformComponent::SetRotation(float rotation)
	{
		Rotation = rotation;
	}
}
