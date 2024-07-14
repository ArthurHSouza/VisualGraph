#include "GraphHandler.hpp"

namespace gh
{
	void BFS(const size_t sourceIndex, std::vector<NodeCircle>& nodes, std::forward_list<std::shared_ptr<EdgeShape>>& edges)
	{
		Graph g = Graph(nodes.size());
		for (const auto& e : edges)
		{
			g.AddEdges(e->GetBeginingIndex(), e->GetEndIndex());
		}
		auto result = g.BFS(sourceIndex);

		nodes.at(sourceIndex).AddText("Source");
		nodes.at(sourceIndex).FillOutlineWithDefinedColor(SelectableVisualObject::DefinedColor::SelectedColor);

		for (const auto& r : result)
		{
			for (const auto& e : edges)
			{
				if (e->GetBeginingIndex() == r.origin && e->GetEndIndex() == r.destiny)
				{
					e->FillWithDefinedColor(SelectableVisualObject::DefinedColor::SelectedColor);
				}
			}

			nodes.at(r.destiny).AddText(std::to_string((int)r.weight));
		}
	}

	void DFS(const size_t sourceIndex, std::vector<NodeCircle>& nodes, std::forward_list<std::shared_ptr<EdgeShape>>& edges)
	{
		Graph g = Graph(nodes.size());
		for (const auto& e : edges)
		{
			g.AddEdges(e->GetBeginingIndex(), e->GetEndIndex());
		}
		auto result = g.DFS(0);

		for (const auto& r : result)
		{
			for (const auto& e : edges)
			{
				if (e->GetBeginingIndex() == r.origin && e->GetEndIndex() == r.destiny)
				{
					e->FillWithDefinedColor(SelectableVisualObject::DefinedColor::SelectedColor);
				}
			}
		}

		nodes.at(sourceIndex).AddText("Source");
		nodes.at(sourceIndex).FillOutlineWithDefinedColor(SelectableVisualObject::DefinedColor::SelectedColor);
	}

	void TopologicalSort(std::vector<NodeCircle>& nodes, const std::forward_list<std::shared_ptr<EdgeShape>>& edges)
	{
		Graph g = Graph(nodes.size());
		for (const auto& e : edges)
		{
			g.AddEdges(e->GetBeginingIndex(), e->GetEndIndex());
		}
		auto result = g.TopologicalSort();
		if (result.empty())
			std::cout << "NO TOPOLOGICAL SORT FOUND\n";
		int order = 0;
		for (std::size_t i = result.size(); i > 0; i--)
		{
			nodes.at(result.top()).AddText(std::to_string(order++));
			result.pop();
		}
	}

	void SCC(std::vector<NodeCircle>& nodes, const std::forward_list<std::shared_ptr<EdgeShape>>& edges)
	{
		Graph g = Graph(nodes.size());
		for (const auto& e : edges)
		{
			g.AddEdges(e->GetBeginingIndex(), e->GetEndIndex());
		}
		auto result = g.KosarujoSSC();
		if (result.empty())
			std::cout << "NO SCC FOUND\n";
		auto colors = { ColorPallet::darkBlue, ColorPallet::celestBlue, ColorPallet::carminRed, ColorPallet::wineRed };
		int idGroup = 0;
		for (const auto& r : result)
		{
			for (const auto& n : r)
			{
				nodes.at(n).FillWithColor(*(colors.begin() + idGroup));
				nodes.at(n).AddText(std::to_string(idGroup));
			}
			idGroup++;
		}
	}

	void ShortestPath(const size_t sourceIndex, std::vector<NodeCircle>& nodes, std::forward_list<std::shared_ptr<EdgeShape>>& edges)
	{
		Graph g = Graph(nodes.size());
		bool willBeDijkstra = true;
		for (const auto& e : edges)
		{
			g.AddEdges(e->GetBeginingIndex(), e->GetEndIndex(), e->GetWeight());
			if (e->GetWeight() < 0)
				willBeDijkstra = false;
		}
		std::vector<GraphEdge> result;
		if (willBeDijkstra)
		{
			result = g.Dijkstra(sourceIndex);
		}
		else
		{
			for (const auto& e : edges)
			{
				g.AddEdgesToEdgeList(e->GetBeginingIndex(), e->GetEndIndex(), e->GetWeight());
			}
			result = g.BellmanFord(0);
		}
		for (const auto& r : result)
		{
			for (const auto& e : edges)
			{
				if (e->GetBeginingIndex() == r.origin && e->GetEndIndex() == r.destiny)
				{
					e->FillWithDefinedColor(SelectableVisualObject::DefinedColor::SelectedColor);
				}
			}
			nodes.at(r.destiny).FillOutlineWithDefinedColor(SelectableVisualObject::DefinedColor::SelectedColor);
			nodes.at(r.destiny).AddText(std::to_string(r.weight).substr(0, 5));
		}
		nodes.at(sourceIndex).AddText("Source");
	}

	void MinimumST(std::vector<NodeCircle>& nodes, std::forward_list<std::shared_ptr<EdgeShape>>& edges)
	{
		Graph g = Graph(nodes.size());
		for (const auto& e : edges)
		{
			g.AddEdges(e->GetBeginingIndex(), e->GetEndIndex(), e->GetWeight());
		}
		auto result = g.PrimMST();

		for (const auto& r : result)
		{
			for (const auto& e : edges)
			{
				if (e->GetBeginingIndex() == r.origin && e->GetEndIndex() == r.destiny ||
					e->GetBeginingIndex() == r.destiny && e->GetEndIndex() == r.origin)
				{
					e->FillWithDefinedColor(SelectableVisualObject::DefinedColor::SelectedColor);
				}
			}
			nodes.at(r.destiny).FillOutlineWithDefinedColor(SelectableVisualObject::DefinedColor::SelectedColor);
		}
	}
}