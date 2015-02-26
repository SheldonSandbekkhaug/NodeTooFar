all:

RunNodeTooFar: NodeTooFar.h NodeTooFar.c++ RunNodeTooFar.c++
	g++-4.8 -pedantic -std=c++11 -Wall NodeTooFar.c++ RunNodeTooFar.c++ -o RunNodeTooFar

Temptest: RunNodeTooFar test.in
	RunNodeTooFar < test.in > temptest.out

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunNodeTooFar
	rm -f RunNodeTooFar.tmp
	rm -f TestNodeTooFar
