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
	std::vector<std::vector<std::size_t>> adjList;
	enum class Color
	{
		WHITE, GRAY, BLACK
	};
	std::vector<Color> visted;
	std::vector<std::size_t> dist;

	void DFSRecursive(std::size_t sourceIndex, std::vector<GraphEdge>& ret);
public:

	Graph(std::size_t ammoutVertex);
	~Graph() = default;
	void AddEdges(std::size_t source, std::size_t destination);

	[[nodiscard]] std::vector<GraphEdge> BFS(std::size_t sourceIndex);
	[[nodiscard]] std::vector<GraphEdge> DFS(std::size_t sourceIndex);
};