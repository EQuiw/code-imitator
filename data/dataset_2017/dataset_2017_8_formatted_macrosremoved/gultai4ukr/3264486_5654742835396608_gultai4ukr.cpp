#include <bits/stdc++.h>
using namespace std;

struct Segment {
  long long int l, r;
  long long int center() { return (l + r) / 2; }
  long long int left_dist() { return this->center() - this->l - 1; }
  long long int right_dist() { return this->r - this->center() - 1; }
  long long int min_dist() {
    return min(this->left_dist(), this->right_dist());
  }
  long long int max_dist() {
    return max(this->left_dist(), this->right_dist());
  }
};

struct Magic {
  bool operator()(Segment &lhs, Segment &rhs) const {
    if (lhs.min_dist() == rhs.min_dist()) {
      if (lhs.max_dist() == rhs.max_dist()) {
        return lhs.center() > rhs.center();
      }
      return lhs.max_dist() < rhs.max_dist();
    }
    return lhs.min_dist() < rhs.min_dist();
  }
};

int main(int argc, char **argv) {
  ifstream fin("/home/roman/CodeliteProjects/Competitive/GCJ17_Quals/in.txt");
  ofstream fout("/home/roman/CodeliteProjects/Competitive/GCJ17_Quals/out.txt");

  int t;
  fin >> t;
  for (int testcase = 0; testcase < t; ++testcase) {
    long long int n, k;
    fin >> n >> k;

    priority_queue<Segment, vector<Segment>, Magic> pq;
    Segment s = {0, n + 1};
    pq.push(s);
    for (int i = 0; i < k; ++i) {
      s = pq.top();
      pq.pop();
      if (s.max_dist() > 0) {
        pq.push({s.l, s.center()});
        pq.push({s.center(), s.r});
      }
    }

    fout << "Case #" << testcase + 1 << ": " << s.max_dist() << ' '
         << s.min_dist() << endl;
  }

  fin.close();
  fout.close();
  return 0;
}
