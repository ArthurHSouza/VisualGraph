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

std::stack<std::size_t> Graph::TopologicalSort()
{
	std::stack<size_t> ret;

	if (HaveCycle()) 
		return ret;
	visted.clear();
	for (std::size_t i{}; i < adjList.size(); i++)
	{
		visted.push_back(Color::WHITE);
	}
	for (std::size_t i{}; i < adjList.size(); i++)
	{
		if (visted[i] == Color::WHITE)
		{
			DFSTopologicalSort(i, ret);
		}
	}
	return ret;
}

std::vector<std::vector<std::size_t>> Graph::KosarujoSSC()
{
	std::vector<std::vector<std::size_t>> ret;
	auto j = 0;
	auto topSort = TopologicalSort();
	if (topSort.size() == 0)
		return ret;
	visted.clear();
	for (std::size_t i{}; i < adjList.size(); i++)
	{
		visted.push_back(Color::WHITE);
	}
	
	TransposeGraph();
	for (std::size_t i = topSort.size(); i > 0; i--)
	{
		if (visted[topSort.top()] == Color::WHITE)
		{
			std::vector<std::size_t> temp;
			DFSRecursive(topSort.top(), temp);
			ret.push_back(temp);
			j++;
		}
		topSort.pop();
	}
	std::cout << j << " SCC\n";
	return ret;
}


void Graph::TransposeGraph()
{
	std::vector<std::vector<std::size_t>> newAdjList;
	newAdjList.reserve(adjList.size());

	for (std::size_t i{}; i < adjList.size(); i++)
	{
		newAdjList.emplace_back(std::vector<std::size_t>());
	}

	for (std::size_t i = 0; i < adjList.size(); i++)
	{
		for (const auto& j : adjList[i])
		{
			newAdjList[j].push_back(i);
		}
	}
	adjList = newAdjList;
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

void Graph::DFSRecursive(std::size_t sourceIndex, std::vector<std::size_t>& ret)
{
	visted[sourceIndex] = Color::BLACK;
	ret.emplace_back(sourceIndex);
	for (const auto& adj : adjList[sourceIndex])
	{
		if (visted[adj] == Color::WHITE)
		{
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

void Graph::DFSTopologicalSort(std::size_t sourceIndex, std::stack<std::size_t>& ret)
{
	visted[sourceIndex] = Color::BLACK;

	for (const auto& adj : adjList[sourceIndex])
	{
		if (visted[adj] == Color::WHITE)
			DFSTopologicalSort(adj, ret);
		
	}
	ret.push( sourceIndex);
}

void Graph::AddEdges(std::size_t source, std::size_t destination)
{
	adjList[source].push_back(destination);
}