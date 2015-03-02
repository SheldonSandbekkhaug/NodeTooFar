#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <map>      // map
#include <list>     // list

#include "NodeTooFar.h"

using namespace std;

int caseNum = 1;

void parse_case(istream& r, int num_connections,
	map<int, Node>& network, vector<pair<int, int>>& queries)
{
  pair<int, int> this_pair(-1, -1); // Default
  int i = 0;
  while(this_pair.first != 0 || this_pair.second != 0)
  {
    int j;
    r >> j;
    int k;
    r >> k;

    if (i < num_connections)
    {
      // Make connections
      updateNetwork(network, j);
      network[j].store(k);

      updateNetwork(network, k);
      network[k].store(j);

      ++i;
    }
    else
    {
      // Make pairs for queries
      this_pair = make_pair(j, k);

      if (j != 0 || k != 0)
        queries.push_back(this_pair);
    }
  }
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
  bool first_query = true;
  for (unsigned int i = 0; i < queries.size(); ++i)
  {
    if (!first_query)
      w << endl;
    execute_query(queries[i], network, w);
    first_query = false;
  }
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
      int neighbor_id = t.connections[i];
      int old_distance_left = distance_left[neighbor_id];

      // Update entry in the TTL map
      if (old_distance_left < distance_left[t.id] - 1)
      {
        distance_left[neighbor_id] = distance_left[t.id] - 1;

        if (distance_left[neighbor_id] > 0)
        {
          // Add this neighbor to the to-be-explored list
          Node neighbor = network[neighbor_id];
          to_explore.push_front(neighbor);
        }
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

  print_results(unreachable, p.first, p.second, w);
}


void print_results(int num_nodes, int start, int ttl, ostream &w)
{
  w << "Case " << caseNum << ": ";
  w << num_nodes << " nodes not reachable from node " << start;
  w << " with TTL = " << ttl << ".";
  ++caseNum;
}


void node_too_far_solve(istream& r, ostream& w)
{
  string s;
  int num_connections = 1;
  int iterations = 0;
  while(num_connections != 0)
  {
    while (getline(r, s)) // Ignore blank lines
    {
      if (!all_whitespace(s) || s != "")
        break;
    }

    // Get the number of connections
    istringstream int_in(s);
    if (!(int_in >> num_connections))
      return;

    // Exit condition
    if (num_connections == 0)
      return;

    map<int, Node> network;
    vector<pair<int, int>> queries;
    
    parse_case(r, num_connections, network, queries);

    if (iterations > 0)
      w << endl;

    solve_case(network, queries, w);
    ++iterations;
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


int next_int(string s)
{
  istringstream int_in(s);
  int i;
  int_in >> i;

  return i;
}

bool all_whitespace(string s)
{
  for (unsigned int i = 0; i < s.size(); ++i)
  {
    if (!isspace(s[i]))
      return false;
  }

  return true;
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
