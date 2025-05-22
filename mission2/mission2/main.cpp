#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "gmock/gmock.h"

using namespace std;


const int MAX_SCORE = 2100000000;
const int MAX_ENTRIES = 10;

struct WordNode {
	string name;
	int point;

	bool operator<(const WordNode& other) const {
		return point < other.point;
	}
};

vector<WordNode> weekBest[7]; //�� ~ ��
vector<WordNode> groupBest[2]; //����, �ָ�
int currentScore = 9;

// ������Ÿ�� �Ÿ� ��� �˰��� (���ڿ� ���絵 �˻�)
int levenshtein(const std::string& a, const std::string& b) {
	const size_t len_a = a.size();
	const size_t len_b = b.size();

	std::vector<std::vector<int>> d(len_a + 1, std::vector<int>(len_b + 1));

	for (size_t i = 0; i <= len_a; ++i) d[i][0] = i;
	for (size_t j = 0; j <= len_b; ++j) d[0][j] = j;

	for (size_t i = 1; i <= len_a; ++i) {
		for (size_t j = 1; j <= len_b; ++j) {
			if (a[i - 1] == b[j - 1])
				d[i][j] = d[i - 1][j - 1];
			else
				d[i][j] = 1 + std::min({ d[i - 1][j], d[i][j - 1], d[i - 1][j - 1] });
		}
	}
	return d[len_a][len_b];
}

// ���� ȯ��
bool similer(const std::string& a, const std::string& b) {
	if (a.empty() && b.empty()) return 100;
	if (a.empty() || b.empty()) return 1;

	int dist = levenshtein(a, b);
	int max_len = std::max(a.length(), b.length());
	// ���絵 ���� (1.0: ������ ����, 0.0: ���� �ٸ�)
	double similarity = 1.0 - (double)dist / max_len;

	int score = 1 + static_cast<int>(similarity * 99);

	if (score >= 80) return true;
	return false;
}

int getWeekdayIndex(const string& day) {
	static map<string, int> dayMap = {
		{"monday", 0},
		{"tuesday", 1},
		{"wednesday", 2},
		{"thursday", 3},
		{"friday", 4},
		{"saturday", 5},
		{"sunday", 6}
	};
	return dayMap[day];
}

int getGroupIndex(int weekdayIndex) {
	return (weekdayIndex >= 0 && weekdayIndex <= 4) ? 0 : 1;
}


void reAdjustScore() {
	currentScore = 9;
	for (int i = 0; i < 7; ++i) {
		int score = 1;
		for (WordNode& node : weekBest[i])
			node.point = score++;
	}
	for (int i = 0; i < 2; ++i) {
		int score = 1;
		for (WordNode& node : groupBest[i])
			node.point = score++;
	}
}

void insertOrUpdate(vector<WordNode>& list, const string& word, int score) {
	for (auto& node : list) {
		if (node.name == word) {
			node.point += static_cast<int>(node.point * 0.1);
			return;
		}
	}
	if (list.size() < MAX_ENTRIES) {
		list.push_back({ word, score });
	}
	else if (list.back().point < score) {
		list.back() = { word, score };
	}
	sort(list.begin(), list.end());
}

string processKeyword(string word, string day) {
	currentScore++;

	int dayIndex = getWeekdayIndex(day);

	// ���� / �ָ�
	int groupIndex = getGroupIndex(dayIndex);
	int point = currentScore;

	//���� ��Ͽ� �����ϴ��� Ȯ��
	//�����Ǵ� Ű�����̸� ������ ����

	for (WordNode& node : weekBest[dayIndex]) {
		if (node.name == word) {
			node.point += static_cast<int>(node.point * 0.1);
			if (currentScore >= MAX_SCORE || node.point >= MAX_SCORE)
				reAdjustScore();
			return word;
		}
	}

	//���� HIT
	for (WordNode& node : weekBest[dayIndex]) {
		if (similer(node.name, word)) {
			return node.name;
		}
	}

	for (WordNode& node : groupBest[groupIndex]) {
		if (similer(node.name, word)) {
			return node.name;
		}
	}

	// �ű� ���
	insertOrUpdate(weekBest[dayIndex], word, point);
	insertOrUpdate(groupBest[groupIndex], word, point);

	return word;
}

void loadKeywords() {
	ifstream fin{ "keyword_weekday_500.txt" }; //500�� ������ �Է�

	if (!fin.is_open()) {
		std::cerr << "���� ���� ����!" << std::endl;
		return;
	}

	for (int i = 0; i < 500; i++) {
		string word, day;
		fin >> word >> day;
		string ret = processKeyword(word, day);
		std::cout << ret << " <== " << word << "\n";
	}
}

int main() {
	loadKeywords();
}