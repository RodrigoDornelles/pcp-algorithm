TIER := 1

all:
	@echo "usage:"
	@echo " > make clean"
	@echo " > make all-deps"
	@echo " > make multi-run"
	@echo " > make single-run"

clean:
	rm -f bin/* *.o

all-deps: bin/pcp_slicer bin/pcp_cousin bin/pcp_palindrome bin/pcp_pos
	@

bin/%:
	${CC} ${CC_FLAGS} tools/$*.c -o bin/$*

single-run: all-deps
	for i in 1 2 3 4 5 6 7 8; do \
		./bin/pcp_slicer -T${TIER} -O$$i -H -idata/sausage.txt |\
		./bin/pcp_cousin -T${TIER} |\
		./bin/pcp_palindrome -T${TIER} -f |\
		(./bin/pcp_pos -T${TIER} -S -idata/sausage.txt||true);\
	done

multi-run: all-deps
	for i in 1 2 3 4 5 6 7 8; do \
		(./bin/pcp_slicer -T${TIER} -O$$i -H -idata/sausage.txt |\
		./bin/pcp_cousin -T${TIER} |\
		./bin/pcp_palindrome -T${TIER} -f\
		&& echo & true);\
	done

multi-kill:
	killall -q pcp_slicer pcp_cousin pcp_palindrome pcp_pos; true
