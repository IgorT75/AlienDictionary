#include <cstdio>
#include <queue>
#include <vector>
#include <map>
#include <stack>
#include <exception>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution
{
private:
	enum State { white = 0, gray = 1, black = 2 };

	map<char, vector<char>> _graph;
	map<char, State> _state;
	string _out;
public:
	Solution() = default;

	string alienOrder(vector<string>& words) {

		// build graph - init
		size_t idx = 0;
		for (const string& s : words) {
			for (const char c : s) {
				if (_graph.find(c) == _graph.end()) {
					_graph[c] = {};
					_state[c] = white;
				}
			}
		}

		// fill graph
		for (size_t i = 1; i < words.size(); ++i) {
			const auto& w1 = words[i-1];
			const auto& w2 = words[i];
			const size_t szMin = std::min(w1.size(), w2.size());
			size_t idx = szMin;
			for (size_t j = 0; j < szMin; ++j) {
				if (w1[j] != w2[j]) {
					auto& v = _graph[w1[j]];
					if (std::find(v.begin(), v.end(), w2[j]) == v.end())
						v.push_back(w2[j]);

					idx = j;
					break;
				}
			}

			// check if ab follows abc
			if (idx == szMin) {
				if (w1.size() > w2.size())
					return ""s;
			}
		}

		// run dfs
		_out = ""s;
		for (auto const& [c, val] : _graph) {
			if (_state[c] == white)
				if (dfs(c))
					return ""s;
		}

		std::reverse(_out.begin(), _out.end());
		return _out;
	}

	// returned true means there is a cycle
	bool dfs(char c) {
		_state[c] = gray;
		for (char adj : _graph[c]) {
			if (_state[adj] == gray) {
				return true;
			}
			if (_state[adj] == white) {
				if (dfs(adj))
					return true;
			}
		}
		_state[c] = black;
		_out += c;
		return false;
	}
};

int main() {
	vector<string> words = { "wrt", "wrf", "er", "ett", "rftt" };
	//words = { "xxxxxx", "z", "zx" };
	//words = { "abc", "abc" };

	Solution s;
	string order = s.alienOrder(words);
	printf("%s\n", order.c_str());
	return 0;
}