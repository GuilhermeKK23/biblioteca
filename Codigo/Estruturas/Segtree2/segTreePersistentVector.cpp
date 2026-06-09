// SegTree Persistente com vector
//
// Constante eh meio ruim, mas eh mais intuitivo de codar e modificar
// Eh uma seg esparsa, entao os indices podem ser grandes ou negativos
// Update retorna a nova raiz
//
// Kth retorna o K-esimo elemento no range [L, R]
// root[i] guarda uma seg de frequência do prefixo i
// Para calcular o K-esimo de [l, r], chama:
// k = seg.kth(root[l-1], root[r], -MAX, MAX, k)
// da pra generalizar essa ideia para K-esimo elemento do caminho de u ate v em uma arvore

#define pb push_back

struct Perseg{
    vector<int> seg, e, d;
    Perseg() : seg(2), e(2), d(2) {};

    int create(){
        seg.pb(0); e.pb(0); d.pb(0);
        return seg.size()-1;
    }

    void copy(int pos, int novo){
        seg[novo] = seg[pos], e[novo] = e[pos], d[novo] = d[pos];
    }

    int update(int pos, int ini, int fim, int id, int val){
        if(id<ini || id>fim) return pos;
        int novo = create(); copy(pos, novo);
        if(ini==fim){
            seg[novo] = val;
            return novo;
        }
        int m = (ini+fim) >> 1;
        if(id<=m){ int aux = update(e[pos], ini, m, id, val); e[novo] = aux; }
        else{ int aux = update(d[pos], m+1, fim, id, val); d[novo] = aux; }
        seg[novo] = seg[e[novo]] + seg[d[novo]];
        return novo;
    }

    int query(int pos, int ini, int fim, int l, int r){
        if(r<ini || l>fim || pos==0) return 0;
        if(l<=ini && fim<=r) return seg[pos];
        int m = (ini+fim) >> 1;
        return query(e[pos], ini, m, l, r) + query(d[pos], m+1, fim, l, r);
    }

    int kth(int pos1, int pos2, int ini, int fim, int k){
		if(ini==fim) return ini;
		int m = (ini+fim)>>1;
		int cnt = seg[e[pos2]] - seg[e[pos1]];
		if(cnt>=k) return kth(e[pos1], e[pos2], ini, m, k);
		else return kth(d[pos1], d[pos2], m+1, fim, k-cnt);
	}
};