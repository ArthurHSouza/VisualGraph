#include "Graph.hpp"
#include <queue>
#include <stack>
#include <limits>
#include <iostream>

Graph::Graph(std::size_t ammoutVertex)
{
	adjList.reserve(ammoutVertex);
	for (std::size_t i{}; i < ammoutVertex; i++)
	{
		adjList.emplace_back(std::vector<std::size_t>());
	}
}

[[nodiscard]] std::vector<GraphEdge> Graph::BFS(std::size_t sourceIndex)
{
	std::vector<GraphEdge> ret;
	for (std::size_t i{}; i < adjList.size(); i++)
	{
		visted.push_back(Color::WHITE);
		dist.push_back(std::numeric_limits<std::size_t>::infinity());
	}

	dist[sourceIndex] = 0;

	std::queue<std::size_t> Q;

	Q.push(sourceIndex);
	
	while (!Q.empty())
	{
		std::size_t u = Q.front();
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

std::vector<GraphEdge> Graph::DFS(std::size_t sourceIndex)
{
	std::vector<GraphEdge> ret;

	for (std::size_t i{}; i < adjList.size(); i++)
	{
		visted.push_back(Color::WHITE);
		dist.push_back(std::numeric_limits<std::size_t>::infinity());
	}
	
	DFSRecursive(sourceIndex, ret);

	return ret;
}

bool Graph::HaveCycle()
{
	for (std::size_t i{}; i < adjList.size(); i++)
	{
		visted.push_back(Color::WHITE);
	}
	for (std::size_t i{}; i < adjList.size(); i++)
	{
		if(DFSRecursiveVerifyCicle(i))
			return true;
		for (auto& v : visted) v = Color::WHITE;
	}
	return false;
}


void Graph::DFSRecursive(std::size_t sourceIndex, std::vector<GraphEdge>& ret)
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

bool Graph::DFSRecursiveVerifyCicle(std::size_t sourceIndex)
{
	visted[sourceIndex] = Color::BLACK;
	for (const auto& adj : adjList[sourceIndex])
	{
		if (visted[adj] == Color::WHITE)
		{
			return DFSRecursiveVerifyCicle(adj);
		}
		else
		{
			return true;
		}
	}
	return false;
}

void Graph::AddEdges(std::size_t source, std::size_t destination)
{
	adjList[source].push_back(destination);
}