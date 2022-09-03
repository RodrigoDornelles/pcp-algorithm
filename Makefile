TIER ?= 1

ifeq ($(TIER), 1)
OFFSETS ?= 0 1 2 3 4 5 6 7 8
else ifeq ($(TIER), 2)
OFFSETS ?= 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
endif

.PHONY: tests

all:
	@echo "usage:"
	@echo " > make clean"
	@echo " > make all-deps"
	@echo " > make multi-run"
	@echo " > make multi-kill"
	@echo " > make single-run"

clean:
	rm -Rf bin/* *.o test_* *.out *.dSYM *.gc*

build: bin/pcp_slicer bin/pcp_cousin bin/pcp_palindrome bin/pcp_pos
	@echo all done!

bin/%:
	${CC} ${CC_FLAGS} tools/$*.c -o bin/$*

single-run: build
	for i in ${OFFSETS}; do \
		./bin/pcp_slicer -T${TIER} -O$$i -H -idata/sausage.txt |\
		./bin/pcp_palindrome -T${TIER} |\
		./bin/pcp_cousin -T${TIER} -f ;\
	done

multi-run: build
	for i in ${OFFSETS}; do \
		(./bin/pcp_slicer -T${TIER} -O$$i -H -idata/sausage.txt |\
		./bin/pcp_palindrome -T${TIER} |\
		./bin/pcp_cousin -T${TIER} -f\
		) & true ;\
	done

multi-kill:
	killall -q pcp_slicer pcp_cousin pcp_palindrome pcp_pos; true

tests:
	${CC} ${CC_FLAGS} tests/tests_str.c -o test_str
	${CC} ${CC_FLAGS} tests/tests_opt.c -o test_opt
	${CC} ${CC_FLAGS} tests/tests_math.c -o test_math
	./test_math ${TESTS_FLAGS} && \
	./test_opt ${TESTS_FLAGS} && \
	./test_str ${TESTS_FLAGS}

tests-coverage:
	make tests \
	TESTS_FLAGS="${TESTS_FLAGS}" \
	CC_FLAGS="${CC_FLAGS} -w -coverage -g"
	gcov *.gcno
