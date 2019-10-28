#include <bits/stdc++.h>

using namespace std;

string solve()
{
    string s;
    cin >> s;
    int n = s.length();
    int i;
    for (i = 1; i < n; i++)
        if (s[i] < s[i - 1])
            break;
    if (i == n)
        return s;
    i--;
    while (i && s[i] == s[i - 1])
        i--;
    for (int j = i + 1; j < n; j++)
        s[j] = '9';
    if (i == 0 && s[i] == '1')
        s.erase(0, 1);
    else
        s[i]--;
    return s;
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
        cout << solve() << endl;
    }

    return 0;
}
