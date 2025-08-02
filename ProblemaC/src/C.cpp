#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

/// Estructura para resolver el problema del emparejamiento máximo
/// en un grafo bipartito utilizando una versión optimizada de DFS/BFS
struct BipartiteMatcher {
	int n, m;                // n: número de nodos en el lado izquierdo
	                         // m: número de nodos en el lado derecho
	vector<vector<int>> g;   // g[u] = lista de vecinos del nodo u en el lado izquierdo
	vector<int> match, dist; // match[v] = nodo izquierdo emparejado con v (o -1 si libre)
	                         // dist[u] = distancia desde u en la BFS

	// Constructor: inicializa el grafo con n nodos a la izquierda y m a la derecha
	BipartiteMatcher(int n, int m)
		: n(n)
		, m(m)
		, g(n)
		, match(m, -1)
		, dist(n) {}

	// Añade una arista entre el nodo u del lado izquierdo y v del derecho
	void add_edge(int u, int v) {
		g[u].push_back(v);
	}

	// BFS: construye niveles de búsqueda y detecta si hay caminos aumentantes
	bool bfs() {
		queue<int> q;
		fill(dist.begin(), dist.end(), -1);

		// Añadimos nodos libres del lado izquierdo a la cola
		for (int u = 0; u < n; ++u) {
			bool is_matched = false;
			for (int v : g[u]) {
				if (match[v] == u) {
					is_matched = true;
					break;
				}
			}
			if (!is_matched) {
				dist[u] = 0;
				q.push(u);
			}
		}

		bool found = false;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int v : g[u]) {
				int u2 = match[v];
				if (u2 == -1) {
					found = true;  // se puede aumentar por esta arista
				} else if (dist[u2] == -1) {
					dist[u2] = dist[u] + 1;
					q.push(u2);
				}
			}
		}
		return found;
	}

	// DFS: intenta extender el emparejamiento por un camino aumentante
	bool dfs(int u) {
		for (int v : g[u]) {
			int u2 = match[v];
			if (u2 == -1 || (dist[u2] == dist[u] + 1 && dfs(u2))) {
				match[v] = u;
				return true;
			}
		}
		return false;
	}

	// Devuelve el tamaño del emparejamiento máximo
	int max_matching() {
		int match_count = 0;
		while (bfs()) {
			for (int u = 0; u < n; ++u) {
				if (dfs(u)) ++match_count;
			}
		}
		return match_count;
	}
};

int main() {
	int T;
	cin >> T;
	while (T--) {
		int R, C;
		cin >> R >> C;
		vector<string> grid(R);
		for (auto& row : grid) cin >> row;

		// Asignamos un ID a cada segmento horizontal sin paredes
		vector<vector<int>> horiz(R, vector<int>(C, -1));
		int h_id = 0;
		for (int i = 0; i < R; ++i) {
			int j = 0;
			while (j < C) {
				if (grid[i][j] == 'X') {
					++j;
					continue;
				}
				while (j < C && grid[i][j] != 'X') {
					horiz[i][j] = h_id;
					++j;
				}
				++h_id;
			}
		}

		// Asignamos un ID a cada segmento vertical sin paredes
		vector<vector<int>> vert(R, vector<int>(C, -1));
		int v_id = 0;
		for (int j = 0; j < C; ++j) {
			int i = 0;
			while (i < R) {
				if (grid[i][j] == 'X') {
					++i;
					continue;
				}
				while (i < R && grid[i][j] != 'X') {
					vert[i][j] = v_id;
					++i;
				}
				++v_id;
			}
		}

		// Creamos el grafo bipartito a partir de las T (puestos de estudio)
		BipartiteMatcher bm(h_id, v_id);
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) {
				if (grid[i][j] == 'T') {
					int h = horiz[i][j];
					int v = vert[i][j];
					bm.add_edge(h, v);  // cada T conecta su fila y columna
				}
			}
		}

		// La respuesta es el tamaño del emparejamiento máximo
		cout << bm.max_matching() << '\n';
	}
}

