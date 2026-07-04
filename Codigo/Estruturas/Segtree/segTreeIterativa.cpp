// SegTree Iterativa
//
// Consultas 0-based
// Valores iniciais devem estar em (seg[n], ... , seg[2*n-1])
// Query: soma do range [a, b]
// Update: muda o valor da posicao p para x
//
// Complexidades:
// build - O(n)
// query - O(log(n))
// update - O(log(n))

int seg[2 * MAX];
int n;

void build() {
	for (int i = n - 1; i; i--) seg[i] = seg[2*i] + seg[2*i+1];
}

int query(int a, int b) {
	int ret = 0;
	for(a += n, b += n; a <= b; ++a /= 2, --b /= 2) {
		if (a % 2 == 1) ret += seg[a];
		if (b % 2 == 0) ret += seg[b];
	}
	return ret;
}

void update(int p, int x) {
	seg[p += n] = x;
	while (p /= 2) seg[p] = seg[2*p] + seg[2*p+1];
}

// Quando a operacao eh nao comutativa
//
// 1) Definir 'struct node' implementando operacao
// 2) 'build' e 'update' continuam iguais
// 3) Alterar query da seguinte forma:
int query(int a, int b) {
    node ql, qr;
	for(a += n, b += n; a <= b; ++a /= 2, --b /= 2) {
		if (a % 2 == 1) ql = node(ql, seg[a]);
		if (b % 2 == 0) qr = node(seg[b], qr);
	}
	return node(ql, qr);
}
