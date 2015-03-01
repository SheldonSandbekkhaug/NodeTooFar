#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <map>      // map
#include <list>     // list

#include "NodeTooFar.h"

using namespace std;

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

      // Try to find that specified node
      auto n1 = network.find(j);
      if (n1 == network.end())
      {
        Node newNode(j);
        network[newNode.id] = newNode;
      }
      network[j].store(k);

      ++i;
    }
  }

  return network;
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
      auto neighbor = distance_left.find(t.connections[i]);

      if (neighbor == distance_left.end())
      {
        distance_left[t.connections[i]] = distance_left[t.id] - 1;
      }
    }
    
  }
  

}


void print_results(int case_num, ostream &w)
{
  // TODO: real behavior
  int num_nodes = 0;
  int some_ttl = 0;
  w << num_nodes << " nodes not reachable from node 35 with TTL = " << some_ttl << endl;
}

vector<pair<int, int>> get_queries(istream& r)
{
  vector<pair<int, int>> queries;

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
