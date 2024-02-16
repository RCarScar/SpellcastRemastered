#pragma once
#include <optional>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <json/value.h>
#include <json/json.h>
#include <ranges>
#include "WordList.h"
#include "Node.h"

class Grid
{
public:
	template<class T, class U>
	void IfMapMissingAdd(T element, U* myElm, std::unordered_map<T, std::vector<U*>>& thisMap);

	Grid();
	void CreateGrid();
	void CreateGrid(std::string forcedInput);
	void Display();
	void NodeTraversal(Node* mNode, std::string currWord, unsigned i, std::unordered_set<Node*> pathway);
	void HashAdjacent();
	void HashWords();
	void TraverseGraph();
	void InputLetters();
	bool TryGetValue();

	bool bonus = false;
	short unsigned bonusAm = 0;

	std::string mInput;

	// Grid is the 5x5 node list containing all letters in a 1D Fashion.
	std::vector<Node*> grid;

	// lenMap contains the length of the word and then the word respectively.
	std::map<int, WordList> lenMap;

	// containedLetters contains literally just all letters that occur in the string.
	std::unordered_set<char> containedLetters;

	// Map the letter to each known node on the grid.
	std::unordered_map<char, std::vector<Node*>> letterNodeMap;

	// Map the character to the point it has.
	std::unordered_map<char, int> letterPoints;

	// Map the points to the word. This is sorted by ascending order.
	std::map<int, std::string> wordPoints;

	// Words done
	std::unordered_set<std::string> done;
};