#pragma once
#include <optional>
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
#include <algorithm>
#include <future>
#include <filesystem>
#include "DictionaryMetrics.h"

class Grid
{
public:

	Grid();
	void CreateGrid();
	void StringToLower(std::string& mString);
	void Display();
	void NodeTraversal(Node* mNode, std::string currWord, unsigned i, std::unordered_set<Node*> pathway, int multiplier, std::vector<int> applied);
	void HashAdjacent();
	void HashWords();
	void TraverseGraph();
	void InputLetters();
	void InputLetters(std::string forcedInput, char mBonus = 'n');
	void LinkPoints();
	bool TryGetValue();
	void RefreshLockFiles();
	DictionaryMetrics ThroughFiles(std::string lockPath, std::string fileName);
	void JsonToThreads(int fileCount = 370);
	~Grid();

	bool bonus = false;
	short unsigned bonusAm = 0;
	std::optional<int> doubleLocation = std::nullopt;
	std::optional<int> tripleLocation = std::nullopt;
	std::optional<int> fullLetLocation = std::nullopt;

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
	std::map<int, std::vector<std::string>> wordPoints;

	// Words done
	std::unordered_set<std::string> done;

	std::unordered_map<std::string, std::vector<int>> multipliers;

	Node* secPos = NULL;
	Node* thirdPos = NULL;
	Node* fullLet = NULL;
};