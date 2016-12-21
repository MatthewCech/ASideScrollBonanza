#include "ComponentHandle.h"

namespace ASSB
{
	template<typename T>
	inline ComponentHandle<T>::ComponentHandle(unsigned long long objectId, std::unordered_map<unsigned long long, T>& map) : Map(map), Id(id)
	{

	}

	template<typename T>
	inline ComponentHandle<T>::operator bool()
	{
		return Map.find(Id) != Map.end();
	}

	template<typename T>
	const T & ComponentHandle<T>::operator->() const
	{
		return Map[Id];
	}

	template<typename T>
	T & ComponentHandle<T>::operator->()
	{
		return Map[Id];
	}
}
