#include <iostream>
#include <cstdio>
#include <iomanip>

using namespace std;

int t, n;
double d, k, s, ans;

int main()
{
    ios_base::sync_with_stdio(false);
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    cin >> t;

    for (int i = 1; i <= t; ++i)
    {
        ans = 0;
        cin >> d >> n;
        for (int j = 0; j < n; ++j)
        {
            cin >> k >> s;
            if ((d - k) / s > ans) {ans = (d - k) / s;}
        }
        ans = d / ans;
        cout.precision(6);
        cout << fixed;
        cout << "Case #" << i << ": " << ans << "\n";
    }

    return 0;
}
