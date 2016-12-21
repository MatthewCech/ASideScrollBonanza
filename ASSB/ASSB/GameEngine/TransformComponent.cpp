#include "TransformComponent.h"

namespace ASSB
{
	TransformComponent::TransformComponent()
	{
	}

	Graphics::Vector4 TransformComponent::GetPosition()
	{
		return Position;
	}

	float TransformComponent::GetScaleX()
	{
		return ScaleY;
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
