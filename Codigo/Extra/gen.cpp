// Gerador, Tester e Hash
//

int main(int argc, char** argv){
    mt19937 rng(atoi(argv[1]));
}

// test.sh
// Para usar: bash test.sh
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

// hash.sh
sed -n $2','$3' p' $1 | sed '/^#w/d' | cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6

// hash_file.sh
// Para usar: bash hash_file.sh A.cpp
while IFS= read -r l; do
	echo "$l" > line.txt
    hl=$(bash hash.sh line.txt 1 1000 | cut -c1-3)
	echo -e "$hl $l"
done < "$1"