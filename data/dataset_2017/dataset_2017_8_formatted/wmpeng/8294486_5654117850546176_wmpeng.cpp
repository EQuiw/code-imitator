#include <bits/stdc++.h>
using namespace std;
int n, r, o, y, g, b, v;
struct Node {
  char c;
  Node *next;
};
void solve1() {
  // r,y,b
  int m[3];
  char mc[3];
  if (r >= y && y >= b) {
    m[0] = r;
    m[1] = y;
    m[2] = b;
    mc[0] = 'R';
    mc[1] = 'Y';
    mc[2] = 'B';
  } else if (r >= b && b >= y) {
    m[0] = r;
    m[1] = b;
    m[2] = y;
    mc[0] = 'R';
    mc[1] = 'B';
    mc[2] = 'Y';
  } else if (y >= r && r >= b) {
    m[0] = y;
    m[1] = r;
    m[2] = b;
    mc[0] = 'Y';
    mc[1] = 'R';
    mc[2] = 'B';
  } else if (y >= b && b >= r) {
    m[0] = y;
    m[1] = b;
    m[2] = r;
    mc[0] = 'Y';
    mc[1] = 'B';
    mc[2] = 'R';
  } else if (b >= y && y >= r) {
    m[0] = b;
    m[1] = y;
    m[2] = r;
    mc[0] = 'B';
    mc[1] = 'Y';
    mc[2] = 'R';
  } else if (b >= r && r >= y) {
    m[0] = b;
    m[1] = r;
    m[2] = y;
    mc[0] = 'B';
    mc[1] = 'R';
    mc[2] = 'Y';
  }
  if (m[0] > m[1] + m[2])
    cout << "IMPOSSIBLE" << endl;
  else {
    Node *last = NULL, *head;
    for (int i = 1; i <= m[0]; i++) {
      head = new Node();
      head->c = mc[0];
      head->next = last;
      last = head;
    }
    Node *temp = head;
    while (temp->next != NULL)
      temp = temp->next;
    temp->next = head;
    temp = head;
    for (int i = 1; i <= m[1]; i++) {
      Node *nod = new Node();
      nod->c = mc[1];
      nod->next = temp->next;
      temp->next = nod;
      temp = temp->next->next;
    }
    for (int i = 1; i <= m[2]; i++) {
      Node *nod = new Node();
      nod->c = mc[2];
      nod->next = temp->next;
      temp->next = nod;
      temp = temp->next->next;
    }
    temp = head;
    while (temp->next != head) {
      cout << temp->c;
      temp = temp->next;
    }
    cout << temp->c << endl;
  }
}
int main() {
  int t;
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-small-attempt0.out", "w", stdout);
  cin >> t;
  for (int I = 1; I <= t; I++) {
    printf("Case #%d: ", I);
    cin >> n >> r >> o >> y >> g >> b >> v;
    solve1();
  }
  return 0;
}
