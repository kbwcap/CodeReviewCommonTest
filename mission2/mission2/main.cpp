#include "keyword_manager.h"
#include "gmock/gmock.h"

using namespace std;

void loadKeywords(KeywordManager& manager) {
	ifstream fin("keyword_weekday_500.txt");
	string word, day;
	for (int i = 0; i < 500 && fin >> word >> day; ++i) {
		string result = manager.processKeyword(word, day);
		cout << result << '\n';
	}
}

int main() {

	KeywordManager manager(new LevenshteinSimilarity());
	loadKeywords(manager);

	return 0;
}

