#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> position(3, vector<int>(3, 0));

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a%b);
}

int lcm(int a, int b) {
	return a*b/gcd(a,b);
}

int simulate(vector<int> p) {
	vector<int> v = {0,0,0};

	vector<int> initial_position = p;
	vector<int> initial_velocity = v;

	int steps = 0;

	do {
		if(p[0] > p[1]) {
			v[0]--;
			v[1]++;
		} else if (p[0] < p[1]) {
			v[0]++;
			v[1]--;
		}

		if(p[0] > p[2]) {
			v[0]--;
			v[2]++;
		} else if (p[0] < p[2]) {
			v[0]++;
			v[2]--;
		}

		if(p[1] > p[2]) {
			v[1]--;
			v[2]++;
		} else if (p[1] < p[2]) {
			v[1]++;
			v[2]--;
		}

		for (int i = 0; i < 3; ++i) {
			p[i] += v[i];
		}

		++steps;
	} while (p != initial_position || v != initial_velocity);

	return steps;
}

int solve() {
	int T_x = simulate({position[0][0], position[1][0], position[2][0]});
	int T_y = simulate({position[0][1], position[1][1], position[2][1]});
	int T_z = simulate({position[0][2], position[1][2], position[2][2]});

	return lcm(T_x, lcm(T_y, T_z));
}

int main() {
	int N;
	cin >> N;

	while(N--) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				cin >> position[i][j];
			}
		}

		cout << solve() << "\n";
	}
}
