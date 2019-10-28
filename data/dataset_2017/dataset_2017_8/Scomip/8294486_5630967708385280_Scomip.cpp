#include <bits/stdc++.h>

using namespace std;

struct horse
{
    int k, s;
    bool operator<(const horse& h) const {return k < h.k;}
} a[1100];

void solve()
{
    int n, d;
    cin >> d >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i].k >> a[i].s;
    sort(a, a + n);
    double ans = 1e18;
    for (int i = 0; i < n; i++)
        ans = min(ans, ((double)a[i].s * d) / ((double)d - a[i].k));
    cout << setprecision(20) << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int i = 1; i <= T; i++)
    {
        cout << "Case #" << i << ": ";
        solve();
        cout << endl;
    }

    return 0;
}
