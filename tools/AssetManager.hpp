#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <unordered_map>

template <typename T> class AssetManager
{
	static std::unordered_map<std::string, T> cache;

public:
	AssetManager() = delete;

	// Load and get a shared SFML asset with T::loadFromFile()
	static T& Get(std::string filePath)
	{
		try
		{
			return cache.at(filePath);
		}
		catch (std::out_of_range&)
		{
			T& asset = cache[filePath];
			asset.loadFromFile(filePath);
			return asset;
		}
	}

	// Free a shared SFML asset
	static void Erase(std::string filePath);
};

template <typename T> std::unordered_map<std::string, T> AssetManager<T>::cache = {};