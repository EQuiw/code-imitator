#include <bits/stdc++.h>
using namespace std;

void solve_case()
{
    int D, N; cin >> D >> N;

    struct Horse { int start, speed; };
    auto horses = vector<Horse>(N);
    for (auto& h : horses) cin >> h.start >> h.speed;

    auto lower = 1.0, upper = 1e15;
    for (auto iterations = 0; iterations < 100; iterations++)
    {
        const auto speed = (lower + upper) / 2;

        auto first_collision = numeric_limits<double>::infinity();
        for (const auto h : horses) if (speed > h.speed)
        {
            const auto collision = h.start / (speed-h.speed);
            first_collision = min(first_collision, collision);
        }
        if (first_collision*speed >= D) lower = speed;
        else upper = speed;
    }
    cout << lower << endl;
}

int main()
{
    cout << fixed << setprecision(9);

    int T; cin >> T;
    for (auto t = 1; t <= T; t++)
    {
        cout << "Case #" << t << ": ";
        solve_case();
    }
}
