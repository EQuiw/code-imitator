// satyaki3794
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;

ll pwr(ll base, ll p, ll mod = (1000000007LL)) {
  ll ans = 1;
  while (p) {
    if (p & 1)
      ans = (ans * base) % mod;
    base = (base * base) % mod;
    p /= 2;
  }
  return ans;
}

ll gcd(ll a, ll b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

int n, red, orange, yellow, green, blue, violet;
vector<string> arr[5];

string yolo(int x) {
  string z = arr[x].back();
  arr[x].pop_back();
  return z;
}

string check(int x) {

  int y = -1, z = -1;
  for (int i = 1; i <= 3; i++) {
    if (i == x)
      continue;
    if (y == -1)
      y = i;
    else
      z = i;
  }

  int xsz = (int)arr[x].size(), ysz = (int)arr[y].size(),
      zsz = (int)arr[z].size();
  if (ysz + zsz < xsz)
    return "";
  if (ysz < zsz) {
    swap(y, z);
    swap(ysz, zsz);
  }

  // cout<<x<<" "<<y<<" "<<z<<endl;

  if (ysz >= xsz) {
    int rem = ysz - xsz;
    if (rem > zsz)
      return "";
    zsz -= rem;
    string ans = "";
    for (int i = 0; i < xsz; i++) {
      ans += yolo(x) + yolo(y);
      if (i == 0) {
        while (rem--) {
          ans += yolo(z) + yolo(y);
        }
      }
      if (i < zsz)
        ans += yolo(z);
    }
    return ans;
  } else {
    int rem = zsz - (xsz - ysz);
    if (rem > ysz)
      return "";
    string ans = "";
    for (int i = 0; i < xsz; i++) {
      ans += yolo(x);
      if (i < ysz) {
        ans += yolo(y);
        if (i < rem)
          ans += yolo(z);
      } else {
        ans += yolo(z);
      }
    }
    return ans;
  }
  return "";
}

int main() {

  ios_base::sync_with_stdio(0);
  cin.tie(0);

  freopen("B-small-attempt2.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t, x = 1;
  cin >> t;
  // t=1;
  while (t--) {

    cin >> n >> red >> orange >> yellow >> green >> blue >> violet;

    orange = green = violet = 0;

    if (orange > 0 && blue < orange + 1) {
      cout << "Case #" << x++ << ": IMPOSSIBLE" << endl;
      continue;
    }

    if (green > 0 && red < green + 1) {
      cout << "Case #" << x++ << ": IMPOSSIBLE" << endl;
      continue;
    }

    if (violet > 0 && yellow < violet + 1) {
      cout << "Case #" << x++ << ": IMPOSSIBLE" << endl;
      continue;
    }

    arr[1].clear();
    arr[2].clear();
    arr[3].clear();

    if (orange > 0) {
      blue -= orange + 1;
      string str = "B";
      while (orange--)
        str += "OB";
      arr[1].push_back(str);
    }

    if (green > 0) {
      red -= green + 1;
      string str = "R";
      while (green--)
        str += "GR";
      arr[2].push_back(str);
    }

    if (violet > 0) {
      yellow -= violet + 1;
      string str = "Y";
      while (violet--)
        str += "VY";
      arr[3].push_back(str);
    }

    while (blue--)
      arr[1].push_back("B");
    while (red--)
      arr[2].push_back("R");
    while (yellow--)
      arr[3].push_back("Y");

    string ans = "";
    ans = check(1);
    // cout<<ans<<endl;
    if ((int)ans.length() == n) {
      cout << "Case #" << x++ << ": " << ans << endl;
      continue;
    }

    ans = check(2);
    if ((int)ans.length() == n) {
      cout << "Case #" << x++ << ": " << ans << endl;
      continue;
    }

    ans = check(3);
    if ((int)ans.length() == n) {
      cout << "Case #" << x++ << ": " << ans << endl;
      continue;
    }

    ans = "";
    if ((int)ans.length() != n) {
      cout << "Case #" << x++ << ": IMPOSSIBLE" << endl;
      continue;
    }
  }

  return 0;
}
