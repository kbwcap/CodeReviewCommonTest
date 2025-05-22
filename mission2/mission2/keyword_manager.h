#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>

const int MAX_SCORE = 2100000000;
const int MAX_ENTRIES = 10;
const int ERR_MSG = -1;

class SimilarityStrategy {
public:
	virtual int computeScore(const std::string& a, const std::string& b) = 0;
	virtual ~SimilarityStrategy() = default;
};
	
class LevenshteinSimilarity : public SimilarityStrategy {
public:
	int computeScore(const std::string& a, const std::string& b) override;
};


struct WordNode {
	std::string name;
	int point;

	bool operator<(const WordNode& other) const {
		return point < other.point;
	}
};

class KeywordManager {
private:
	std::vector<WordNode> weekBest[7];   // Monday ~ Sunday
	std::vector<WordNode> groupBest[2];  // Weekday(0), Weekend(1)
	int currentScore = 9;

	SimilarityStrategy *similarity;

	int getWeekdayIndex(const std::string& day);
	int getGroupIndex(int weekdayIndex);
	bool isSimilar(const std::string& a, const std::string& b);
	void reAdjustScore();
	void insertOrUpdate(std::vector<WordNode>& list, const std::string& word, int score);

public:
	KeywordManager(SimilarityStrategy *sim)
		: similarity(sim) {
	}

	std::string processKeyword(const std::string& word, const std::string& day);
};