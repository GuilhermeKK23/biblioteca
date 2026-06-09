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