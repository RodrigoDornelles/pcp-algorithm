clean:
	rm -f pcp_*

build: clean
	${CC} tools/pcp9_pos.c -o pcp9_pos
	${CC} tools/pcp9_slicer.c -o pcp9_slicer
	${CC} tools/pcp9_cousin.c -o pcp9_cousin
	${CC} tools/pcp9_palindrome.c -o pcp9_palindrome