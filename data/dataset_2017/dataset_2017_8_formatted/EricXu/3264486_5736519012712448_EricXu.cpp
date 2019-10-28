#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <utility>
using namespace std;

int bfs(char *g, int ars, int size) {
  int i, j;
  set<string> vis;
  queue<pair<string, int>> v;
  string current = "", goal = "";
  for (i = 0; i < ars; i++)
    goal += "+";
  for (i = 0; i < ars; i++)
    current += g[i];
  v.push(make_pair(current, 0));
  while (!v.empty()) {
    string temp = v.front().first, copy = v.front().first;
    vis.insert(temp);
    int steps = v.front().second;
    v.pop();
    if (temp == goal)
      return steps;
    for (i = 0; i <= ars - size; i++) {
      for (j = i; j < i + size; j++) {
        if (temp[j] == '+')
          temp[j] = '-';
        else
          temp[j] = '+';
      }
      if (vis.find(temp) == vis.end())
        v.push(make_pair(temp, steps + 1));
      temp = copy;
    }
  }
  return -1;
}

int main() {
  ifstream infile;
  ofstream outfile;
  infile.open("pan.in");
  outfile.open("pan.txt");
  int i, j, t, size;
  infile >> t;
  string temp;
  for (i = 0; i < t; i++) {
    infile >> temp >> size;
    char *g = new char[temp.size()];
    for (j = 0; j < temp.size(); j++)
      g[j] = temp[j];
    int ans = bfs(g, temp.size(), size);
    if (ans == -1)
      outfile << "Case #" << i + 1 << ": IMPOSSIBLE" << endl;
    else
      outfile << "Case #" << i + 1 << ": " << ans << endl;
  }
  return 0;
}
