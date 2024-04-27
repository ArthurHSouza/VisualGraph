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

[[nodiscard]] std::vector<Graph::graphEdge> Graph::BFS(int sourceIndex)
{
	std::vector<graphEdge> ret;
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

std::vector<Graph::graphEdge> Graph::DFS(int sourceIndex)
{
	std::vector<graphEdge> ret;

	std::stack<std::size_t> S;

	S.push(sourceIndex);

	for (int i{}; i < adjList.size(); i++)
	{
		visted.push_back(Color::WHITE);
	}
	/*
	while (!S.empty())
	{
		std::size_t actual = S.top();
		S.pop();
		if (visted[actual] == Color::WHITE)
		{
			visted[actual] == Color::BLACK;

			for (const auto& i : adjList[actual])
			{
				if (visted[i] == Color::WHITE)
					S.push(i);
			}
			if(!S.empty())
				ret.emplace_back(actual, S.top(), 0);
		}
	}
	*/

	visted[sourceIndex] = Color::BLACK;
	while (!S.empty())
	{
		std::size_t actual = S.top();
		S.pop();

		std::cout << actual << " ";
		for (const auto& i : adjList[actual])
		{
			if (visted[i] == Color::WHITE)
			{
				S.push(i);
				visted[i] = Color::BLACK;
			}
		}
		if(!S.empty())
			ret.emplace_back(actual, S.top());
	}

	return ret;
}

void Graph::AddEdges(int source, int destination)
{
	adjList[source].push_back(destination);
	adjList[destination].push_back(source);
}