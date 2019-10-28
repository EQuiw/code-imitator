#include <bits/stdc++.h>
using namespace std;

int t, tc, n, d;

int main() {
    cout.precision(10);
    cout << fixed;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while (t--) {
        cin >> d >> n;
        cout << "Case #" << ++tc << ": ";
        double mx = 0;
        for (int i = 0; i < n; ++i) {
            int k, s;
            cin >> k >> s;
            double t = 1.0 * (d - k) / s;
            mx = max(mx, t);
        }
        cout << d/mx << '\n';
    }
}
