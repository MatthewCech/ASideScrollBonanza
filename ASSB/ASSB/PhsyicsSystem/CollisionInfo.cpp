#include "CollisionInfo.hpp"


namespace ASSB
{
	// Constructor
	CollisionInfo::CollisionInfo(bool colliding, float offset, Graphics::Vector4 normal1, Graphics::Vector4 normal2)
		: Colliding(colliding)
		, Offset(offset)
		, Normal1(normal1)
		, Normal2(normal2)
	{  }


	// Bool operator
	CollisionInfo::operator bool()
	{
		return Colliding;
	}
}