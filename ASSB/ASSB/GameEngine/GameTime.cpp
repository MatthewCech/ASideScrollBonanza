#include "GameTime.h"
#include <cmath>

namespace ASSB
{
	GameTime::GameTime() : MaxDT(0.1f)
	{  }

	void GameTime::Tick()
	{
		auto now = std::chrono::steady_clock::now();
		if (Last.time_since_epoch() == std::chrono::nanoseconds())
		{
			Start = now;
			Last = now;
		}
		auto span = now - Last;
		DT = std::fmin(span.count() / 1000000000.0f, MaxDT); //nanosecond to second
		span = now - Start;
		RunTime = span.count() / 1000000000.0f; //nanosecond to second
		Last = now;
	}
}
