#include "AssetManager.hpp"

template<typename T>
void AssetManager<T>::Erase(std::string filePath)
{
	cache.erase(filePath);
}