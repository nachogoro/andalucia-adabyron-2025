#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	ll t;
	cin >> t;

	while(t--) {
		ll concursantes;
		cin >> concursantes;

		ll combates = 0;

		while (concursantes != 1) {
			if (concursantes % 2 != 0) {
				concursantes++;
			}

			concursantes /= 2;
			combates += concursantes;
		}

		cout << combates << "\n";
	}
}
