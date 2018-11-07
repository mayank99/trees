OBJS =  integer.o real.o string.o scanner.o bst.o tnode.o queue.o cda.o
# MAIN = amaze
OOPTS = -Wall -Wextra -g -std=c99 -c
LOPTS = -Wall -Wextra -g -std=c99
TESTDIR = testing/
TESTS = $(sort $(basename $(notdir $(wildcard $(TESTDIR)*.c))))

all : $(OBJS)
	cp -f *.o $(TESTDIR)
	cp -f *.h $(TESTDIR)

test : all $(TESTS)
	for x in $(TESTS); do \
			echo; echo -------; echo $$x.expected; echo -------; cat $(TESTDIR)$$x.expected; \
			./$(TESTDIR)$$x > $(TESTDIR)$$x.yours; \
			echo -------; echo $$x.yours; echo -------; cat $(TESTDIR)$$x.yours; echo -------; \
			cmp --silent $(TESTDIR)$$x.expected $(TESTDIR)$$x.yours && echo "PASSED" || echo "FAILED"; echo -------; \
	done
	
valgrind : all $(TESTS)
	for x in $(TESTS); do \
			valgrind --log-file=$(TESTDIR)$$x.valgrind $(TESTDIR)$$x; \
			echo; echo -------; echo $$x.valgrind; echo -------;  cat $(TESTDIR)$$x.valgrind; echo; \
	done

$(TESTS): %: $(TESTDIR)%.c all
	gcc -Wall -Wextra -g -o $(TESTDIR)$@ $< $(OBJS)

tnode.o : tnode.c tnode.h
	gcc $(OOPTS) tnode.c

bst.o : bst.c bst.h tnode.o queue.o
	gcc $(OOPTS) bst.c

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

queue.o : queue.c queue.h cda.o
	gcc $(OOPTS) queue.c

da.o : da.c da.h
	gcc $(OOPTS) da.c

cda.o : cda.c cda.h
	gcc $(OOPTS) cda.c

clean	:
		rm -f $(OBJS) $(MAIN)