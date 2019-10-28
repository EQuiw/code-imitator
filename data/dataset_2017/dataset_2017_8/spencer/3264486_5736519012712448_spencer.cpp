#include <bits/stdc++.h>
using namespace std;

void solve_case()
{
    string S; int K; cin >> S >> K;
    const auto N = int(S.size());

    auto result = 0;
    for (auto i = 0; i+K-1 < N; i++)
    {
        if (S[i] == '-')
        {
            for (auto j = 0; j < K; j++)
                S[i+j] = S[i+j] == '-' ? '+' : '-';
            result++;
        }
    }

    auto ok = true;
    for (const auto c : S)
        ok &= c == '+';
    if (ok) cout << result << endl;
    else cout << "IMPOSSIBLE" << endl;
}

int main()
{
    int T; cin >> T;

    for (auto t = 1; t <= T; t++)
    {
        cout << "Case #" << t << ": ";
        solve_case();
    }
}
