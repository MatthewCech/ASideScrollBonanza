#include "GameTime.h"

namespace ASSB
{
	GameTime::GameTime()
	{
		Start = std::chrono::steady_clock::now();
		Last = std::chrono::steady_clock::now();
	}

	void GameTime::Tick()
	{
		auto span = std::chrono::steady_clock::now() - Last;
		DT = span.count() / 1000000000.0; //nanosecond to second
		span = std::chrono::steady_clock::now() - Start;
		RunTime = span.count() / 1000000000.0; //nanosecond to second
		Last = std::chrono::steady_clock::now();
	}
}
