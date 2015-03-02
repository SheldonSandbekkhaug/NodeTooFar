#ifndef NodeTooFar_h
#define NodeTooFar_h

#include <iostream> // istream, ostream
#include <string>   // string
#include <vector>
#include <map>
#include <utility> // pair, make_pair

using namespace std;

class Node
{
  public:
    int id;
    vector<int> connections;

    Node();
    Node(int myID);
    void store(int theirID);
};

/**
 * Read in a single test case. Construct a map of <int, Node>
 */
map<int, Node> parse_case(istream& r, int num_connections);

/**
 *  Check if a node with id exists.
 *  If not, add it to the network.
 */
void updateNetwork(map<int, Node>& network, int id);

/**
 * Solve one test case.
 */
void solve_case(map<int, Node>, vector<pair<int, int>> queries, ostream& w);

/**
 * Gets all queries for this case
 */
vector<pair<int, int>> get_queries(istream &r);

/**
 * Solve one query
 */
void execute_query(pair<int, int>, map<int, Node>, ostream &w);

/**
 * Print the input case results.
 */
void print_results(int num_nodes, int start, int ttl, ostream &w);

/**
 * The "main" function of the program.
 */
void node_too_far_solve(istream& r, ostream& w);

/**
 * Gets the next integer from the input stream.
 */
int next_int(istream& r);


#endif
