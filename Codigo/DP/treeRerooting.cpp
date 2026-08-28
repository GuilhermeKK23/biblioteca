// Tree Rerooting DP
//
// Usa um Divide and Conquer pra calcular a dp de forma facil, com um log a mais
// Calcula ans[i] para todo vertice i da arvore
// Soh precisa saber como calcular a dp pra raiz e como combinar a resposta do filho no pai
// Complexidade: O(NlogN)

using DP_Type = long long;
vector<pair<int,int>> adj[MAXN];
DP_Type dp[MAXN];  //dp down
DP_Type ans[MAXN]; 
map<pair<int,int>,bool>custo;

// Valor inicial de cada node
DP_Type get_default(int u) {
    return 0; 
}

// Como combinar a resposta de um filho (v) no pai (u)
DP_Type combine(DP_Type nodeDP, DP_Type neiDP, int u, pair<int,int>edge) {
    return (nodeDP+neiDP+(edge.second));
}

// Se eh distancia, seria dipo +1 para contar o vertice em si...
DP_Type finalize_dp(DP_Type nodeDP, int u, int p) {
    return nodeDP;
}

//Caixa preta completa

void dfs1(int u, int p) {
    dp[u] = get_default(u);
    for (auto v : adj[u]) {
        if (v.first == p) continue;
        dfs1(v.first, u);
        dp[u] = combine(dp[u], dp[v.first], u,v);
    }
    dp[u] = finalize_dp(dp[u], u, p);
}

void dfs2(int u, int p, DP_Type up_val) {
    vector<pair<int,int>> neighbors;
    vector<DP_Type> A;
    
    for (auto v : adj[u]) {
        neighbors.push_back(v);
        if (v.first == p) A.push_back(up_val);
        else A.push_back(dp[v.first]);
    }
    
    int deg = neighbors.size();
    vector<DP_Type> exc(deg, get_default(u));
    auto calc_exclusive = [&](auto& self, int l, int r, DP_Type curr) -> void {
        if (l == r) {
            exc[l] = curr;
            return;
        }
        int mid = l + (r - l) / 2;
        
        DP_Type left_val = curr;
        for (int i = mid + 1; i <= r; i++) left_val = combine(left_val, A[i], u, neighbors[i]);
        self(self, l, mid, left_val);
        
        DP_Type right_val = curr;
        for (int i = l; i <= mid; i++) right_val = combine(right_val, A[i], u, neighbors[i]);
        self(self, mid + 1, r, right_val);
    };
    
    if (deg > 0) {
        calc_exclusive(calc_exclusive, 0, deg - 1, get_default(u));
    }
    
    DP_Type root_val = get_default(u);
    for (int i = 0; i < deg; i++) {
        root_val = combine(root_val, A[i], u, neighbors[i]);
    }
    ans[u] = finalize_dp(root_val, u, -1);
    
    for (int i = 0; i < deg; i++) {
        int v = neighbors[i].first;
        if (v != p) {
            DP_Type next_up_val = finalize_dp(exc[i], u, v);
            dfs2(v, u, next_up_val);
        }
    }
}

void run_rerooting() {
    dfs1(1, 0); // Considerando nos indexados em 1 e 0 como nulo
    dfs2(1, 0, get_default(1));
}