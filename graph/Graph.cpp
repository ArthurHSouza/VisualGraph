#include "Graph.hpp"
#include <queue>
#include <stack>
#include <limits>
#include <map>
#include "Heap.hpp"
#include <iostream>

Graph::Graph(std::size_t ammoutVertex)
{
	adjList.reserve(ammoutVertex);
	edgeList.reserve(ammoutVertex);
	for (std::size_t i{}; i < ammoutVertex; i++)
	{
		adjList.emplace_back(std::vector<AdjListNode>());
	}
}

[[nodiscard]] std::vector<GraphEdge> Graph::BFS(std::size_t sourceIndex)
{
	std::vector<GraphEdge> ret;
	std::vector<float> dist;
	for (std::size_t i{}; i < adjList.size(); i++)
	{
		visted.push_back(Color::WHITE);
		dist.push_back(std::numeric_limits<float>::infinity());
	}

	dist.at(sourceIndex) = 0;

	std::queue<std::size_t> Q;

	Q.push(sourceIndex);
	
	while (!Q.empty())
	{
		std::size_t u = Q.front();
		Q.pop();

		for (const auto& i : adjList.at(u))
		{
			if (visted[i.destiny] == Color::WHITE)
			{
				visted[i.destiny] = Color::GRAY;
				dist[i.destiny] = dist.at(u) + 1;
				Q.push(i.destiny);
				ret.emplace_back( u, i.destiny, dist[i.destiny]);
			}
		}

		visted.at(u) = Color::BLACK;
	}
	return ret;
}

std::vector<GraphEdge> Graph::DFS(std::size_t sourceIndex)
{
	std::vector<GraphEdge> ret;
	timeFinishedIndex = std::vector<std::pair<size_t,size_t>> (adjList.size(), { 0,0 });

	for (std::size_t i{}; i < adjList.size(); i++)
	{
		visted.push_back(Color::WHITE);
	}

	DFSRecursive(sourceIndex, ret);

	//This is done only to travel all the nodes
	for (size_t i{}; i < adjList.size(); i++)
	{
		if(visted.at(i) == Color::WHITE)
			DFSRecursive(i);
	}

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
		if (visted.at(i) == Color::WHITE)
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
	//auto topSort = TopologicalSort();
	DFS(0);
	auto timeFinishedCpy = timeFinishedIndex;
	timeFinishedIndex.clear();

	if (timeFinishedCpy.size() == 0)
		return ret;

	visted.clear();
	for (std::size_t i{}; i < adjList.size(); i++)
	{
		visted.push_back(Color::WHITE);
	}
	std::ranges::sort(timeFinishedCpy, std::greater<std::pair<size_t, size_t>>());
	TransposeGraph();
	for (const auto& i : timeFinishedCpy)
	{
		if (visted[i.second] == Color::WHITE)
		{
			std::vector<std::size_t> temp;
			DFSRecursive(i.second, temp);
			ret.push_back(temp);
			j++;
		}
	}
	std::cout << j << " SCC\n";
	return ret;
}

std::vector<GraphEdge> Graph::Dijkstra(std::size_t sourceIndex)
{
	std::vector<GraphEdge> ret(adjList.size());

	std::vector<float> distance;
	std::vector < std::pair<float, std::size_t>> distance_index;
	for (std::size_t i{}; i < adjList.size(); i++)
	{
		distance.push_back(std::numeric_limits<float>::infinity());
	}
	distance.at(sourceIndex) = 0;
	
	distance_index.push_back(std::pair<float, std::size_t>{ 0.f ,sourceIndex });
	Heap weightQueue(distance_index,true);

	while (!weightQueue.Empty())
	{
		auto top = weightQueue.Top().second;

		weightQueue.Pop();
		for (const auto& i : adjList.at(top))
		{
			//Relaxing
			if (distance.at(i.destiny) > distance.at(top) + i.weight)
			{
				ret.at(i.destiny) = {top, i.destiny, distance.at(top) + i.weight};
				distance.at(i.destiny) = distance.at(top) + i.weight;
				distance_index.push_back({ distance.at(i.destiny), i.destiny});
			}
		}

		weightQueue.Update();
	}
	return ret;
}

std::vector<GraphEdge> Graph::BellmanFord(std::size_t sourceIndex)
{
	std::vector<GraphEdge> ret(adjList.size());

	std::vector<float> distance;

	for (std::size_t i{}; i < adjList.size(); i++)
	{
		distance.push_back(std::numeric_limits<float>::infinity());
	}
	distance.at(sourceIndex) = 0;

	size_t iOut{};
	for (; iOut < edgeList.size(); iOut++)
	{
		for (size_t i{}; i < edgeList.size(); i++)
		{
			size_t origin = edgeList.at(i).origin;
			size_t destiny = edgeList.at(i).destiny;
			float weight = edgeList.at(i).weight;

			//Relaxing
			if (distance.at(destiny) > distance.at(origin) + weight)
			{
				ret.at(destiny) = { origin, destiny, distance[origin] + weight };
				distance[destiny] = distance[origin] + weight;
			}
		}
	}

	for (size_t i{}; i < edgeList.size(); i++)
	{
		size_t origin = edgeList[i].origin;
		size_t destiny = edgeList[i].destiny;
		float weight = edgeList[i].weight;

		if (distance[destiny] > distance[origin] + weight)
		{
			return std::vector<GraphEdge>();
		}
	}

	return ret;
}

std::vector<GraphEdge> Graph::PrimMST()
{
	std::vector<GraphEdge> ret(adjList.size(), {0,0,0});
	std::vector<bool> vist(adjList.size(), false);
	std::vector<float> distance;
	std::vector < std::pair<float, std::size_t>> distance_index;
	for (std::size_t i{}; i < adjList.size(); i++)
	{
		distance.push_back(std::numeric_limits<float>::infinity());
	}
	distance.at(0) = 0;

	distance_index.push_back(std::pair<float, std::size_t>{ 0.f, 0 });
	Heap weightQueue(distance_index, true);

	while (!weightQueue.Empty())
	{
		auto top = weightQueue.Top().second;

		weightQueue.Pop();
		for (const auto& i : adjList.at(top))
		{
			//Does not take a node that is already added in the tree
			if (!vist.at(i.destiny) && distance.at(i.destiny) > i.weight)
			{
				ret.at(i.destiny) = { top, i.destiny, distance.at(top) + i.weight };
				distance.at(i.destiny) = distance.at(top) + i.weight;
				distance_index.push_back({ distance.at(i.destiny), i.destiny });
			}
		}
		vist.at(top) = true;

		weightQueue.Update();
	}
	return ret;
}

void Graph::TransposeGraph()
{
	std::vector<std::vector<AdjListNode>> newAdjList;
	newAdjList.reserve(adjList.size());

	for (std::size_t i{}; i < adjList.size(); i++)
	{
		newAdjList.emplace_back(std::vector<AdjListNode>());
	}

	for (std::size_t i = 0; i < adjList.size(); i++)
	{
		for (const auto& j : adjList.at(i))
		{
			newAdjList[j.destiny].push_back({i,j.weight});
		}
	}
	adjList = newAdjList;
}

void Graph::DFSRecursive(std::size_t sourceIndex, std::vector<GraphEdge>& ret)
{
	visted[sourceIndex] = Color::BLACK;
	for (const auto& adj : adjList[sourceIndex])
	{
		if (visted[adj.destiny] == Color::WHITE)
		{
			ret.emplace_back(sourceIndex, adj.destiny, 0);
			timeCounter++;
			DFSRecursive(adj.destiny, ret);
		}
	}
	timeCounter++;
	timeFinishedIndex[sourceIndex] = { timeCounter, sourceIndex};
}

void Graph::DFSRecursive(std::size_t sourceIndex, std::vector<std::size_t>& ret)
{
	visted[sourceIndex] = Color::BLACK;
	ret.emplace_back(sourceIndex);
	for (const auto& adj : adjList[sourceIndex])
	{
		if (visted[adj.destiny] == Color::WHITE)
		{
			DFSRecursive(adj.destiny, ret);
		}
	}
}

void Graph::DFSRecursive(size_t sourceIndex)
{
	visted[sourceIndex] = Color::BLACK;
	for (const auto& adj : adjList[sourceIndex])
	{
		if (visted[adj.destiny] == Color::WHITE)
		{
			timeCounter++;
			DFSRecursive(adj.destiny);
		}
	}
	timeCounter++;
	timeFinishedIndex[sourceIndex] = { timeCounter, sourceIndex };
}

bool Graph::DFSRecursiveVerifyCicle(std::size_t sourceIndex)
{
	visted[sourceIndex] = Color::BLACK;
	for (const auto& adj : adjList[sourceIndex])
	{
		if (visted[adj.destiny] == Color::WHITE)
		{
			return DFSRecursiveVerifyCicle(adj.destiny);
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
		if (visted[adj.destiny] == Color::WHITE)
			DFSTopologicalSort(adj.destiny, ret);
		
	}
	ret.push( sourceIndex);
}

void Graph::AddEdges(std::size_t source, std::size_t destination, float weight)
{
	adjList.at(source).push_back({destination, weight});
}

void Graph::AddEdgesToEdgeList(std::size_t source, std::size_t destination, float weight)
{
	edgeList.emplace_back(source, destination, weight);
}
