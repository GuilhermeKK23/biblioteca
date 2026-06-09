// SegTree Persistente com Lazy com vector
//
// Constante é meio ruim, mas é mais intuitivo de codar e modificar
// É uma seg esparsa, então os índices podem ser grandes ou negativos
// Update retorna a nova raiz

#define int long long
#define pb push_back

struct Perseg{
	vector<int> seg, lz, e, d;

	Perseg() : seg(2), lz(2), e(2), d(2) {}

	int create(){
		seg.pb(0); lz.pb(0); e.pb(0); d.pb(0);
		return seg.size()-1;
	}

	void copy(int pos, int novo){
		seg[novo] = seg[pos], lz[novo] = lz[pos], e[novo] = e[pos], d[novo] = d[pos];
	}

	int newlazynode(int pos, int ini, int fim, int val){
		int novo = create(); copy(pos, novo);
		lz[novo] += val;
		seg[novo] = seg[pos] + (fim-ini+1)*val;
		return novo;
	}

	void refresh(int pos, int ini, int fim){
		if(lz[pos]==0) return;

		if(ini<fim){
			int m = (ini+fim)>>1, aux;
			aux = newlazynode(e[pos], ini, m, lz[pos]); e[pos] = aux;
			aux = newlazynode(d[pos], m+1, fim, lz[pos]); d[pos] = aux;
		}

		lz[pos] = 0;
	}

	int update(int pos, int ini, int fim, int l, int r, int val){
		refresh(pos, ini, fim);
		if(r<ini || fim<l) return pos;
		if(l<=ini && fim<=r) return newlazynode(pos, ini, fim, val);
		int m = (ini+fim)>>1, aux;
		int novo = create(); copy(pos, novo);
		aux = update(e[novo], ini, m, l, r, val); e[novo] = aux;
		aux = update(d[novo], m+1, fim, l, r, val); d[novo] = aux;
		seg[novo] = seg[e[novo]] + seg[d[novo]];
		return novo;
	}

	int query(int pos, int ini, int fim, int l, int r){
		refresh(pos, ini, fim);
		if(r<ini || fim<l) return 0;
		if(l<=ini && fim<=r) return seg[pos];
		int m = (ini+fim)>>1;
		return query(e[pos], ini, m, l, r) + query(d[pos], m+1, fim, l, r);
	}
};