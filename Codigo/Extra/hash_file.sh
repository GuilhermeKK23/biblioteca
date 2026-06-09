# hash_file.sh
#
# Gera o hash de cada linha do programa, para comparar com o hash da lib
# Para usar, cria também o hash.sh e roda:
# bash hash_file.sh A.cpp
# as linhas que só tem } geram hashs diferentes, mas o resto tá certo
while IFS= read -r l; do
	echo "$l" > line.txt
    hl=$(bash hash.sh line.txt 1 1000 | cut -c1-3)
	echo -e "$hl $l"
done < "$1"