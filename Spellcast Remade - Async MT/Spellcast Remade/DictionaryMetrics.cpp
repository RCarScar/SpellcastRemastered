#include "DictionaryMetrics.h"


std::ostream& operator<<(std::ostream& input, const DictionaryMetrics& dict)
{
	input << std::endl << "Words Initially: " << dict.startCount << std::endl << "Words Now: " << dict.validWords << std::endl << "Words Removed: " << dict.removedCount << std::endl;
	return input;
}

DictionaryMetrics operator+(DictionaryMetrics& lhs, const DictionaryMetrics& rhs)
{
	return DictionaryMetrics(lhs.startCount += rhs.startCount, lhs.removedCount + rhs.removedCount, lhs.validWords += rhs.validWords);
}

DictionaryMetrics& operator+=(DictionaryMetrics& lhs, const DictionaryMetrics& rhs)
{
	lhs.startCount += rhs.startCount;
	lhs.validWords += rhs.validWords;
	lhs.removedCount += rhs.removedCount;
	return lhs;
}