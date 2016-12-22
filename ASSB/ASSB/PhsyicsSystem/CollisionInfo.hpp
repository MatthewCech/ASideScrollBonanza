#pragma once
#include "Graphics\Vector4.h"



namespace ASSB
{
	// Object containing info about the collision that just occured.
	class CollisionInfo
	{
	public:
		// Constructor
		CollisionInfo(bool colliding, float offset, Graphics::Vector4 normal1, Graphics::Vector4 normal2);

		// Bool operator overload
		operator bool();

		// Variables
		bool Colliding;
		float Offset;
		Graphics::Vector4 Normal1;
		Graphics::Vector4 Normal2;
	};
}
