MAIN = scanner.o rbt.o gst.o bst.o tnode.o queue.o cda.o
OBJS =  integer.o real.o string.o $(MAIN)
OOPTS = -Wall -Wextra -g -std=c99 -c
LOPTS = -Wall -Wextra -g -std=c99
TESTDIR = testing/
TESTS = $(sort $(basename $(notdir $(wildcard $(TESTDIR)*.c))))
TREE-TESTS = t-0-0 t-0-1 t-0-2 t-0-3 t-0-4 t-0-5 t-0-6 t-0-7 t-0-8 t-0-9 t-0-10 trg-0-10

all : $(MAIN) trees
	cp -f trees $(TESTDIR)

copy : $(OBJS)
	cp -f *.o $(TESTDIR)
	cp -f *.h $(TESTDIR)
	cp -f ../objects/tnode.o .
	cp -f ../objects/bst.o .
	cp -f ../objects/gst.o .
	cp -f ../objects/rbt.o .

test: all
	gcc $(LOPTS) -o test $(OBJS) rbt-0-6.c
	valgrind --leak-check=full test

test-trees: all
	for x in $(TREE-TESTS); do \
			echo; echo -------; echo $$x-r.expected; echo -------; cat $(TESTDIR)$$x-r.expected; \
			./$(TESTDIR)trees -r $(TESTDIR)$$x.corpus $(TESTDIR)$$x.commands > $(TESTDIR)$$x-r.yours; \
			echo -------; echo $$x-r.yours; echo -------; cat $(TESTDIR)$$x-r.yours; echo -------; \
			cmp --silent $(TESTDIR)$$x-r.expected $(TESTDIR)$$x-r.yours && echo "PASSED" || echo "FAILED"; echo -------; \
			echo; echo -------; echo $$x-g.expected; echo -------; cat $(TESTDIR)$$x-g.expected; \
			./$(TESTDIR)trees -g $(TESTDIR)$$x.corpus $(TESTDIR)$$x.commands > $(TESTDIR)$$x-g.yours; \
			echo -------; echo $$x-g.yours; echo -------; cat $(TESTDIR)$$x-g.yours; echo -------; \
			cmp --silent $(TESTDIR)$$x-g.expected $(TESTDIR)$$x-g.yours && echo "PASSED" || echo "FAILED"; echo -------; \
	done

tester : all $(TESTS)
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
	gcc $(LOPTS) -o $(TESTDIR)$@ $< $(OBJS)

tnode.o : tnode.c tnode.h
	gcc $(OOPTS) tnode.c

bst.o : bst.c bst.h tnode.o queue.o
	gcc $(OOPTS) bst.c
	
gst.o : gst.c gst.h bst.o
	gcc $(OOPTS) gst.c

rbt.o : rbt.c rbt.h gst.o
	gcc $(OOPTS) rbt.c

trees: trees.c $(MAIN) string.o
	gcc $(LOPTS) -o trees trees.c $(MAIN) string.o

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

queue.o : queue.c queue.h cda.o
	gcc $(OOPTS) queue.c

da.o : da.c da.h
	gcc $(OOPTS) da.c

cda.o : cda.c cda.h
	gcc $(OOPTS) cda.c

integer.o: integer.c integer.h
	gcc $(OOPTS) integer.c

real.o: real.c real.h
	gcc $(OOPTS) real.c

string.o : string.c string.h
	gcc $(OOPTS) string.c

clean	:
		rm -f $(MAIN) *.o