#include "AssetManager.hpp"

template<typename T>
static void AssetManager<T>::Erase(std::string filePath)
{
	cache.erase(filePath);
}