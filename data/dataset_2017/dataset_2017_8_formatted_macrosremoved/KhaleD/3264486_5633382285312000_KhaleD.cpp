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
int t, digits;
ll n;
bool dp[N][12];
string ans, nString;

bool biggerThanN(string x) {
  if (((int)(x).size()) < ((int)(nString).size()))
    return false;
  if (((int)(x).size()) > ((int)(nString).size()))
    return true;
  return x > nString;
}

string conv(ll x) {
  stringstream ss;
  ss << x;
  return ss.str();
}

void solve(int i, int p, string curr) {
  if (biggerThanN(curr)) {
    dp[i][p] = true;
    return;
  }
  if (i <= digits + 1 and curr != "") {
    if (((int)(curr).size()) > ((int)(ans).size()))
      ans = curr;
    if (((int)(curr).size()) == ((int)(ans).size()) and curr > ans)
      ans = curr;
  }
  if (i == digits + 1)
    return;
  if (dp[i][p])
    return;

  for (int j = (p); j <= (int)(9); ++j)
    solve(i + 1, j, curr + char(j + '0'));
}

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);
  scanf("%d", &t);
  for (int testCase = (1); testCase <= (int)(t); ++testCase) {
    cin >> n;
    digits = (int)log10(n) + 1;
    nString = conv(n);

    ans = "";
    memset(dp, 0, sizeof dp);
    solve(1, 1, "");
    printf("Case #%d: ", testCase);
    cout << (ans) << endl;
  }
}

// freopen("input.txt","r",stdin);
// freopen("output.txt","w",stdout);
// ios::sync_with_stdio(0);cin.tie(0);
