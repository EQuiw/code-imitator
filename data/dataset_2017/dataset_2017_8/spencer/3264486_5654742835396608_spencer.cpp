#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll solve_case()
{
    ll N, K; cin >> N >> K;

    auto seen = 0LL;
    auto counts = map<ll, ll, greater<ll>>{{N, 1}};
    while (true)
    {
        const auto previous = counts;

        counts.clear();
        for (const auto kv : previous)
        {
            const auto gap = kv.first, count = kv.second;
            if (seen + count >= K) return gap;
            else
            {
                seen += count;

                const auto smaller = (gap-1)/2;
                const auto larger = gap-1 - smaller;
                counts[smaller] += count;
                counts[larger] += count;
            }
        }
    }
}

int main()
{
    int T; cin >> T;
    for (auto t = 1; t <= T; t++)
    {
        cout << "Case #" << t << ": ";
        const auto gap = solve_case();
        const auto smaller = (gap-1)/2;
        const auto larger = gap-1 - smaller;
        cout << larger << " " << smaller << endl;
    }
}
