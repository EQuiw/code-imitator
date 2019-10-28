// Bathroom Stalls.cpp : Defines the entry point for the console application.
//

#include <algorithm>
#include <iostream>

#include <map>
using namespace std;
class Tree {
public:
  struct Node {
    int s, e, l, r;
    Node *left, *right, *parent;
    Node() {}
    Node(int s, int e) : s(s), e(e) {
      if ((e - s - 1) % 2) {
        l = r = (e - s - 1) / 2;
      } else {
        r = (e - s - 1) / 2;
        l = r - 1;
      }
      left = nullptr;
      right = nullptr;
      parent = nullptr;
    }
    void divide() {
      int sr = (e - s) / 2;
      left = new Node(s, sr);
      right = new Node(sr, e);
      left->parent = this;
      right->parent = this;
    }
  };
  Node *root;
  Tree(int s, int e) { root = new Node(s, e); }
  Node insert() {
    Node *cur = root;
    while (cur->left != nullptr) {
      Node *tmp = cur->left;
      int leftMin = min(cur->left->l, cur->left->r);
      int leftMax = max(cur->left->l, cur->left->r);
      int rightMin = min(cur->right->l, cur->right->r);
      int rightMax = max(cur->right->l, cur->right->r);

      if (leftMin < rightMin || (leftMin == rightMin && leftMax < rightMax))
        tmp = cur->right;
      cur = tmp;
    }
    Node res = *cur;
    cur->divide();
    update(cur);
    return res;
  }
  void update(Node *cur) {
    while (true) {
      Node *tmp = cur->left;
      int leftMin = min(cur->left->l, cur->left->r);
      int leftMax = max(cur->left->l, cur->left->r);
      int rightMin = min(cur->right->l, cur->right->r);
      int rightMax = max(cur->right->l, cur->right->r);
      if (leftMin < rightMin || (leftMin == rightMin && leftMax < rightMax)) {
        tmp = cur->right;
      }
      cur->l = tmp->l;
      cur->r = tmp->r;
      if (cur->parent == nullptr)
        break;
      cur = cur->parent;
    }
  }
};

int main() {
  long long int t, n, k;
  Tree::Node res;
  map<long long int, long long int> mapa;

  cin >> t;
  for (int j = 1; j <= t; ++j) {

    cin >> n >> k;
    mapa.clear();
    mapa[n] = 1;
    int res;
    auto it = mapa.begin();
    int ile = 0;
    int sum = 0;
    while (it != mapa.end() && it->first != 0) {
      if (k > it->second)
        k -= it->second;
      else {
        res = it->first;
        break;
      }
      sum += it->second;
      mapa[it->first / 2] += it->second;
      ile++;

      mapa[it->first - it->first / 2 - 1] += it->second;
      it--;
    }
    cout << "Case #" << j << ": " << max(res / 2, res - res / 2 - 1) << " "
         << min(res / 2, res - res / 2 - 1) << "\n";
  }
  return 0;
}
