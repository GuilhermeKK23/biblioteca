// Teorema Chines do Resto
//
// Combina equacoes modulares lineares: x = a (mod m)
// O m final eh o lcm dos m's, e a resposta eh unica mod o lcm
// Os m nao precisam ser coprimos
// Se nao tiver solucao, o 'a' vai ser -1
//
// Teorema: seja m = m_1 x m_2 x ... x m_k, m_i coprimos, entao o sistema
// a = a_1 (mod m_1), ..., a = a_k (mod m_k)
// tem solucao unica mod m
// Corolario: a equacao x = a (mod m) eh equivalente a
// x = a_1 (mod_1), ..., x = a_k (mod m_k)
// Se os m_i nao forem coprimos, eh so quebrar eles em fatores primos
//
// Problemas:
// Se quiser calcular alguma conta mod m, onde m nao eh primo mas eh livre de 
// quadrado e todo primo eh pequeno, dah pra usar Teorema de Lucas e o chines
// Se o juiz quiser que avise caso a resposta seja maior que 10^9, testa os pares
// de equacoes, e ve quando o m passa de 10^9. Quando passar, ou a resposta eh o a atual,
// ou eh maior que 10^9, ou nao tem resposta, entao basta testar esse valor nas outras
// equacoes

template<typename T> tuple<T, T, T> ext_gcd(T a, T b) {
    if (!a) return {b, 0, 1};
    auto [g, x, y] = ext_gcd(b%a, a);
    return {g, y - b/a*x, x};
}

template<typename T = ll> struct crt {
	T a, m;

	crt() : a(0), m(1) {}
	crt(T a_, T m_) : a(a_), m(m_) {}
	crt operator * (crt C) {
		auto [g, x, y] = ext_gcd(m, C.m);
		if ((a - C.a) % g) a = -1;
		if (a == -1 or C.a == -1) return crt(-1, 0);
		T lcm = m/g*C.m;
		T ans = a + (x*(C.a-a)/g % (C.m/g))*m;
		return crt((ans % lcm + lcm) % lcm, lcm);
	}
};
