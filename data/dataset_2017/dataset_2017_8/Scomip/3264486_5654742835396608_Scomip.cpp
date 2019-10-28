#include <bits/stdc++.h>

using namespace std;

pair<long long,long long> solve()
{
    long long n, k, l = 1, r = 0;
    cin >> n >> k;
    while (k > (l + r))
    {
        k -= (l + r);
        if (n % 2)
            l = l * 2 + r;
        else
            r = r * 2 + l;
        n = (n - 1) / 2;
    }
    if (k <= r) n++;
    return {n / 2, n / 2 - !(n % 2)};
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
        auto p = solve();
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}
