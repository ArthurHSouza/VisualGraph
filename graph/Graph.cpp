#include "Graph.hpp"


Graph::Graph(std::size_t ammoutVertex)
{
	adjList.reserve(ammoutVertex);
	for (int i{}; i < ammoutVertex; i++)
	{
		adjList.emplace_back(std::vector<int>());
	}
}

[[nodiscard]] std::vector<std::pair<int, int>> Graph::BFS(int sourceIndex)
{
	std::vector<std::pair<int, int>> ret;
	for (int i{}; i < adjList.size(); i++)
	{
		visted.push_back(Color::WHITE);
		dist.push_back(std::numeric_limits<int>::infinity());
	}

	dist[sourceIndex] = 0;

	std::queue<int> Q;

	Q.push(sourceIndex);
	ret.push_back({ sourceIndex, dist[sourceIndex] });
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();

		for (auto& i : adjList[u])
		{
			if (visted[i] == Color::WHITE)
			{
				visted[i] = Color::GRAY;
				dist[i] = dist[u] + 1;
				Q.push(i);
				ret.push_back({ i, dist[i] });
			}
		}

		visted[u] = Color::BLACK;
	}
	return ret;
}

void Graph::AddEdges(int source, int destination)
{
	adjList[source].push_back(destination);
	adjList[destination].push_back(source);
}