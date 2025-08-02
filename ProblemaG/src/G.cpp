#include <bits/stdc++.h>

using namespace std;

struct count_t {
	int A = 0;
	int C = 0;
	int G = 0;
	int T = 0;
};

string strand;
int min_gc;
int max_at;
int shortest;
int longest;
vector<count_t> prefix;

void update(count_t& c, char nucleotid) {
	switch(nucleotid) {
		case 'A':
			c.A++;
			break;
		case 'C':
			c.C++;
			break;
		case 'G':
			c.G++;
			break;
		case 'T':
			c.T++;
			break;
		default:
			break;
	}
}

// Binary search for the first position in [to, from] which has at least min_G
// G and min_C C nucleotids. If none is found, returns a number above to.
int first_gc(vector<count_t>& p, int from, int to, int min_G, int min_C) {
	int left = from;
	int right = to;

	while (left != right) {
		int middle = (left + right) / 2;
		if (p[middle].G < min_G || p[middle].C < min_C) {
			left = middle + 1;
		} else {
			right = middle;
		}
	}

	if (p[left].G >= min_G && p[left].C >= min_C) {
		return left;
	} else {
		return to + 1;
	}
}

// Binary search for the last position in [to, from] which has at most max_A
// A and max_T T nucleotids. If none is found, returns a number below from.
int last_at(vector<count_t>& p, int from, int to, int max_A, int max_T) {
	int left = from;
	int right = to;

	while (left <= right) {
		int mid = (left + right) / 2;
		if (p[mid].A < max_A && p[mid].T < max_T) {
			// buscar más a la derecha
			left = mid + 1;
		} else {
			// descartar mid y lo de la derecha
			right = mid - 1;
		}
	}

	// Al salir, right es el último que cumple la condición
	return right;
}


int candidates(int i) {
	count_t until_now;
	if (i > 0) {
		until_now = prefix[i-1];
	}

	int end_of_shortest = i + shortest - 1;
	int end_of_longest = i + longest - 1;
	end_of_longest = clamp(end_of_longest, 0, (int) prefix.size() - 1);

	int left = first_gc(prefix, end_of_shortest, end_of_longest, until_now.G + min_gc, until_now.C + min_gc);
	int right = last_at(prefix, end_of_shortest, end_of_longest, until_now.A + max_at, until_now.T + max_at);

	return clamp(right - left + 1, 0, numeric_limits<int>::max());
}

void solve()
{
	prefix = vector<count_t>(strand.size(), {0,0,0,0});
	update(prefix[0], strand[0]);

	for (int i = 1; i < strand.size(); ++i) {
		prefix[i] = prefix[i-1];
		update(prefix[i], strand[i]);
	}

	int result = 0;

	for (int i = 0; i < strand.size() - shortest + 1; ++i) {
		result += candidates(i);
	}
	cout << result << "\n";
}

int main() {
	int o;
	cin >> o;

	while(o--) {
		int l;
		cin >> l >> shortest >> longest >> min_gc >> max_at;

		// Skip newline char
		getline(cin, strand);

		getline(cin, strand);
		solve();
	}
}
