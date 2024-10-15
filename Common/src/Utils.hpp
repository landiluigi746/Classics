#pragma once

#include <typeinfo>
#include <string>
#include <memory>

namespace Classics
{
	template<typename T>
	std::string GetTypeName()
	{
		return typeid(T).name();
	}

	template<typename T>
	using SharedPtr = std::shared_ptr<T>;

	template<typename T>
	using UniquePtr = std::unique_ptr<T>;
}