// String Hashing
//
// Complexidades:
// construtor - O(|s|)
// operator() - O(1)

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

int uniform(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

template<int MOD> struct mini_hash {
    static int P;
    vector<ll> h, p;
    mini_hash(){}
    mini_hash(const string& s) : h(s.size()), p(s.size()) {
        p[0] = 1, h[0] = s[0];
        for (int i = 1; i < (int)s.size(); i++)
            p[i] = p[i - 1] * P % MOD, h[i] = (h[i - 1] * P + s[i]) % MOD;
    }
    ll operator()(){ // retorna hash s[0..s.size()-1]
        return h[h.size()-1];
    }
    ll operator()(int l, int r) { // retorna hash s[l...r]
        ll hash = h[r] - (l ? h[l - 1] * p[r - l + 1] % MOD : 0);
        return hash < 0 ? hash + MOD : hash;
    }
};
template<int MOD> int mini_hash<MOD>::P = uniform(256, MOD - 1); // l > |sigma|

struct super_hash {
    int k;
    mini_hash<(int)1e9+7> h1;
    mini_hash<(int)1e9+9> h2;
    //mini_hash<(int)1e9+21> h3;
    //mini_hash<(int)1e9+33> h4;

    super_hash() {}
    super_hash(const string& s, int num = 2) : k(num) {
        if (k >= 1) h1 = s;
        if (k >= 2) h2 = s;
        //if (k >= 3) h3 = s;
        //if (k >= 4) h4 = s;
    }

    vector<ll> operator()(){ // retorna hash s[0..s.size()-1]
        vector<ll> res;
        res.reserve(k);
        if (k >= 1) res.push_back(h1());
        if (k >= 2) res.push_back(h2());
        //if (k >= 3) res.push_back(h3());
        //if (k >= 4) res.push_back(h4());
        return res;
    }
    vector<ll> operator()(int l, int r) { // retorna hash s[l...r]
        vector<ll> res;
        res.reserve(k);
        if (k >= 1) res.push_back(h1(l, r));
        if (k >= 2) res.push_back(h2(l, r));
        //if (k >= 3) res.push_back(h3(l, r));
        //if (k >= 4) res.push_back(h4(l, r));
        return res;
    }
};