#pragma once
#include <iostream>
#include <vector>
#include <optional>
#include "WordList.h"

class DictionaryMetrics
{
public:
	friend std::ostream& operator<<(std::ostream& os, const DictionaryMetrics& dict);
	friend DictionaryMetrics& operator+=(DictionaryMetrics& lhs, const DictionaryMetrics& rhs);
	friend DictionaryMetrics operator+(DictionaryMetrics& lhs, const DictionaryMetrics& rhs);

	DictionaryMetrics(unsigned mStart, unsigned mRemoved, unsigned mValid)
	{
		startCount = mStart;
		removedCount = mRemoved;
		validWords = mValid;
	}
	DictionaryMetrics()
	{
		startCount = 0;
		removedCount = 0;
		validWords = 0;
	}
	unsigned startCount = 0;
	unsigned removedCount = 0;
	unsigned validWords = 0;
	std::vector<std::pair<int, std::string>> myLenMap;
};