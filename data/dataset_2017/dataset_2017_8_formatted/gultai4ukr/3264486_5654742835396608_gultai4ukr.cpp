#include <bits/stdc++.h>

#define PAUSE system("pause")
#define LL long long int
#define LD long double
#define PB push_back
#define PF push_front
#define MP make_pair
#define FORi(i, a, b) for (int i = a; i < b; ++i)
#define FORd(i, a, b) for (int i = a; i > b; --i)

using namespace std;

struct Segment {
  LL l, r;
  LL center() { return (l + r) / 2; }
  LL left_dist() { return this->center() - this->l - 1; }
  LL right_dist() { return this->r - this->center() - 1; }
  LL min_dist() { return min(this->left_dist(), this->right_dist()); }
  LL max_dist() { return max(this->left_dist(), this->right_dist()); }
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
  FORi(testcase, 0, t) {
    LL n, k;
    fin >> n >> k;

    priority_queue<Segment, vector<Segment>, Magic> pq;
    Segment s = {0, n + 1};
    pq.push(s);
    FORi(i, 0, k) {
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
