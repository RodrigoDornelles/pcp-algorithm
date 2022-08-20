all:
	@echo "usage:"
	@echo " > make clean"
	@echo " > make all-deps"
	@echo " > make multi-run"
	@echo " > make single-run"

clean:
	rm -f bin/*

all-deps: bin/pcp_slicer bin/pcp_cousin bin/pcp_palindrome bin/pcp_pos
	@

bin/%:
	${CC} ${CC_FLAGS} tools/$*.c -o bin/$*

single-run: all-deps
	for i in 1 2 3 4 5 6 7 8; do \
		./bin/pcp_slicer -O$$i -H -idata/sausage.txt |\
		./bin/pcp_cousin |\
		./bin/pcp_palindrome -f |\
		(./bin/pcp_pos -S -idata/sausage.txt||true);\
	done
