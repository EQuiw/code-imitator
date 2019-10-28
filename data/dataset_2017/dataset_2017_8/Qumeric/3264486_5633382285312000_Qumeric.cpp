#include <bits/stdc++.h>

using namespace std;

int t;

string s;

void fix(int p) {
    for (int i = p; i > 0 && s[i] < '0'; i--) {
        s[i] = '9';
        s[i-1]--;
    }
}

void solve() {
    cin >> s;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] < s[i-1]) {
            for (int j = i; j < s.size(); j++)
                s[j] = '9';
            s[i-1]--;
            fix(i-1);
            i = 0;
        }
    }
    if (s[0] == '0') {
        for (int i = 1; i < s.size(); i++)
            cout << '9';
        cout << '\n';
        return;
    }
    cout << s << '\n';
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

}
