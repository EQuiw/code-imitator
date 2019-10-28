#include <fstream>
#include <iostream>
#include <queue>
#include <utility>
using namespace std;

int main() {
  ifstream infile;
  ofstream outfile;
  infile.open("unicorn.in");
  outfile.open("unicorn.txt");
  int i, j, t, n, r, o, y, g, b, v;
  infile >> t;
  for (i = 0; i < t; i++) {
    infile >> n >> r >> o >> y >> g >> b >> v;
    if (r > n / 2 || y > n / 2 || b > n / 2) {
      outfile << "Case #" << i + 1 << ": IMPOSSIBLE" << endl;
      continue;
    }
    priority_queue<pair<int, char>> order;
    order.push(make_pair(r, 'R'));
    order.push(make_pair(y, 'Y'));
    order.push(make_pair(b, 'B'));
    char *circle = new char[n];
    for (j = 0; j < n; j++)
      circle[j] = ' ';
    char color = order.top().second;
    int amount = order.top().first;
    order.pop();
    int copy = n - amount, copy2 = amount;
    priority_queue<int> distances;
    while (copy > 0) {
      distances.push(copy / copy2);
      copy = copy - copy / copy2;
      copy2--;
    }
    j = 0;
    while (!distances.empty()) {
      circle[j] = color;
      j += distances.top() + 1;
      distances.pop();
    }
    char prev = color;
    color = order.top().second;
    amount = order.top().first;
    order.pop();
    for (j = 1; j < n; j++) {
      if (amount == 0)
        break;
      if (circle[j - 1] == prev) {
        circle[j] = color;
        amount--;
      }
    }
    color = order.top().second;
    for (j = 0; j < n; j++)
      if (circle[j] == ' ')
        circle[j] = color;
    outfile << "Case #" << i + 1 << ": ";
    for (j = 0; j < n; j++)
      outfile << circle[j];
    outfile << endl;
  }
  return 0;
}
