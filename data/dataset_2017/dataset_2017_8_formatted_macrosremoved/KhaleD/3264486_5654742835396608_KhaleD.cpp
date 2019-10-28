#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef set<int> si;
typedef map<int, int> mii;

const int N = 1002;
int t, n, k;

int main() {
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);
  scanf("%d", &t);
  for (int testCase = (1); testCase <= (int)(t); ++testCase) {
    scanf("%d%d", &n, &k);

    priority_queue<int, vi> q;
    q.push(n);
    for (int i = (1); i <= (int)(k - 1); ++i) {
      int x = q.top();
      q.pop();
      if (x / 2)
        q.push(x / 2);
      if (x / 2 - (x % 2 == 0))
        q.push(x / 2 - (x % 2 == 0));
    }

    int x = q.top();
    int y = max(x / 2, x / 2 - (x % 2 == 0)),
        z = min(x / 2, x / 2 - (x % 2 == 0));
    printf("Case #%d: %d %d\n", testCase, y, z);
  }
}

// freopen("input.txt","r",stdin);
// freopen("output.txt","w",stdout);
// ios::sync_with_stdio(0);cin.tie(0);
