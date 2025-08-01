#include <bits/stdc++.h>
using namespace std;

int main() {
	int o;
	cin >> o;

	while (o--) {
		int n, q;
		cin >> n >> q;

		vector<int> notas(n);
		for (int i = 0; i < n; ++i) {
			cin >> notas[i];
		}

		// Ordenamos las notas para poder hacer búsquedas binarias
		sort(notas.begin(), notas.end());

		while (q--) {
			int u;
			cin >> u;

			// Buscamos el primer elemento >= u
			auto it = lower_bound(notas.begin(), notas.end(), u);

			// La cantidad de notas >= u es el número de elementos desde 'it' hasta el final
			int resultado = notas.end() - it;
			cout << resultado << "\n";
		}
	}

    return 0;
}

