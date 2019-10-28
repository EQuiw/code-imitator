#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;


typedef long long ll;


void printcase(int k, ll ans) {
    cout << "Case #" << k << ": ";
    cout << ans << endl;
}

int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t;
    cin >> t;
    for (int tt = 0; tt < t; ++tt) {
        ll x;
        cin >> x;
        vector<int> dt;
        while (x)
            dt.push_back(x % 10), x /= 10;
        reverse(dt.begin(), dt.end());
        set<ll> ans;
        ll nowx = 0;
        for (int i = 0; i < dt.size(); ++i) {
            if (!i || dt[i - 1] < dt[i]) {
                ll nowy = nowx * 10ll;
                nowy += dt[i] - 1;
                for (int j = i + 1; j < dt.size(); ++j)
                    nowy *= 10ll, nowy += 9;
                ans.insert(nowy);
            } 
            if (!i || dt[i - 1] <= dt[i])
                nowx *= 10, nowx += dt[i];
            else
                break;
        }
        ans.insert(nowx);
        printcase(tt + 1, *ans.rbegin());
    }
    return 0;
}
