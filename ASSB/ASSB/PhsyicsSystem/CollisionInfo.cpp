#include "CollisionInfo.hpp"


namespace ASSB
{
	// Constructor
	CollisionInfo::CollisionInfo(bool colliding, float offset, Graphics::Vector4 normal)
		: Colliding(colliding)
		, Offset(offset)
		, Normal(normal)
	{  }


	// Bool operator
	CollisionInfo::operator bool()
	{
		return Colliding;
	}
}