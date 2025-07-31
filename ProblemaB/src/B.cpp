#include <bits/stdc++.h>
#include <string>

using namespace std;

struct TrieNode {
    TrieNode* children[10] = {};
    int count = 0; // number of words that pass through this node

    ~TrieNode() {
        for (int i = 0; i < 10; ++i) {
            delete children[i];
        }
    }
};

class Trie {
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    // Insert a word made of digits '0'-'9'
    void insert(const string& word) {
        TrieNode* node = root;
        node->count++; // update root count
        for (char ch : word) {
            int idx = ch - '0';
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
            node->count++;
        }
    }

    // Count how many words start with the given prefix
    int count_prefix(const string& prefix) const {
        TrieNode* node = root;
        for (char ch : prefix) {
            int idx = ch - '0';
            if (!node->children[idx]) return 0;
            node = node->children[idx];
        }
        return node->count;
    }
};

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int n, p;
	int caso = 1;
	std::string line;
	while (cin >> n >> p) {
		// Skip new line
		getline(cin, line);
		Trie t;
		while (n--) {
			getline(cin, line);
			t.insert(line);
		}
		cout << "Case " << caso << ":\n";
		while (p--) {
			getline(cin, line);
			cout << t.count_prefix(line) << "\n";
		}
		caso++;
	}
}
