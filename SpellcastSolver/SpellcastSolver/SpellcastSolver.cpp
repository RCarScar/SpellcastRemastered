/*
	This script was written for fun on 2/10/24
	The basic idea for this script is still in the workings but there's a few ways to do this graph traversal.
	You want to sling together the longest word in a graph of 25 adjacently connected letters in a 5x5 grid.
	There's a point system that is assigned seemingly logically, not completely sure but vowels are worth less,
	there is a 2x point letter that spawns randomly, I have plans to account for this but it will be tough nonetheless.
	The current strategy is to find the longest words and check if 1. Their letters are in the grid, 2. Check if all letters are
	adjacent, the plan is to use breadth-first search. The time complexity is O(FUCKING LO(n)g), it'll definietly
	take a lot of optimization and learning.
*/
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

class Done
{
public:
	Done()
	{
		done = std::unordered_set<std::string>();
	}
	std::unordered_set<std::string> done;
};

class WordList
{
public:
	std::vector<std::string> myWords = std::vector<std::string>();
private:
};

void GetLetters(std::string& mInput, std::unordered_set<char>& mLetters, bool &bonus, int& bonusFac);
void LetterstoGrid(std::vector<Node*>& mGrid, const std::string mInput, std::unordered_map<char, std::vector<Node*>>& letterNodes);
void DisplayGrid(const std::vector<Node*> mGrid);
void NoderTheExplorer(Node* currNode, std::string, unsigned index, Done &mdone, std::unordered_set<Node*> trackPath, const bool bonus, const int factor);
void HookUpAdjacent(std::vector<Node*>& mGrid);
void HashWords(std::map<int, WordList>& lenMap, const std::unordered_set<char> letterList);
void TraverseGraph(const std::map<int, WordList> lenMap, const std::unordered_map<char, std::vector<Node*>> letterNodes, const bool bonus, const int factor);
bool TryGetValue(Node* thisNode, char target, const std::unordered_map<char, std::vector<Node*>> myMap, const bool bonus);
void IfDictMissingAdd(char value, Node* element, std::unordered_map<char, std::vector<Node*>>* myDict);

int main()
{
	while (true)
	{
		bool bonus = false;
		int bonusAm = 0;

		// Grid is the 5x5 node list containing all letters in a 1D Fashion.
		std::vector<Node*> grid = std::vector<Node*>();

		// lenMap contains the length of the word and then the word respectively.
		std::map<int, WordList> lenMap = std::map<int, WordList>();

		// containedLetters contains literally just all letters that occur in the string.
		std::unordered_set<char> containedLetters = std::unordered_set<char>();

		// Map the letter to each known node on the grid.
		std::unordered_map<char, std::vector<Node*>> letterNodes = std::unordered_map<char, std::vector<Node*>>();
		// Get the letters first.
		// Grid Input & Manipulation
		std::string mInput;
		GetLetters(mInput, containedLetters, bonus, bonusAm);
		LetterstoGrid(grid, mInput, letterNodes);
		HookUpAdjacent(grid);
		DisplayGrid(grid);

		// JSON Lenmap Setup
		HashWords(lenMap, containedLetters);

		// Big Shit
		TraverseGraph(lenMap, letterNodes, bonus, bonusAm);

		for (auto i : grid)
			delete i;
	}

	return 0;
}

void TraverseGraph(const std::map<int, WordList> lenMap, const std::unordered_map<char, std::vector<Node*>> letterNodes,const bool bonus, const int factor)
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
	Done medone = Done();
	for (auto& [_, word] : lenMap | std::views::reverse) {
		for (int j = 0; j < word.myWords.size(); j++)
		{
			std::string currW = word.myWords[j];
			Node* lastNode = NULL;
			std::unordered_set<Node*> AIDS = std::unordered_set<Node*>();
			for (Node* node : letterNodes.at(currW[0]))
			{
				NoderTheExplorer(node, currW, 0, medone, AIDS, bonus, factor);
			}
		}
	}
}

/*








			for (int i = 0; i < currW.length() - 1; i++)
			{
				// For every letter in the word, find the corresponding Node map.
				char currentLetter = currW[i];
				std::vector<Node*> myNodes = letterNodes.at(currentLetter);
				for (int j = 0; j < myNodes.size(); j++)
				{
					// You have the vector of nodes. Check each nodes' adjacency list to see if it contains the next letter.
					std::unordered_map<char, std::vector<Node*>> myAdjNodes = myNodes[j]->adjList;

					for (auto k : myAdjNodes[currW[i]])
					{
						NoderTheExplorer(k);
					}
				}
				if (!perfect)
					break;
			}*/

void NoderTheExplorer(Node* currNode, std::string t, unsigned i, Done &mdone, std::unordered_set<Node*> trackPath, const bool bonus, const int factor)
{
	if (i == t.length() - factor)
	{
		if (mdone.done.find(t) == mdone.done.end())
		{
			std::cout << t << std::endl;
			mdone.done.insert(t);
		}
		return;
	}
	if (t[i] != currNode->letter.value())
	{
		return;
	}

	if (trackPath.find(currNode) == trackPath.end())
		trackPath.insert(currNode);

	// adjNodes the pointer to adjacent list the unordered map. The unordered map to the string at position i.
	for (auto& [_, word] : currNode->adjList | std::views::reverse)
	{
		for (auto j : word)
		{
			if (trackPath.find(j) != trackPath.end())
				continue;
			NoderTheExplorer(j, t, i + 1, mdone, trackPath, bonus, factor	);
		}
	}
}

void HashWords(std::map<int, WordList>& lenMap, const std::unordered_set<char> letterList)
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
		while(true) { }
	}

	int removedCount = 0;

	// Assign the JSON info.
	for (auto i : jsonData.getMemberNames())
	{
		bool problem = false;
		// Add every word to a map of their length.
		std::string mWord = i;

		// Ignore this word if 1. It's longer than 25 letters, 2. It has a letter not in the grid.
		if (mWord.size() >= 26 || mWord.size() <= 5)
		{
			removedCount++;
			continue;
		}
		for (char myChar : mWord)
		{
			if (letterList.find(myChar) == letterList.end())
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

void HookUpAdjacent(std::vector<Node*>& mGrid)
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
				std::unordered_map<char, std::vector<Node*>> *myAdjList = &mGrid[i]->adjList;
				Node* currNode = mGrid[currPos];
				IfDictMissingAdd(currNode->letter.value(), currNode, myAdjList);
			}
		}
	}
}

#pragma region GeneralPurpose
bool TryGetValue(Node* thisNode, char target, const std::unordered_map<char, std::vector<Node*>> myMap)
{
	// If the target exists within the dictionary
	if (myMap.find(target) == myMap.end())
		return false;

	// Set the referenced node to the map-found at target.
	thisNode = myMap.at(target)[0];

	return true;
}

void IfDictMissingAdd(char value, Node* element, std::unordered_map<char, std::vector<Node*>> *myDict)
{
	// If the dictionary doesn't contain the value,
	if (myDict->find(value) == myDict->end())
	{
		// Form a new pair, push the new element into the list, and then push that pair to the dictionary
		std::vector<Node*> newV = std::vector<Node*>();
		std::pair<char, std::vector<Node*>> myP = std::make_pair(value, newV);
		myP.second.push_back(element);
		myDict->insert(myP);
	}
	else
	{
		// If the element exists, just push it to the back.
		myDict->at(value).push_back(element);
	}
}
#pragma endregion

#pragma region Display
void DisplayGrid(const std::vector<Node*> mGrid)
{
	for (int i = 0; i < 25; i++)
	{
		if (i % 5 == 0)
		{
			std::cout << std::endl << "| ";
		}
		std::cout << mGrid[i]->letter.value() << " | ";
	}
	std::cout << std::endl << std::endl;
	for (int i = 0; i < 25; i++)
	{
		std::cout << "Node " << i << " contains: " << std::endl;
		std::unordered_map<char, std::vector<Node*>> myAdjList = mGrid[i]->adjList;
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
#pragma endregion

void LetterstoGrid(std::vector<Node*> &mGrid, const std::string mInput, std::unordered_map<char, std::vector<Node*>> &letterNodes)
{
	// If the string is less than 25 characters, just straight up leave.
	if (mInput.size() != 25)
	{
		std::cout << "String is too short! Characters: " << mInput.size();
		return;
	}
	// Set all 25 nodes.
	for (int i = 0; i < 25; i++)
	{
		// Takes the letter, inserts it into a new node
		char letter = mInput[i];
		Node *currNode = new Node(letter);
		
		mGrid.push_back(currNode);
		
		// If the letter is new to the letter node dictionary, make a new spot for it and insert the new node into the list.
		if (letterNodes.find(letter) == letterNodes.end())
		{
			// Makes a Node pointer list, and adds the new letter Node.
			std::vector<Node*> newList = std::vector<Node*>();
			newList.push_back(currNode);

			// Inserts the new letter and 
			std::pair<char, std::vector<Node*>> mP = std::make_pair(letter, newList);
			letterNodes.insert(mP);
			continue;
		}
		letterNodes[letter].push_back(currNode);
	}
}

#pragma region Input
void GetLetters(std::string& mInput, std::unordered_set<char>& letters, bool &bonus, int &bonusFac)
{
	int containsSpecialChar = 0;
	do
	{
		containsSpecialChar = 0;
		std::cout << "Please input 25 letters in a row. No spaces. No special characters. Letter count: " << mInput.size() << std::endl;
		std::cin >> mInput;
		for (int i = 0; i < mInput.length(); i++)
		{
			char myLetter = std::tolower(mInput[i]);
			if (myLetter < 97 || myLetter > 122)
			{
				containsSpecialChar = 1;
			}
		}
		if (containsSpecialChar == 1)
			std::cout << "Do not include any special characters!" << std::endl;
	} while (mInput.size() != 25 || containsSpecialChar == 1);
	
	char ans = ' ';
	do
	{
		std::cout << "Bonus? Y/N" << std::endl;
		std::cin >> ans;
		ans = std::tolower(ans);
	} while (ans != 'y' && ans != 'n');

	if(ans == 'y')
	{
		do
		{
			std::cout << "Swap Count? " << std::endl;
			std::cin >> bonusFac;
		} while (bonusFac < 0 || bonusFac > 3);
	}

	if (ans == 'y')
		bonus = true;
	else
		bonus = false;

	// If the letter hasn't been seen yet, add it to the list of letters.
	for (char myChar : mInput)
	{
		if (letters.find(myChar) == letters.end())
		{
			letters.insert(myChar);
		}
	}
}
#pragma endregion