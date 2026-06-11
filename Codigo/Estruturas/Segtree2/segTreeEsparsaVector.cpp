// SegTree Esparsa com vector
//
// Constante eh meio ruim, mas eh mais intuitivo de codar e modificar
// Find retorna o indice de val

#define pb push_back

struct Sparseg{
    vector<int> seg;
    vector<int> e;
    vector<int> d;

    Sparseg() : seg(2), e(2), d(2) {}

    int create(){
        seg.pb(0); e.pb(0); d.pb(0);
        return seg.size()-1;
    }

    void update(int pos, int ini, int fim, int id, int val){
        if(id<ini || fim<id) return;
        if(ini==fim){
            seg[pos] = val;
            return;
        }
        int m = (ini+fim)>>1;
        if(e[pos]==0){ int aux = create(); e[pos] = aux; }
        if(d[pos]==0){ int aux = create(); d[pos] = aux; }
        update(e[pos], ini, m, id, val);
        update(d[pos], m+1, fim, id, val);
        seg[pos] = seg[e[pos]] + seg[d[pos]];
    }

    int query(int pos, int ini, int fim, int l, int r){
        if(fim<l || r<ini) return 0;
        if(l<=ini && fim<=r) return seg[pos];
        int m = (ini+fim)>>1;
        return query(e[pos], ini, m, l, r) + query(d[pos], m+1, fim, l, r);
    }

    int find(int pos, int ini, int fim, int val){
        if(ini==fim) return ini;
        int m = (ini+fim)>>1;
        if(e[pos]==0){ int aux = create(); e[pos] = aux; }
        int esq = query(e[pos], ini, m, ini, m);
        if(val<=esq){
            return find(e[pos], ini, m, val);
        }else{
            if(d[pos]==0){ int aux = create(); d[pos] = aux; }
            return find(d[pos], m+1, fim, val - esq);
        }
    }
};