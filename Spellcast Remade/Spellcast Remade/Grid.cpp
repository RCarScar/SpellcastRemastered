#include <iostream>
#include "Grid.h"

bool HasSpecChar(std::string& mString)
{
	for (auto a : mString)
	{
		char myLetter = std::tolower(a);
		if (myLetter < 97 || myLetter > 122)
			return true;
	}
	return false;
}

void StringToLower(std::string &mString)
{
	for (auto& a : mString)
	{
		a = std::tolower(a);
	}
}

Grid::Grid()
{
	letterPoints['a'] = 1;
	letterPoints['b'] = 4;
	letterPoints['c'] = 5;
	letterPoints['d'] = 3;
	letterPoints['e'] = 1;
	letterPoints['f'] = 5;
	letterPoints['g'] = 1;
	letterPoints['h'] = 4;
	letterPoints['i'] = 1;
	letterPoints['j'] = 7;
	letterPoints['k'] = 6;
	letterPoints['l'] = 3;
	letterPoints['m'] = 4;
	letterPoints['n'] = 2;
	letterPoints['o'] = 1;
	letterPoints['p'] = 4;
	letterPoints['q'] = 8;
	letterPoints['r'] = 2;
	letterPoints['s'] = 2;
	letterPoints['t'] = 2;
	letterPoints['u'] = 8;
	letterPoints['v'] = 5;
	letterPoints['w'] = 5;
	letterPoints['x'] = 7;
	letterPoints['y'] = 4;
	letterPoints['z'] = 8;
}

void Grid::InputLetters()
{
	do
	{
		if (HasSpecChar(mInput))
			std::cout << "Do not include any special characters!" << std::endl;
		std::cout << "Please input 25 letters in a row. No spaces. No special characters. Previous Letter count: " << mInput.size() << std::endl;
		std::cin >> mInput;
		StringToLower(mInput);
	} while (mInput.size() != 25 || HasSpecChar(mInput));
}

void Grid::CreateGrid()
{
	// If the string is not 25 characters, just straight up leave.
	if (mInput.size() != 25)
	{
		std::cout << "String is too short! Characters: " << mInput.size();
		return;
	}
	// Set all 25 nodes.
	for (auto i : mInput)
	{
		// Takes the letter, inserts it into a new node
		Node* currNode = new Node(i);

		grid.push_back(currNode);

		// If the letter is new to the letter node dictionary, make a new spot for it and insert the new node into the list.
		IfMapMissingAdd(i, currNode, letterNodeMap);
	}
}

void Grid::CreateGrid(std::string forcedInput)
{
	mInput = forcedInput;
	// If the string is not 25 characters, just straight up leave.
	if (mInput.size() != 25)
	{
		std::cout << "String is too short! Characters: " << mInput.size();
		return;
	}
	// Set all 25 nodes.
	for (auto i : mInput)
	{
		// Takes the letter, inserts it into a new node
		Node* currNode = new Node(i);

		grid.push_back(currNode);

		// If the letter is new to the letter node dictionary, make a new spot for it and insert the new node into the list.
		IfMapMissingAdd(i, currNode, letterNodeMap);
	}
}

void Grid::Display()
{
	for (int i = 0; i < 25; i++)
	{
		if (i % 5 == 0)
		{
			std::cout << std::endl << "| ";
		}
		std::cout << grid[i]->letter.value() << " | ";
	}

	std::cout << std::endl << std::endl;

	for (int i = 0; i < 25; i++)
	{
		std::cout << "Node " << i << " contains: " << std::endl;
		std::unordered_map<char, std::vector<Node*>> myAdjList = grid[i]->adjList;
		for (auto& [_, node] : myAdjList | std::views::reverse)
		{
			for (int j = 0; j < node.size(); j++)
			{
				std::cout << " - " << node[j]->letter.value() << std::endl;
			}
		}
	}
	std::cout << std::endl << std::endl;
}

void Grid::NodeTraversal(Node *mNode, std::string currWord, unsigned i, std::unordered_set<Node*> pathway)
{
	if (i == currWord.length() - bonusAm)
	{
		if (done.find(currWord) == done.end())
		{
			done.insert(currWord);
		}
		return;
	}
	if (currWord[i] != mNode->letter.value())
	{
		return;
	}

	if (pathway.find(mNode) == pathway.end())
		pathway.insert(mNode);

	// adjNodes the pointer to adjacent list the unordered map. The unordered map to the string at position i.
	for (auto& [_, word] : mNode->adjList | std::views::reverse)
	{
		for (auto j : word)
		{
			if (pathway.find(j) != pathway.end())
				continue;
			NodeTraversal(j, currWord, i + 1, pathway);
		}
	}
}

void Grid::HashAdjacent()
{
	for (int i = 0; i < 25; i++)
	{
		// This is literally the point you are currently at.
		int startPos = i - 6;

		// Fuck this shit
		std::optional<char> aBound1 = 0, aBound2 = 0;
		std::optional<char> bBound1 = 0, bBound2 = 0;
		std::optional<char> cBound1 = 0, cBound2 = 0;

		// Set the bounds for the 3 rows being checked.
		int tempRow = (int)std::floor((((float)i - 5) / 5));
		aBound1 = tempRow * 5;
		aBound2 = aBound1.value() + 4;

		tempRow = (int)std::floor(((float)i / 5));
		bBound1 = tempRow * 5;
		bBound2 = bBound1.value() + 4;

		tempRow = (int)std::floor((((float)i + 5) / 5));
		cBound1 = tempRow * 5;
		cBound2 = cBound1.value() + 4;

		// Ex Case: i = 0; -5 < 0, aBound1 & aBound2 ignored; cBound1 = 5, cBound2 = 9

		// If out of bounds, remove the row from the grid calculator.
		if (i - 5 < 0)
			aBound1 = std::nullopt;
		if (i + 5 > 24)
			cBound1 = std::nullopt;

		for (int j = 0; j < 3; j++)
		{
			int currBounds1 = 0, currBounds2 = 0;
			// If this current row is denied
			switch (j)
			{
			case 0:
				if (aBound1 == std::nullopt)
					continue;
				currBounds1 = aBound1.value();
				currBounds2 = aBound2.value();
				break;
			case 2:
				if (cBound1 == std::nullopt)
					continue;
				currBounds1 = cBound1.value();
				currBounds2 = cBound2.value();
				break;
			case 1:
				currBounds1 = bBound1.value();
				currBounds2 = bBound2.value();
				break;
			default:
				break;
			}
			for (int buhpuhmuhfuh = 0; buhpuhmuhfuh < 3; buhpuhmuhfuh++)
			{
				// The updated position in the 9x9 centered around i.
				int currPos = startPos + buhpuhmuhfuh + (5 * j);

				// If it isn't within the current set bounds, continue;
				if (currPos < currBounds1 || currPos > currBounds2 || currPos == i)
					continue;

				// If a valid position, add the Node at currPos.
				std::unordered_map<char, std::vector<Node*>>* myAdjList = &grid[i]->adjList;
				Node* currNode = grid[currPos];
				IfMapMissingAdd(currNode->letter.value(), currNode, *myAdjList);
			}
		}
	}
}

void Grid::HashWords()
{
	// Open the json dictionary file
	std::ifstream file("words_dictionary.json");
	Json::Value jsonData;
	Json::Reader jsonReader;

	// The data is now in jsonData.
	jsonReader.parse(file, jsonData);

	// If there's an error, don't even do anything.
	if (!file.is_open()) {
		std::cerr << "Error opening JSON file." << std::endl;
		while (true) {}
	}

	int removedCount = 0;

	// Assign the JSON info.
	for (auto i : jsonData.getMemberNames())
	{
		bool problem = false;
		// Add every word to a map of their length.
		std::string mWord = i;

		// Ignore this word if 1. It's longer than 25 letters, 2. It has a letter not in the grid.
		if (mWord.size() >= 26 || mWord.size() <= 3)
		{
			removedCount++;
			continue;
		}
		for (char myChar : mWord)
		{
			if (letterNodeMap.find(myChar) == letterNodeMap.end())
			{
				problem = true;
				break;
			}
		}
		if (problem == true)
		{
			// std::cout << i << " has been expelled from Hogwarts." << std::endl;
			removedCount++;
			continue;
		}

		int myLen = (int)mWord.length();
		if (lenMap.find(myLen) == lenMap.end())
			lenMap[myLen] = WordList();
		lenMap[myLen].myWords.push_back(mWord);
	}
	std::cout << std::endl << "Dictionary Metrics: " << std::endl << "Starting Data Count: " << jsonData.size() << std::endl;
	std::cout << "Removed Words: " << removedCount << std::endl;
	std::cout << "Words Remaining: " << (jsonData.size() - removedCount) << std::endl;
}

void Grid::TraverseGraph()
{
	#pragma region PrintLetterWordList
		/*for (auto& [_, word] : lenMap | std::views::reverse) {

			for (int j = 0; j < word.myWords.size(); j++)
			{
				std::cout << word.myWords[j] << std::endl;
			}
		}*/
		/*for (auto& [_, word] : letterNodes | std::views::reverse) {

			for (int j = 0; j < word.size(); j++)
			{
				char myLetter = word[j]->letter.value();
				std::cout << myLetter << std::endl;
			}
		}*/
	#pragma endregion

	std::cout << std::endl << std::endl << "Answers: " << std::endl << std::endl;
	for (auto& [_, word] : lenMap | std::views::reverse) {
		for (int j = 0; j < word.myWords.size(); j++)
		{
			std::string currW = word.myWords[j];
			Node* lastNode = NULL;
			std::unordered_set<Node*> pathway = std::unordered_set<Node*>();
			for (Node* node : letterNodeMap.at(currW[0]))
			{
				NodeTraversal(node, currW, 0, pathway);
			}
		}
	}
}

bool Grid::TryGetValue()
{
	return false;
}

template<class T, class U>
void Grid::IfMapMissingAdd(T element, U* myElm, std::unordered_map<T, std::vector<U*>>& thisMap)
{
	if (thisMap.find(element) == thisMap.end())
	{
		std::pair <T, std::vector<U*>> temp = std::make_pair(element, std::vector<U*>());
		temp.second.push_back(myElm);
		thisMap.insert(temp);
	}
}
