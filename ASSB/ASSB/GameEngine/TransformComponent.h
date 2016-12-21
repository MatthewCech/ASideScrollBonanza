#pragma once
#include "Graphics/Vector4.h"
#include "Graphics/ConstantBuffer.h"

namespace ASSB
{
	class TransformComponent
	{
	public:
		TransformComponent();
		Graphics::Vector4 GetPosition();
		float GetScaleX();
		float GetScaleY();
		float GetRotation();
		void SetPosition(const Graphics::Vector4& position);
		void SetScale(float x, float y);
		void SetRotation(float rotation);
	private:
		//slightly overkill
		float ScaleX;
		float ScaleY;
		Graphics::Vector4 Position;
		float Rotation;
	};
}
