#include "Graph.hpp"
#include <queue>
#include <stack>
#include <limits>
#include <iostream>

Graph::Graph(std::size_t ammoutVertex)
{
	adjList.reserve(ammoutVertex);
	for (int i{}; i < ammoutVertex; i++)
	{
		adjList.emplace_back(std::vector<int>());
	}
}

[[nodiscard]] std::vector<GraphEdge> Graph::BFS(int sourceIndex)
{
	std::vector<GraphEdge> ret;
	for (int i{}; i < adjList.size(); i++)
	{
		visted.push_back(Color::WHITE);
		dist.push_back(std::numeric_limits<int>::infinity());
	}

	dist[sourceIndex] = 0;

	std::queue<int> Q;

	Q.push(sourceIndex);
	
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();

		for (const auto& i : adjList[u])
		{
			if (visted[i] == Color::WHITE)
			{
				visted[i] = Color::GRAY;
				dist[i] = dist[u] + 1;
				Q.push(i);
				ret.emplace_back( u, i, dist[i]);
			}
		}

		visted[u] = Color::BLACK;
	}
	return ret;
}

std::vector<GraphEdge> Graph::DFS(int sourceIndex)
{
	std::vector<GraphEdge> ret;

	for (int i{}; i < adjList.size(); i++)
	{
		visted.push_back(Color::WHITE);
		dist.push_back(std::numeric_limits<int>::infinity());
	}
	
	DFSRecursive(sourceIndex, ret);

	return ret;
}


void Graph::DFSRecursive(int sourceIndex, std::vector<GraphEdge>& ret)
{
	visted[sourceIndex] = Color::BLACK;
	for (const auto& adj : adjList[sourceIndex])
	{
		if (visted[adj] == Color::WHITE)
		{
			ret.emplace_back(sourceIndex, adj, 0);
			DFSRecursive(adj, ret);
		}
	}
}

void Graph::AddEdges(int source, int destination)
{
	adjList[source].push_back(destination);
	adjList[destination].push_back(source);
}