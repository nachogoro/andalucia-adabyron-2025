#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> d;
	for (int r = 0; r < n; r++) {
		d.push_back({});

		for (int c = 0; c < m; c++) {
			int diamantes;
			cin >> diamantes;
			d[r].push_back(diamantes);
		}
	}

	vector<vector<int>> dp(n, vector<int>(m));

	dp[0][0] = d[0][0];

	for (int r = 1; r < n; r++) {
		dp[r][0] = dp[r-1][0] + d[r][0];
	}

	for (int c = 1; c < m; c++) {
		dp[0][c] = dp[0][c-1] + d[0][c];
	}

	for (int r = 1; r < n; ++r) {
		for (int c = 1; c < m; ++c) {
			dp[r][c] = d[r][c] + max(max(dp[r-1][c], dp[r][c-1]), dp[r-1][c-1]);
		}
	}

	cout << dp[n-1][m-1] << "\n";
}
