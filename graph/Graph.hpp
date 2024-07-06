#pragma once
#include <vector>
#include <stack>
#include <utility>
#include <iostream>
//TODO: Remove all 'iostram'

struct GraphEdge
{
	std::size_t origin = 0;
	std::size_t destiny = 0;
	float weight = 0;
};

class Graph
{
private:
	struct AdjListNode
	{
		size_t destiny;
		float weight = 0;
	};

	std::vector<std::vector<AdjListNode>> adjList;
	std::vector<GraphEdge> edgeList;
	enum class Color
	{
		WHITE, GRAY, BLACK
	};
	std::vector<Color> visted;
	size_t timeCounter{}; //DFS only
	std::vector<std::pair<size_t, size_t>> timeFinishedIndex;

	void TransposeGraph();
	//This one is to know what edges the DFS travel
	void DFSRecursive(std::size_t sourceIndex, std::vector<GraphEdge>& ret);
	//This one is to know what nodes the DFS travel
	void DFSRecursive(std::size_t sourceIndex, std::vector<std::size_t>& ret);
	//This one does not store any edge or node traveled
	void DFSRecursive(size_t sourceIndex);
	bool DFSRecursiveVerifyCicle(std::size_t sourceIndex);
	void DFSTopologicalSort(std::size_t sourceIndex, std::stack<std::size_t>& ret);
public:

	Graph(std::size_t ammoutVertex);
	~Graph() = default;
	void AddEdges(std::size_t source, std::size_t destination, float weight = 0.f);
	void AddEdgesToEdgeList(std::size_t source, std::size_t destination, float weight);

	[[nodiscard]] std::vector<GraphEdge> BFS(std::size_t sourceIndex);
	[[nodiscard]] std::vector<GraphEdge> DFS(std::size_t sourceIndex);
	[[nodiscard]] bool HaveCycle();
	//If the stack returned is empty that mean that the graph have a cycle
	//so in that way is impossible to apply the Topological Sort algorithm
	[[nodiscard]] std::stack<std::size_t> TopologicalSort();
	std::vector<std::vector<std::size_t>> KosarujoSSC();
	//Returns the vertex index and the minimum distance to it
	[[nodiscard]] std::vector<GraphEdge> Dijkstra(std::size_t sourceIndex);
	[[nodiscard]] std::vector<GraphEdge> BellmanFord(std::size_t sourceIndex);
};