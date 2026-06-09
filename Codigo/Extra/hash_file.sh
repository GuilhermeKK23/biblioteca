while IFS= read -r l; do
	echo "$l" > line.txt
    hl=$(bash hash.sh line.txt 1 1000 | cut -c1-3)
	echo -e "$hl $l"
done < "$1"