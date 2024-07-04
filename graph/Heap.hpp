#pragma once
#include <vector>
#include <algorithm>
#include <ranges>
#include <type_traits>
//TODO: Se how to use requieres

template<typename T>
class Heap
{
private:
	std::vector<T>& data;
	bool isMinHeap;
public:
	//Build a heap data structure, if you want a min heap, use 'true' in the second argument
	Heap(std::vector<T>& d, bool isMinHeap) //requires std::is_arithmetic<T>
		: data{d}, isMinHeap{isMinHeap}
	{
		(isMinHeap) ? std::ranges::make_heap(data, std::greater<>{}) : std::ranges::make_heap(data);
	}

	~Heap() = default;

	void AddElement(T e) //requires std::is_arithmetic<T>
	{
		data.push_back(e);
		(isMinHeap) ? std::ranges::push_heap(data, std::greater<>{}) : std::ranges::push_heap(data);
	}

	void Pop()
	{
		(isMinHeap) ? std::ranges::pop_heap(data, std::greater<>{}) : std::ranges::pop_heap(data);
		data.pop_back();
	}

	void Update()
	{
		(isMinHeap) ? std::ranges::make_heap(data, std::greater<>{}) : std::ranges::make_heap(data);
	}
	T Top() { return data[0]; }

	bool Empty() { return data.empty(); }
};

