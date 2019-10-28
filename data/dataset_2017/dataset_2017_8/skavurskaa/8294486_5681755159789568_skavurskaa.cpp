#include <bits/stdc++.h>
using namespace std;
typedef tuple<int,int,int> T;

int N, Q, adj[101][101];
int E[101], S[101], U, V;
map<T, double> dp;
double solve(int v, int c, int h)
{
    if (v == V) return 0;
    if (dp.find(T(v,c,h)) == dp.end())
    {
        dp[T(v,c,h)] = 1e20;
        for (int i = 1; i <= N; i++)
            if (adj[v][i] != -1)
            {
                if (h >= adj[v][i])
                    dp[T(v,c,h)] = min(dp[T(v,c,h)], solve(i,c,h-adj[v][i])+adj[v][i]/(double)S[c]);
                if (E[v] >= adj[v][i])
                    dp[T(v,c,h)] = min(dp[T(v,c,h)], solve(i,v,E[v]-adj[v][i])+adj[v][i]/(double)S[v]);
            }
    }
    return dp[T(v,c,h)];
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N >> Q;
        for (int i = 1; i <= N; i++) cin >> E[i] >> S[i];
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                cin >> adj[i][j];
        cout << "Case #" << t << ":";
        for (int i = 0; i < Q; i++)
        {
            cin >> U >> V;
            dp.clear();
            cout << " " << fixed << setprecision(10) << solve(U,U,E[U]);
        }
        cout << endl;
    }
}
