#include "gmock/gmock.h"
#include "keyword_manager.h"
using namespace std;

TEST(BwTestAll, ExactMatch) {
	LevenshteinSimilarity sim;
	EXPECT_EQ(sim.computeScore("apple", "apple"), 0);
}

TEST(BwTestAll, SimilarWords) {
	LevenshteinSimilarity sim;
	EXPECT_EQ(sim.computeScore("apple", "appla"), 1);
}

TEST(BwTestAll, KeywordManagerGetWeekdayIndex) {
	KeywordManager manager(new LevenshteinSimilarity());
	string result = manager.processKeyword("apple", "appla");
	EXPECT_EQ(result, "ERR_CASE");
}

TEST(BwTestAll, KeywordManagerGetGroupIndex) {
	KeywordManager manager(new LevenshteinSimilarity());
	string result = manager.processKeyword("water", "monday");
	EXPECT_EQ(result, "water");
}

TEST(BwTestAll, KeywordManagerPerfectlySameKeyword) {
	KeywordManager manager(new LevenshteinSimilarity());
	string result = manager.processKeyword("water", "monday");
	EXPECT_EQ(result, "water");
	result = manager.processKeyword("water", "monday");
	EXPECT_EQ(result, "water");
}

TEST(BwTestAll, KeywordManagerSimilarWord) {
	KeywordManager manager(new LevenshteinSimilarity());
	string result = manager.processKeyword("water", "monday");
	EXPECT_EQ(result, "water");
	result = manager.processKeyword("witer", "monday");
	EXPECT_EQ(result, "water");
}

TEST(BwTestAll, KeywordManagerWeekBestScore) {
	KeywordManager manager(new LevenshteinSimilarity());
	string result = manager.processKeyword("water", "monday");
	EXPECT_EQ(result, "water");
	result = manager.processKeyword("pepper", "monday");
	EXPECT_EQ(result, "pepper");
	result = manager.processKeyword("orange", "monday");
	EXPECT_EQ(result, "orange");
	result = manager.processKeyword("kiss", "monday");
	EXPECT_EQ(result, "kiss");
	result = manager.processKeyword("light", "monday");
	EXPECT_EQ(result, "light");
	result = manager.processKeyword("dog", "monday");
	EXPECT_EQ(result, "dog");
	result = manager.processKeyword("cat", "monday");
	EXPECT_EQ(result, "cat");
	result = manager.processKeyword("home", "monday");
	EXPECT_EQ(result, "home");
	result = manager.processKeyword("coffee", "monday");
	EXPECT_EQ(result, "coffee");
	result = manager.processKeyword("gift", "monday");
	EXPECT_EQ(result, "gift");
}


TEST(BwTestAll, KeywordManagerReArangeScore) {
	KeywordManager manager(new LevenshteinSimilarity());
	string result = manager.processKeyword("water", "monday");
	EXPECT_EQ(result, "water");
	result = manager.processKeyword("pepper", "monday");
	EXPECT_EQ(result, "pepper");
	result = manager.processKeyword("orange", "monday");
	EXPECT_EQ(result, "orange");
	result = manager.processKeyword("kiss", "monday");
	EXPECT_EQ(result, "kiss");
	result = manager.processKeyword("light", "monday");
	EXPECT_EQ(result, "light");
	result = manager.processKeyword("dog", "monday");
	EXPECT_EQ(result, "dog");
	result = manager.processKeyword("cat", "monday");
	EXPECT_EQ(result, "cat");
	result = manager.processKeyword("home", "monday");
	EXPECT_EQ(result, "home");
	result = manager.processKeyword("coffee", "monday");
	EXPECT_EQ(result, "coffee");
	for (int i = 0; i < 300; ++i) {
		result = manager.processKeyword("coffee", "monday");
	}
	EXPECT_EQ(result, "coffee");
}

TEST(BwTestAll, KeywordManagerSameNameInInsertOrUpdate) {
	KeywordManager manager(new LevenshteinSimilarity());
	string result = manager.processKeyword("water", "monday");
	EXPECT_EQ(result, "water");
	result = manager.processKeyword("witer", "tuesday");
	EXPECT_EQ(result, "water");
	result = manager.processKeyword("weter", "wednesday");
	EXPECT_EQ(result, "water");
	result = manager.processKeyword("wbter", "thursday");
	EXPECT_EQ(result, "water");
	result = manager.processKeyword("wnter", "friday");
	EXPECT_EQ(result, "water");
	result = manager.processKeyword("water", "saturday");
	EXPECT_EQ(result, "water");
	result = manager.processKeyword("weter", "monday");
	EXPECT_EQ(result, "water");
	result = manager.processKeyword("wster", "tuesday");
	EXPECT_EQ(result, "water");
	result = manager.processKeyword("whter", "wednesday");
	EXPECT_EQ(result, "water");
	result = manager.processKeyword("wkter", "thursday");
	EXPECT_EQ(result, "water");
	result = manager.processKeyword("wlter", "friday");
	EXPECT_EQ(result, "water");
	result = manager.processKeyword("wpter", "saturday");
	EXPECT_EQ(result, "water");
}