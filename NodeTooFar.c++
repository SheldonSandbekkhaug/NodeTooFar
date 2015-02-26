#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <vector>   // vector

#include "NodeTooFar.h"

using namespace std;

string read_case(istream& r, int num_connections)
{
  return "TODO"; // TODO: implement this
}


void solve_case(istream& r, ostream& w)
{
  // TODO: implement
}


void print_results(int case_num, ostream &w)
{
  // TODO: real behavior
  int num_nodes = 0;
  int some_ttl = 0;
  w << num_nodes << " nodes not reachable from node 35 with TTL = " << some_ttl << endl;
}


void node_too_far_solve(istream& r, ostream& w)
{
  string s;
  int num_connections = 1;
  while(num_connections != 0)
  {
    // Ignore blank lines between cases
    while(getline(r, s))
    {
      if(s != "")
        break;
    }

    // Get the number of connections in the next case
    num_connections = next_int(r);

    istringstream one_case(read_case(r, num_connections));

    //solve_case(one_case, w);
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