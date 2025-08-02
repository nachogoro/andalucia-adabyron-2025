#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

struct Edge {
	int u, v;
	double dist;
	int satisfaction;
	bool operator<(const Edge& other) const {
		return dist < other.dist;
	}
};

// Disjoint Set Union (Union-Find) para Kruskal
struct DSU {
	vector<int> parent;
	DSU(int n) : parent(n) {
		iota(parent.begin(), parent.end(), 0);
	}
	int find(int u) {
		if (parent[u] != u)
			parent[u] = find(parent[u]);
		return parent[u];
	}
	bool unite(int u, int v) {
		int pu = find(u);
		int pv = find(v);
		if (pu == pv) return false;
		parent[pu] = pv;
		return true;
	}
};

// Calcula la distancia euclídea entre dos puntos
double dist(pii a, pii b) {
	int dx = a.first - b.first;
	int dy = a.second - b.second;
	return sqrt(dx * dx + dy * dy);
}

// Intenta construir un árbol de expansión con aristas de distancia <= max_dist
// Si lo consigue y la satisfacción es >= S, devuelve true
bool can_build(double max_dist, int N, int S, const vector<Edge>& all_edges) {
	vector<Edge> filtered;
	for (const Edge& e : all_edges) {
		if (e.dist <= max_dist)
			filtered.push_back(e);
	}

	// Ordenamos primero por satisfacción descendente, luego por distancia ascendente
	sort(filtered.begin(), filtered.end(), [](const Edge& a, const Edge& b) {
			if (a.satisfaction != b.satisfaction)
				return a.satisfaction > b.satisfaction;
			return a.dist < b.dist;
			});

	DSU dsu(N + 1);
	int count = 0, total_satisfaction = 0;
	for (const Edge& e : filtered) {
		if (dsu.unite(e.u, e.v)) {
			++count;
			total_satisfaction += e.satisfaction;
			if (count == N) break;
		}
	}

	return count == N && total_satisfaction >= S;
}

int main() {
	int T;
	cin >> T;
	cout << fixed << setprecision(2);

	while (T--) {
		int N, X, Y;
		cin >> N >> X >> Y;
		vector<pii> nodes(N + 1);
		nodes[0] = {X, Y};

		for (int i = 1; i <= N; ++i) {
			cin >> nodes[i].first >> nodes[i].second;
		}

		int S;
		cin >> S;

		int M;
		cin >> M;

		map<pair<int, int>, int> view;
		for (int i = 0; i < M; ++i) {
			int a, b, v;
			cin >> a >> b >> v;
			if (a > b) swap(a, b);
			view[{a, b}] = v;
		}

		// Generar todas las aristas
		vector<Edge> edges;
		for (int i = 0; i <= N; ++i) {
			for (int j = i + 1; j <= N; ++j) {
				double d = dist(nodes[i], nodes[j]);
				int s = view.count({i, j}) ? view[{i, j}] : 0;
				edges.push_back({i, j, d, s});
			}
		}

		// Binary search entre 0 y una distancia máxima (diagonal del plano)
		double lo = 0.0, hi = 2e4 * sqrt(2), ans = -1.0;
		while (hi - lo > 1e-3) {
			double mid = (lo + hi) / 2.0;
			if (can_build(mid, N, S, edges)) {
				ans = mid;
				hi = mid;
			} else {
				lo = mid;
			}
		}

		if (ans < 0)
			cout << "-1.00\n";
		else
			cout << ans << '\n';
	}

	return 0;
}

