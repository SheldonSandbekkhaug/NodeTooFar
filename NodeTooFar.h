#ifndef NodeTooFar_h
#define NodeTooFar_h

#include <iostream> // istream, ostream
#include <string>   // string
#include <vector>
#include <list>

using namespace std;

/**
 * Read in a single test case.
 */
string read_case(istream& r);

/**
 * Solve one test case.
 */
void solve_case(istream& r, ostream& w);

/**
 * Print the input case results.
 */
void print_results(int case_num, ostream &w);

/**
 * The "main" function of the program.
 */
void node_too_far_solve(istream& r, ostream& w);

#endif
