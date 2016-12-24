#pragma once
#include <unordered_map>
#include <memory>
#include "Globals.hpp"

namespace ASSB
{
	template <typename T>
	class ComponentHandle
	{
	public:
		ComponentHandle(Globals::ObjectID objectId, std::unordered_map<Globals::ObjectID, std::unique_ptr<T>>& map);

		operator bool();
		const T* operator->() const;
		T* operator->();
		const T& operator*() const;
		T& operator*();

		ComponentHandle& operator=(const ComponentHandle& other);
	private:
		std::unordered_map<Globals::ObjectID, std::unique_ptr<T>>& Map;
		Globals::ObjectID Id;

	};
}

#include "ComponentHandle.tpp"
