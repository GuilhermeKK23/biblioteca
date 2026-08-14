// Functional Graph reduzido
//
// Template mais fraco, mas mais legivel
// Para calcular as coisas, chama lenhadora(n, p), onde n-1
// eh o maior vertice e p eh o vector de pai
// eh bem facil modificar para calcular mais coisa

namespace func_graph{
	int n;
	bool marc[MAX];
	int pai[MAX], ingrau[MAX], prof[MAX], tam[MAX];

	void achei_ciclo(int ini){
		int t = 1, cur = ini;
		cur = pai[cur];
		while(cur!=ini){
			cur = pai[cur];
			++t;
		}

		marc[cur] = 1, tam[cur] = t;
		cur = pai[cur];
		while(cur!=ini){
			marc[cur] = 1, tam[cur] = t;
			cur = pai[cur];
		}
	}

	void lenhadora(int n, vector<int> &p){
		for(int i=0; i<n; ++i) pai[i] = p[i], ++ingrau[pai[i]];

		queue<int> q;
		for(int i=0; i<n; ++i) if(ingrau[i]==0) q.push(i);

		vector<int> proc;
		while(q.size()){
			int cur = q.front(); q.pop();
			marc[cur] = 1;
			proc.pb(cur);

			--ingrau[pai[cur]];
			if(ingrau[pai[cur]]==0) q.push(pai[cur]);
		}

		for(int i=0; i<n; ++i) if(marc[i]==0) achei_ciclo(i);

		for(int i=proc.size()-1; i>=0; --i){
			int cur = proc[i];
			prof[cur] = prof[pai[cur]]+1;
			tam[cur] = tam[pai[cur]];
		}
	}
}