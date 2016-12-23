#pragma once
#include "ComponentHandle.h"
#include "Components/TransformComponent.h"
#include "Graphics/Vector4.h"
#include "EventSystem/ObjectEventManager.hpp"
#include "Events/UpdateEvent.hpp"
#include <vector>



namespace ASSB
{
	// Random utilities and whatnot
	class InterpObj 
	{
	public:
		// Constructor
		InterpObj(Globals::ObjectID id, Graphics::Vector4 start, Graphics::Vector4 desto, double lengthMS, double startTime)
			: ID(id)
			, Start(start)
			, Desto(desto)
			, Length(lengthMS)
			, StartTime(startTime)
		{  }

		// Variables
		Globals::ObjectID ID;
		Graphics::Vector4 Start;
		Graphics::Vector4 Desto;
		double Length;
		double StartTime;

	private:
		// Omit
		//InterpObj(const InterpObj &rhs) = delete;
	};

	class Utilities : public EventSystem::ObjectEventManager
	{
	public:
		// Constructor
		Utilities();

		// Position Interpolation - Currently Quad
		// Time measured in milliseconds.
		void InterpolatePos(Globals::ObjectID id, Graphics::Vector4 desto, double ms);

		// Utilities instance
		static Utilities *Instance;

	private:
		// Variables
		std::vector<InterpObj> activeIterpolators_;
		void onUpdate(UpdateEvent *e);
		double lastTime_;

		// Omit
		Utilities &operator=(const Utilities &rhs) = delete;
		Utilities(const Utilities &rhs) = delete;
	};
}
