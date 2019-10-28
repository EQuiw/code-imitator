#include <bits/stdc++.h>
using namespace std;

char inv(char c)
{
    if (c == '-') return '+';
    else return '-';
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cout << "Case #" << t << ": ";
        string s; int k;
        cin >> s >> k;
        int cnt = 0;
        for (int i = 0; i <= s.size()-k; i++)
        {
            if (s[i] == '-')
            {
                cnt++;
                for (int j = i; j < i+k; j++)
                    s[j] = inv(s[j]);
            }
        }
        if (s.find('-') != -1) cout << "IMPOSSIBLE" << endl;
        else cout << cnt << endl;
    }
}
