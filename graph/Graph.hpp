#pragma once
#include <vector>
#include <iostream>

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

	struct graphEdge 
	{
		std::size_t origin;
		std::size_t destiny;
		std::size_t weight;
	};

	Graph(std::size_t ammoutVertex);
	~Graph() = default;
	void AddEdges(int source, int destination);

	[[nodiscard]] std::vector<graphEdge> BFS(int sourceIndex);
	[[nodiscard]] std::vector<graphEdge> DFS(int sourceIndex);
};