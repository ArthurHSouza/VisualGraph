#pragma once
#include <vector>
#include <forward_list>
#include <memory>
#include "EdgeShape.hpp"
#include "NodeCircle.hpp"
#include "Graph.hpp"
#include "VisualText.hpp"

namespace gh
{
	void BFS(const size_t sourceIndex, std::vector<NodeCircle>& nodes, std::forward_list<std::shared_ptr<EdgeShape>>& edges);
	void DFS(const size_t sourceIndex, std::vector<NodeCircle>& nodes, std::forward_list<std::shared_ptr<EdgeShape>>& edges);
	void TopologicalSort(std::vector<NodeCircle>& nodes, const std::forward_list<std::shared_ptr<EdgeShape>>& edges);
	void SCC(std::vector<NodeCircle>& nodes, const std::forward_list<std::shared_ptr<EdgeShape>>& edges);
	void ShortestPath(const size_t sourceIndex, std::vector<NodeCircle>& nodes, std::forward_list<std::shared_ptr<EdgeShape>>& edges);
	void MinimumST(std::vector<NodeCircle>& nodes, std::forward_list<std::shared_ptr<EdgeShape>>& edges);
}