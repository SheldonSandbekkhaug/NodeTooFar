#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <map>      // map
#include <list>     // list

#include "NodeTooFar.h"

using namespace std;

int caseNum = 1;

map<int, Node> parse_case(istream& r, int num_connections)
{
  string s;
  map<int, Node> network;
  for(int i=0; i < num_connections;)
  {
    getline(r, s);
    istringstream line(s);

    // j, k is a connection between nodes
    int j = 0;
    while (line >> j)
    {
      int k;
      line >> k;

      updateNetwork(network, j);
      network[j].store(k);

      updateNetwork(network, k);
      network[k].store(j);

      ++i;
    }
  }

  return network;
}


void updateNetwork(map<int, Node>& network, int id)
{
  // Try to find that specified node
  auto n1 = network.find(id);
  if (n1 == network.end())
  {
    Node newNode(id);
    network[newNode.id] = newNode;
  }
}


void solve_case(map<int, Node> network, vector<pair<int, int>> queries,
    ostream& w)
{
  for (unsigned int i = 0; i < queries.size(); ++i)
    execute_query(queries[i], network, w);
}

void execute_query(pair<int, int> p, map<int, Node> network, ostream &w)
{
  // Insert at front, remove from back
  list<Node> to_explore;
  map<int, int> distance_left; // <nodeID, TTL when reached>

  // Initialize every entry in distance_left to have value -1
  for (auto it = network.begin(); it != network.end(); ++it)
  {
    distance_left[it->first] = -1;
  }

  // Initialize breadth-first search
  int nodeID = p.first;
  distance_left[nodeID] = p.second;

  to_explore.push_front(network[nodeID]);

  // Use breadth-first search
  while(to_explore.size() > 0)
  {
    // Get the next Node
    Node t = to_explore.front();
    to_explore.pop_front();

    // Add all of t's neighbors that haven't been visited yet
    for (unsigned int i = 0; i < t.connections.size(); ++i)
    {
      int old_ttl = distance_left[t.connections[i]];

      // Update entry in the TTL map
      if (old_ttl < 0)
      {
        distance_left[t.connections[i]] = distance_left[t.id] - 1;       
      }
    }  
  }

  // Find all nodes that have TTL of less than 0
  int unreachable = 0;
  for (auto it = distance_left.begin(); it != distance_left.end(); ++it)
  {
    if (it->second < 0)
      ++unreachable;
  }

  print_results(unreachable, p.second, w);
}


void print_results(int num_nodes, int ttl, ostream &w)
{
  w << "Case " << caseNum << ": ";
  w << num_nodes << " nodes not reachable from node " << num_nodes;
  w << " with TTL = " << ttl << "." << endl;
  ++caseNum;
}

vector<pair<int, int>> get_queries(istream& r)
{
  vector<pair<int, int>> queries;

  string s;
  getline(r, s);
  istringstream line(s);

  int startNode = 0;
  while (line >> startNode)
  {
    int ttl;
    line >> ttl;

    // Break condition
    if (startNode == 0 && ttl == 0)
      break;

    // Make a pair and add it to the vector
    queries.push_back(make_pair(startNode, ttl));
  }

  return queries;
}


void node_too_far_solve(istream& r, ostream& w)
{
  string s;
  int num_connections = 1;
  while(num_connections != 0)
  {
    // Get the number of connections in the next case
    num_connections = next_int(r);

    map<int, Node> network = parse_case(r, num_connections);

    // Pairs of node, TTL
    vector<pair<int, int>> queries = get_queries(r);

    solve_case(network, queries, w);
    getline(r, s); // Ignore blank line
  }
}


int next_int(istream& r)
{
  string s;
  getline(r,s);

  istringstream int_in(s);
  int i;
  int_in >> i;

  return i;
}


Node::Node()
{
  // Empty
}

Node::Node(int myID)
{
  id = myID;
}

void Node::store(int theirID)
{
  connections.push_back(theirID);
}
