#pragma once
#include <optional>
#include <iostream>
#include <vector>
#include <unordered_map>

class Node
{
public:
	Node()
	{
		letter = std::nullopt;
	}
	Node(char m_Letter)
	{
		letter = m_Letter;
	}
	std::unordered_map<char, std::vector<Node*>> adjList = std::unordered_map<char, std::vector<Node*>>();
	std::optional<char> letter;
private:
};