// SegTree Esparsa com lazy com vector
//
// Constante eh meio ruim, mas eh mais intuitivo de codar e modificar
// Da pra dar reserve no comeco pro push_back ficar mais barato

#define pb push_back

struct Sparseg{
	vector<int> seg, lz, e, d;

	Sparseg() : seg(2), lz(2), e(2), d(2) {}

	int create(){
		seg.pb(0); lz.pb(0); e.pb(0); d.pb(0);
		return seg.size()-1;
	}

	void refresh(int pos, int ini, int fim){
		if(lz[pos]==0) return;

		seg[pos] += lz[pos];
		if(ini<fim){
			if(e[pos]==0){ int aux = create(); e[pos] = aux; }
			if(d[pos]==0){ int aux = create(); d[pos] = aux; }
			lz[e[pos]] += lz[pos];
			lz[d[pos]] += lz[pos];
		}

		lz[pos] = 0;
	}

	void update(int pos, int ini, int fim, int l, int r){
		refresh(pos, ini, fim);
		if(fim<l || r<ini) return;
		if(l<=ini && fim<=r){
			lz[pos]++;
			refresh(pos, ini, fim);
			return;
		}
		int m = (ini+fim)>>1;
		if(e[pos]==0){ int aux = create(); e[pos] = aux; }
		if(d[pos]==0){ int aux = create(); d[pos] = aux; }
		update(e[pos], ini, m, l, r);
		update(d[pos], m+1, fim, l, r);
		seg[pos] = max(seg[e[pos]], seg[d[pos]]);
	}

	int query(int pos, int ini, int fim, int l, int r){
		refresh(pos, ini, fim);
		if(fim<l || r<ini) return 0;
		if(l<=ini && fim<=r) return seg[pos];
		int m = (ini+fim)>>1;
		return max(query(e[pos], ini, m, l, r), query(d[pos], m+1, fim, l, r));
	}
};