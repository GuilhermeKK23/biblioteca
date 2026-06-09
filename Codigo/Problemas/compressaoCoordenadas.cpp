// Compressao de Coordenadas
//
// Coloca todos os valores que voce quer comprimir em cc
// Para comprimir, faz a[i] = comp(a[i])
// Para descomprimir, faz a[i] = descomp(a[i])

sort(cc.begin(), cc.end());
cc.erase(unique(cc.begin(), cc.end()), cc.end());
auto comp = [&](int x){ return (lower_bound(cc.begin(), cc.end(), x) - cc.begin() + 1); };
auto descomp = [&](int x){ return cc[x-1]; };