#include <bits/stdc++.h>
using namespace std;

int fld(const int a, const int b) { return a / b; }
int cld(const int a, const int b) { return (a + b - 1) / b; }

void solve_case()
{
    int N, P; cin >> N >> P;

    auto ratatouille = vector<int>(N);
    for (auto& x : ratatouille) cin >> x;

    struct Event { int id, ingredient, time, time2; bool start; };
    auto events = vector<Event>();
    for (auto i = 0; i < N; i++)
    {
        const auto r = ratatouille[i];
        for (auto j = 0; j < P; j++)
        {
            int q; cin >> q;
            const auto start = cld(10*q, 11*r), finish = fld(10*q, 9*r);
            if (start <= finish)
            {
                events.push_back({i*P + j, i, start, finish+1, true});
                events.push_back({i*P + j, i, finish+1, 0, false});
            }
        }
    }

    const auto compare = [](const Event a, const Event b)
    {
        if (a.time != b.time) return a.time < b.time;
        else return a.start < b.start;
    };
    sort(begin(events), end(events), compare);

    auto result = 0;
    struct S { int id, time; };
    const auto compare2 = [](const S a, const S b) { return a.time < b.time; };
    auto active = vector<set<S, decltype(compare2)>>(N, set<S, decltype(compare2)>(compare2));
    for (const auto e : events)
    {
        if (e.start)
        {
            active[e.ingredient].insert({e.id, e.time2});

            auto non_empty = 0;
            for (const auto& s : active)
                non_empty += s.size() != 0;
            if (non_empty == N)
            {
                result++;
                for (auto& s : active) s.erase(begin(s));
            }
        }
        else active[e.ingredient].erase({e.id, e.time});
    }
    cout << result << endl;
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
