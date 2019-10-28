#include <bits/stdc++.h>
using namespace std;

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; t++)
    {
        long long int D, N; double K[1111], S[1111]; cin >> D >> N;
        long double time_fin, spd=1e15;
        for (int i = 0; i < N; i++)
        {
            cin >> K[i] >> S[i];
            time_fin = (D-K[i])/S[i];
            spd = min(spd,D/time_fin);
        }

        /* to viajando
        set<tuple<double,int,int>> s;
        for (int i = 0; i < N; i++)
            for (int j = i+1; j < N; j++)
            {
                int time_intersect, pos_intersect;
                if (K[i] < K[j] && S[i] > S[j])
                {
                    time_intersect = (K[j]-K[i])/(S[i]-S[j]);
                    pos_intersect = K[i] + time_intersect*S[i];
                    if (pos_intersect > D) break;
                    s.insert(make_tuple(pos_intersect,i,j))
                }
                else if (K[i] > K[j] && S[i] < S[j])
                {
                    time_intersect = (K[i]-K[j])/(S[j]-S[i]);
                    pos_intersect = K[i] + time_intersect*S[i];
                    if (pos_intersect > D) break;
                    s.insert(make_tuple(pos_intersect,j,i))
                }
            }
        */
        cout << "Case #" << t << ": " << fixed << setprecision(10) << spd << endl;
    }
}
