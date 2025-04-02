#include "Grid.h"

template<class T, class U>
void IfMapMissingAdd(T element, U myElm, std::map<T, std::vector<U>>& thisMap)
{
	if (thisMap.find(element) == thisMap.end())
	{
		std::pair <T, std::vector<U>> temp = std::make_pair(element, std::vector<U>());
		temp.second.push_back(myElm);
		thisMap.insert(temp);
	}
	else
	{
		thisMap.at(element).push_back(myElm);
	}
}

template<class T, class U>
void IfMapMissingAdd(T element, U myElm, std::unordered_map<T, std::vector<U>>& thisMap)
{
	if (thisMap.find(element) == thisMap.end())
	{
		std::pair <T, std::vector<U>> temp = std::make_pair(element, std::vector<U>());
		temp.second.push_back(myElm);
		thisMap.insert(temp);
	}
	else
	{
		thisMap.at(element).push_back(myElm);
	}
}

template<class T, class U>
void IfMapMissingAdd(T element, U* myElm, std::unordered_map<T, std::vector<U*>>& thisMap)
{
	if (thisMap.find(element) == thisMap.end())
	{
		std::pair <T, std::vector<U*>> temp = std::make_pair(element, std::vector<U*>());
		temp.second.push_back(myElm);
		thisMap.insert(temp);
	}
	else
	{
		thisMap.at(element).push_back(myElm);
	}
}

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

void Grid::StringToLower(std::string &mString)
{
	std::string tmpString = "";
	int offset = 1;
	for (int i = 0; i < mString.length(); i++)
	{
		if (mString[i] == '2')
		{
			doubleLocation = i - offset;
			offset++;
			if (i == mString.length() - 1)
				break;
			continue;
		}
		if (mString[i] == '3')
		{
			tripleLocation = i - offset;
			offset++;
			if (i == mString.length() - 1)
				break;
			continue;
		}
		if (mString[i] == '4')
		{
			fullLetLocation = i - offset;
			offset++;
			if (i == mString.length() - 1)
				break;
			continue;
		}
		tmpString += std::tolower(mString[i]);
	}
	mString = tmpString;
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
	letterPoints['u'] = 4;
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
		std::cout << "Please input 25 letters in a row. No spaces. No special characters. If there's a triple or double, put a 2/3 to the right of it. If there's a 2x word, put a 4 to the right of the letter with it. Previous Letter count: " << mInput.size() << std::endl;
		std::cin >> mInput;
		StringToLower(mInput);
	} while (mInput.size() != 25 || HasSpecChar(mInput));

	char ans = ' ';
	do
	{
		std::cout << "Bonus? Y/N" << std::endl;
		std::cin >> ans;
		ans = std::tolower(ans);
	} while (ans != 'y' && ans != 'n');

	if (ans == 'y')
	{
		do
		{
			std::cout << "Swap Count? " << std::endl;
			std::cin >> bonusAm;
		} while (bonusAm < 0 || bonusAm > 3);
	}

	if (ans == 'y')
		bonus = true;
	else
		bonus = false;

	// If the letter hasn't been seen yet, add it to the list of letters.
	for (char myChar : mInput)
	{
		if (containedLetters.find(myChar) == containedLetters.end())
		{
			containedLetters.insert(myChar);
		}
	}
}
void Grid::InputLetters(std::string forcedInput, char mBonus)
{
	mInput = forcedInput;
	StringToLower(mInput);
	while (mInput.size() != 25 || HasSpecChar(mInput))
	{
		if (HasSpecChar(mInput))
			std::cout << "Do not include any special characters!" << std::endl;
		std::cout << "Please input 25 letters in a row. No spaces. No special characters. If there's a triple or double, put a 2/3 to the right of it. If there's a 2x word, put a 4 to the right of the letter with it. Previous Letter count: " << mInput.size() << std::endl;
		std::cin >> mInput;
		StringToLower(mInput);
	} 

	char ans = mBonus;
	ans = std::tolower(ans);
	while (ans != 'y' && ans != 'n')
	{
		std::cout << "Bonus? Y/N" << std::endl;
		std::cin >> ans;
		ans = std::tolower(ans);
	} 

	if (ans == 'y')
	{
		do
		{
			std::cout << "Swap Count? " << std::endl;
			std::cin >> bonusAm;
		} while (bonusAm < 0 || bonusAm > 3);
	}

	if (ans == 'y')
		bonus = true;
	else
		bonus = false;

	// If the letter hasn't been seen yet, add it to the list of letters.
	for (char myChar : mInput)
	{
		if (containedLetters.find(myChar) == containedLetters.end())
		{
			containedLetters.insert(myChar);
		}
	}
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

	if (doubleLocation != std::nullopt)
		secPos = grid[doubleLocation.value()];
	if (tripleLocation != std::nullopt)
		thirdPos = grid[tripleLocation.value()];
	if (fullLetLocation != std::nullopt)
		fullLet = grid[fullLetLocation.value()];
}

void Grid::LinkPoints()
{
	for (const auto& elem : done)
	{
		int myTotal = 0;
		for (const auto letter : elem)
		{
			myTotal += letterPoints.at(letter);
		}
		if (multipliers.find(elem) != multipliers.end())
		{
			std::vector<int>::iterator ip;
			std::sort(multipliers.at(elem).begin(), multipliers.at(elem).end());
			ip = std::unique(multipliers.at(elem).begin(), multipliers.at(elem).end());
			multipliers.at(elem).resize(std::distance(multipliers.at(elem).begin(), ip));
			for (auto multies : multipliers.at(elem))
			{
				std::cout << elem << " has a multiplier of " << multies << std::endl;
				switch (multies)
				{
				case 1:
					break;
				case 2:
					if (doubleLocation != std::nullopt)
					{
						myTotal += letterPoints[grid[doubleLocation.value()]->letter.value()];
					}
					break;
				case 3:
					if (tripleLocation != std::nullopt)
					{
						myTotal += letterPoints[grid[tripleLocation.value()]->letter.value()] + letterPoints[grid[tripleLocation.value()]->letter.value()];
					}
					break;
				case 4:
					if (fullLetLocation != std::nullopt)
					{
						myTotal *= 2;
					}
					break;
				}
			}
		}
		IfMapMissingAdd(myTotal, elem, wordPoints);
	}
	for (auto& [total, wordList] : wordPoints)
	{
		for (auto word : wordList)
		{
			std::cout << total << " - " << word << std::endl;
		}
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

	/*for (int i = 0; i < 25; i++)
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
	}*/
	std::cout << std::endl << std::endl;
}

void Grid::NodeTraversal(Node *mNode, std::string currWord, unsigned i, std::unordered_set<Node*> pathway, int multiplier, std::vector<int> applied)
{
	if (i == currWord.length() - bonusAm)
	{
		// If the word is not in the final list add it, then return.
		if (done.find(currWord) == done.end())
		{
			done.insert(currWord);
			for (auto nums : applied)
			{
				multipliers[currWord].push_back(nums);
			}
		}
		return;
	}
	if (currWord[i] != mNode->letter.value())
	{
		return;
	}

	if (secPos != NULL)
		if (mNode == secPos)
		{
			multiplier = 2;
			applied.push_back(2);
		}

	if (thirdPos != NULL)
		if (mNode == thirdPos)
		{
			multiplier = 3;
			applied.push_back(3);
		}

	if (fullLet != NULL)
		if (mNode == fullLet)
		{
			multiplier = 4;
			applied.push_back(4);
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
			NodeTraversal(j, currWord, i + 1, pathway, multiplier, applied);
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

void HashJson(std::string fileName, std::string extension, std::unordered_map<int, std::vector<std::string>> &threadWord, int fileCount)
{
	std::ifstream file(fileName + extension);
	Json::Value jsonData;
	Json::Reader jsonReader;
	std::chrono::steady_clock::time_point clock_begin = std::chrono::steady_clock::now();
	// The data is now in jsonData.
	jsonReader.parse(file, jsonData);
	std::chrono::steady_clock::time_point clock_end = std::chrono::steady_clock::now();

	std::chrono::steady_clock::duration time_span = clock_end - clock_begin;
	double nseconds = double(time_span.count()) * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;

	std::cout << "It took me " << nseconds << " seconds to parse the JSON file." << std::endl << std::endl;

	// If there's an error, don't even do anything.
	if (!file.is_open()) {
		std::cerr << "Error opening JSON file." << std::endl;
		while (true) {}
	}

	int counter = 0;
	for (auto& i : jsonData.getMemberNames()) {
		IfMapMissingAdd(counter % fileCount, i, threadWord);
		counter++;
	}
	DictionaryMetrics initial(jsonData.size(), 0, jsonData.size());
	std::cout << "Initial: " << initial << std::endl;
}

void Grid::RefreshLockFiles()
{
	std::string assetPath = "assets/";
	for (const auto& i : std::filesystem::directory_iterator(assetPath))
	{
		std::string tempStr = "";
		for (unsigned j = i.path().string().length() - 5; j < i.path().string().length(); j++)
		{
			tempStr += i.path().string()[j];
		}
		if (tempStr == ".LOCK")
			std::filesystem::remove(i.path());
	}
}

DictionaryMetrics Grid::ThroughFiles(std::string lockPath, std::string fileName)
{
	std::chrono::steady_clock::time_point clock_begin = std::chrono::steady_clock::now();
	// Haha nice comment im keeping that there
	// Do Shit!
	DictionaryMetrics def(0, 0, 0);

	if (std::filesystem::exists(lockPath))
		return def;
	std::ifstream myFile(lockPath);
	std::ifstream thismFile(fileName);
	unsigned removedCount = 0;
	Json::Value myV;
	Json::Reader myR;
	myR.parse(thismFile, myV);

	for (auto &i : myV.getMemberNames())
	{
		bool problem = false;
		// Add every word to a map of their length.

		// Ignore this word if 1. It's longer than 25 letters, 2. It has a letter not in the grid.
		if (i.length() >= 26)
		{
			removedCount++;
			continue;
		}
		for (char myChar : i)
		{
			if (containedLetters.find(myChar) == containedLetters.end())
			{
				problem = true;
				break;
			}
		}
		if (problem == true)
		{
			//std::cout << i << " has been expelled from Hogwarts." << std::endl;
			removedCount++;
			continue;
		}

		def.myLenMap.push_back(std::make_pair(i.length(), i));
	}
	def += DictionaryMetrics(myV.getMemberNames().size(), removedCount, myV.getMemberNames().size() - removedCount);
	// std::cout << def;

	std::chrono::steady_clock::time_point clock_end = std::chrono::steady_clock::now();
	std::chrono::steady_clock::duration time_span = clock_end - clock_begin;
	double nseconds = double(time_span.count()) * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
	// std::cout << "Took " << nseconds << " for " << fileName << std::endl;
	if (myFile.is_open())
		myFile.close();

	if (std::filesystem::exists(lockPath))
		std::filesystem::remove(lockPath);

	if (thismFile.is_open())
		thismFile.close();
	return def;
}

void Grid::JsonToThreads(int fileCount)
{
	std::unordered_map<int, std::vector<std::string>> threadWord;
	// Open the json dictionary file
	std::string fileName = "words_dictionary";
	std::string extension = ".json";
	bool done = false;
	std::vector<std::future<DictionaryMetrics>> threads;
	std::vector<std::future_status> statusees;

	std::cout << "Added to Dictionary Successfully." << std::endl; 


	for (int i = 0; i < fileCount; i++)
	{
		std::string newFileName = "assets/" + fileName + std::to_string(i) + extension;
		if (std::filesystem::exists(newFileName))
			continue;
		if (done == false)
		{
			HashJson(fileName, extension, threadWord, fileCount);
			done = true;
		}
		std::ofstream myFile(newFileName);
		Json::Value rootJsonValue;

		Json::StreamWriterBuilder builder;
		builder["commentStyle"] = "None";
		builder["indentation"] = "   ";
		std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

		for (std::string elem : threadWord[i])
		{
			rootJsonValue[elem] = 1;
		}
		writer->write(rootJsonValue, &myFile);

		if (myFile.is_open())
			myFile.close();
	}

	for (int i = 0; i < fileCount; i++)
	{
		std::string newFileName = "assets/" + fileName + std::to_string(i) + extension;

		std::string lockName = "assets/" + fileName + std::to_string(i) + ".LOCK";
		threads.push_back(std::async(std::launch::async, &Grid::ThroughFiles , this, lockName, newFileName));

		std::future_status newStatus;
		statusees.push_back(newStatus);
	}

	std::chrono::steady_clock::time_point clock_begin = std::chrono::steady_clock::now();

	for (int i = 0; i < fileCount; i++)
	{
		statusees[i] = threads[i].wait_for(std::chrono::milliseconds(10000));
	}

	std::chrono::steady_clock::time_point clock_end = std::chrono::steady_clock::now();
	std::chrono::steady_clock::duration time_span = clock_end - clock_begin;
	double nseconds = double(time_span.count()) * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
	
	bool alldone = false;
	while (alldone == false)
	{
		alldone = true;
		for (auto j : statusees)
		if (j != std::future_status::ready)
		{
			alldone = false;
		}
	}

	DictionaryMetrics father;
	for (auto &i : threads)
	{
		DictionaryMetrics f = i.get();
		for (auto [num, word] : f.myLenMap)
		{
			if (lenMap.find(num) == lenMap.end())
			{
				WordList tmp = WordList();
				std::pair<int, WordList> temp = std::make_pair(num, tmp);
				lenMap.insert(temp);
			}
			lenMap[num].myWords.push_back(word);
		}
		father += f;
	}

	std::cout << father;

	std::cout << "HOOO HEEE THAT WAS HELL there's your 8. " << nseconds << " seconds to get out of that hell hole." << std::endl << std::endl;
}

void JsonToBinary()
{

}

void Grid::HashWords()
{
	JsonToThreads(1);


	//int removedCount = 0;

	//// Assign the JSON info.
	//for (auto i : jsonData.getMemberNames())
	//{
	//	bool problem = false;
	//	// Add every word to a map of their length.
	//	std::string mWord = i;

	//	// Ignore this word if 1. It's longer than 25 letters, 2. It has a letter not in the grid.
	//	if (mWord.size() >= 26)
	//	{
	//		removedCount++;
	//		continue;
	//	}
	//	for (char myChar : mWord)
	//	{
	//		if (containedLetters.find(myChar) == containedLetters.end())
	//		{
	//			problem = true;
	//			break;
	//		}
	//	}
	//	if (problem == true)
	//	{
	//		// std::cout << i << " has been expelled from Hogwarts." << std::endl;
	//		removedCount++;
	//		continue;
	//	}

	//	int myLen = (int)mWord.length();
	//	if (lenMap.find(myLen) == lenMap.end())
	//		lenMap[myLen] = WordList();
	//	lenMap[myLen].myWords.push_back(mWord);
	//}
	//std::cout << std::endl << "Dictionary Metrics: " << std::endl << "Starting Data Count: " << jsonData.size() << std::endl;
	//std::cout << "Removed Words: " << removedCount << std::endl;
	//std::cout << "Words Remaining: " << (jsonData.size() - removedCount) << std::endl;
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

	if (doubleLocation != std::nullopt)
		secPos = grid[doubleLocation.value()];
	if (tripleLocation != std::nullopt)
		thirdPos = grid[tripleLocation.value()];
	if (fullLetLocation != std::nullopt)
		fullLet = grid[fullLetLocation.value()];

	for (auto& [_, word] : lenMap | std::views::reverse) {
		for (int j = 0; j < word.myWords.size(); j++)
		{
			std::string currW = word.myWords[j];
			Node* lastNode = NULL;
			std::unordered_set<Node*> pathway = std::unordered_set<Node*>();
			for (Node* node : letterNodeMap.at(currW[0]))
			{
				NodeTraversal(node, currW, 0, pathway, 1, std::vector<int>());
			}
		}
	}
}

bool Grid::TryGetValue()
{
	return false;
}

Grid::~Grid()
{
	for (auto i : grid)
	{
		delete i;
	}
}