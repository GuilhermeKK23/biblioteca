# test.sh
#
# Gera vários casos de teste e compara a solução principal com uma solução bruteforce
# Para usar, muda os nomes dos arquivos e roda bash test.sh
# A.cpp eh o codigo principal, a saida vai para out1
# brute.cpp eh o codigo para testar, a saida vai para out2
# gen.cpp eh o gerador de casos
g++ A.cpp -o solve
g++ brute.cpp -o brute
g++ gen.cpp -o gen

for((i=1; i<=1000; ++i)) do
    echo $i
    ./gen $i > in
    ./solve < in > out1
    ./brute < in > out2
    diff -w out1 out2 || break

done