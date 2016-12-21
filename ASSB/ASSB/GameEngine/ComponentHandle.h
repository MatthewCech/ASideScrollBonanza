#pragma once
#include <unordered_map>

namespace ASSB
{
	template <typename T>
	class ComponentHandle
	{
	public:
		ComponentHandle(unsigned long long objectId, std::unordered_map<unsigned long long, T>& map);

		operator bool();
		const T& operator->() const;
		T& operator->();
	private:
		std::unordered_map<unsigned long long, T>& Map;
		unsigned long long Id;
	};
}

#include "ComponentHandle.tpp"
