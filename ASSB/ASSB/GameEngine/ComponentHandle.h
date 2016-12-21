#pragma once
#include <unordered_map>
#include "Globals.hpp"

namespace ASSB
{
	template <typename T>
	class ComponentHandle
	{
	public:
		ComponentHandle(Globals::ObjectID objectId, std::unordered_map<Globals::ObjectID, T>& map);

		operator bool();
		const T* operator->() const;
		T* operator->();
		const T& operator*() const;
		T& operator*();
	private:
		std::unordered_map<Globals::ObjectID, T>& Map;
		Globals::ObjectID Id;

		ComponentHandle& operator=(const ComponentHandle& other);
	};
}

#include "ComponentHandle.tpp"
