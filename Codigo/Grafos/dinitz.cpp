// Dinitz
//
// O(min(m * max_flow, n^2 m))
// Grafo com capacidades 1: O(min(m sqrt(m), m * n^(2/3)))
// Todo vertice tem grau de entrada ou saida 1: O(m sqrt(n))

// Minimum Vertex Cover: menor conjunto de vertices que chega em toda aresta do grafo
// Teorema de Konig: Minimum Vertex Cover = Maximum Matching em grafo bipartido
// Recover: roda min-cut e eh so pegar os vertices das arestas do corte
//
// Maximum Independent Set: maior conjunto de vertices tal que ninguem eh vizinho
// Maximum Independent Set = N - Minimum Vertex Cover (os vertices tambem sao complementares)
// Recover: pega os vertices que nao sao do min cover
//
// Maximum Clique: maior conjunto de vertices tal que todo mundo eh vizinho de todo mundo
// Maximum Independent Set = Maximum Clique do grafo complementar
// Dica: se modelar o problema para maximum clique, tenta transformar ver se o grafo complementar eh bipartido
// Recover: sao os mesmos vertices do maximum independent set
//
// Minimum Path Cover: menor numero de caminhos (disjuntos ou nao, da pra resolver os 2) para pegar todos os vertices do grafo
// Para modelar: duplica cada vertice, faz a aresta (a, b) se:
// se forem caminhos disjuntos, se existe aresta entre a e b
// se forem caminhos nao disjuntos, se existe caminho entre a e b
// Recover: roda o mincut e pega A_t e B_s (ou uns outros vertices, se vira ai)
//
// Maximum Closure: dado um grafo direcionado, vertices com pesos positivos ou negativos,
// existe aresta (u, v) se escolher u te obriga a pegar v (talvez seja o contrario, mas acho que ta certo), 
// quero saber o maximo (ou minimo) custo que posso conseguir
// primeiro, pega as SCC, depois cria um grafo em que se a[u]>0 entao existe uma aresta (src, u, a[u]),
// e se a[u]<0 entao existe uma aresta (u, snk, -a[u]), e as arestas normais tem capacidade inf
// agora roda o min-cut e a resposta eh a soma dos vertices que voce chega saindo de src
// Recover: sao os vertices que voce chega saindo de src
//
// Teorema de Dilworth: tamanho da maximum antichain = menor tamanho da chain decomposition (disjunta)
// Teorema de Mirsky: tamanho da maior chain = menor tamanho da antichain decomposition (disjunta, mas tanto faz)
// Teorema de Erdos-Szekeres: uma sequencia de pelo menos rs+1 numeros reais tem uma subsequencia crescente
// de tamanho r+1 ou uma subsequencia decrescente de tamanho s+1
// Dica 1: as vezes vc usa o teorema pra chegar em outro problema, nao um grafo. Por exemplo, LIS
// Dica 2: as vezes o numero de caminhos disjuntos eh igual ao numero de caminhos nao necessariamente disjuntos,
// ai nao precisa construir as O(N^2) arestas. Por exemplo, se o dag for de subsets


struct dinitz {
	const bool scaling = false; // com scaling -> O(nm log(MAXCAP)),
	int lim;                    // com constante alta
	struct edge {
		int to, cap, rev, flow;
		bool res;
		edge(int to_, int cap_, int rev_, bool res_)
			: to(to_), cap(cap_), rev(rev_), flow(0), res(res_) {}
	};

	vector<vector<edge>> g;
	vector<int> lev, beg;
	ll F;
	dinitz(int n) : g(n), F(0) {}

	void add(int a, int b, int c) {
		g[a].emplace_back(b, c, g[b].size(), false);
		g[b].emplace_back(a, 0, g[a].size()-1, true);
	}
	bool bfs(int s, int t) {
		lev = vector<int>(g.size(), -1); lev[s] = 0;
		beg = vector<int>(g.size(), 0);
		queue<int> q; q.push(s);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (auto& i : g[u]) {
				if (lev[i.to] != -1 or (i.flow == i.cap)) continue;
				if (scaling and i.cap - i.flow < lim) continue;
				lev[i.to] = lev[u] + 1;
				q.push(i.to);
			}
		}
		return lev[t] != -1;
	}
	int dfs(int v, int t, int f = INF) {
		if (!f or v == t) return f;
		for (int& i = beg[v]; i < g[v].size(); i++) {
			auto& e = g[v][i];
			if (lev[e.to] != lev[v] + 1) continue;
			int foi = dfs(e.to, t, min(f, e.cap - e.flow));
			if (!foi) continue;
			e.flow += foi, g[e.to][e.rev].flow -= foi;
			return foi;
		}
		return 0;
	}
	ll max_flow(int s, int t) {
		for (lim = scaling ? (1<<30) : 1; lim; lim /= 2)
			while (bfs(s, t)) while (int ff = dfs(s, t)) F += ff;
		return F;
	}
};

// Recupera as arestas do corte s-t
vector<pair<int, int>> get_cut(dinitz& g, int s, int t) {
	g.max_flow(s, t);
	vector<pair<int, int>> cut;
	vector<int> vis(g.g.size(), 0), st = {s};
	vis[s] = 1;
	while (st.size()) {
		int u = st.back(); st.pop_back();
		for (auto e : g.g[u]) if (!vis[e.to] and e.flow < e.cap)
			vis[e.to] = 1, st.push_back(e.to);
	}
	for (int i = 0; i < g.g.size(); i++) for (auto e : g.g[i])
		if (vis[i] and !vis[e.to] and !e.res) cut.emplace_back(i, e.to);
	return cut;
}
