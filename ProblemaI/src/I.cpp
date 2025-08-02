#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll solve_case(int M, const vector<int>& top, const vector<int>& bot) {
    if (M == 0) return 0;
    if (M == 1) return max(top[0], bot[0]);

    vector<ll> dp_top(M), dp_bot(M);

    // Casos base
    dp_top[0] = top[0];
    dp_bot[0] = bot[0];

    dp_top[1] = bot[0] + top[1];
    dp_bot[1] = top[0] + bot[1];

    // Transición dinámica
    for (int i = 2; i < M; ++i) {
        dp_top[i] = max(dp_bot[i - 1], dp_bot[i - 2]) + top[i];
        dp_bot[i] = max(dp_top[i - 1], dp_top[i - 2]) + bot[i];
    }

    return max(dp_top[M - 1], dp_bot[M - 1]);
}

int main() {
    int N;
    cin >> N;

    while (N--) {
        int M;
        cin >> M;
        vector<int> top(M), bot(M);

        for (int i = 0; i < M; ++i) cin >> top[i];
        for (int i = 0; i < M; ++i) cin >> bot[i];

        cout << solve_case(M, top, bot) << '\n';
    }
}
