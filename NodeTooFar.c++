#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <vector>   // vector

#include "NodeTooFar.h"

using namespace std;

string read_case(istream& r)
{
  string out = "";
  string s;
  while(getline(r, s))
  {
    if(s == "")
      break;
    out += s + "\n";
  }

  // Removes trailing newline
  out = out.substr(0, out.length() - 1);

  assert("" != out);

  return out;
}

void solve_case(istream& r, ostream& w)
{

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
  getline(r,s);
  istringstream sin(s); // Get number of elections
  int i;
  sin >> i;
  getline(r,s); // Ignores the expected blank line
  for(;i>0;i--)
  {
    istringstream input(read_case(r));

    solve_case(input, w);
    if(i>1)
      w << "\n";
  }
}