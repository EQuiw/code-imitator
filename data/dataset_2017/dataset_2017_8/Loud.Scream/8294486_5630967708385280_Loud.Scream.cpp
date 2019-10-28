#include <bits/stdc++.h>

using namespace std;

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define ld long double
#define ll long long
#define uint unsigned int
#define all(a) a.begin(), a.end()
#ifdef DEBUG
    #define NAME "1"
#else
    #define NAME "fox-blocks"
#endif
#define FREOPEN freopen(NAME".in", "r", stdin); freopen(NAME".out", "w", stdout)
#define PI 3.1415926535897932384626433832795

const double EPS = 1e-9;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	cout << fixed << setprecision(7);
	for (int qq = 1; qq <= t; ++qq) {
		cout << "Case #" << qq << ": ";
		int n;
		ld d;
		cin >> d >> n;
		ld st[n], v[n];
		for (int i = 0; i < n; ++i)
			cin >> st[i] >> v[i];
		ld mx = -1.0;
		for (int i = 0; i < n; ++i)
			mx = max(mx, (d - st[i]) / v[i]);
		ld l = d / mx;
		cout << l << "\n";
	}
	return 0;
}