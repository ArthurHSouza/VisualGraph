#pragma once
#include <vector>
#include <iostream>

struct GraphEdge
{
	std::size_t origin;
	std::size_t destiny;
	std::size_t weight;
};

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

	void DFSRecursive(int sourceIndex, std::vector<GraphEdge>& ret);
public:

	Graph(std::size_t ammoutVertex);
	~Graph() = default;
	void AddEdges(int source, int destination);

	[[nodiscard]] std::vector<GraphEdge> BFS(int sourceIndex);
	[[nodiscard]] std::vector<GraphEdge> DFS(int sourceIndex);
};