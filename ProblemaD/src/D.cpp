#include <bits/stdc++.h>

using namespace std;

void solve(const vector<int>& compras, int vales)
{
	// Valor, gasto original, persona
	using entry = std::tuple<double, int, int>;

	priority_queue<entry> pq;

	for (int c = 0; c < compras.size(); ++c) {
		pq.push({compras[c], compras[c], c});
	}

	vector<int> resultado(compras.size(), 0);

	while(vales--) {
		double valor;
		int gasto, persona;
		tie(valor, gasto, persona) = pq.top();
		pq.pop();

		resultado[persona]++;
		pq.push({gasto / (resultado[persona] + 1), gasto, persona});
	}

	for (int i = 0; i < resultado.size(); ++i) {
		cout << resultado[i];
		if (i != resultado.size() - 1) cout << " ";
	}
	cout << "\n";
}

int main() {
	while(true) {
		int m, n;
		cin >> m >> n;

		if (m == 0 && n == 0) break;

		vector<int> v(m, 0);
		for (int i = 0; i < m; ++i) {
			cin >> v[i];
		}

		solve(v, n);
	}
}
