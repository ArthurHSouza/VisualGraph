#pragma once
#include <vector>
#include <limits>
#include <queue>
#include <iostream>
#include <utility>

class Graph
{
private:
	std::vector<std::vector<int>> adjList;
	enum class Color
	{
		WHITE, GRAY, BLACK
	};
	std::vector<Color> visted;
	std::vector<int> dist;

public:
	Graph(std::size_t ammoutVertex);
	~Graph() = default;
	void AddEdges(int source, int destination);

	[[nodiscard]] std::vector<std::pair<int, int>> BFS(int sourceIndex);


};