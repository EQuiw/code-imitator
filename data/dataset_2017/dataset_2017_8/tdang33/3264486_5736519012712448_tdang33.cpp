#include <iostream>
#include <string>

using namespace std;

void swap(string & s, int k, int i) {
    for (int j = i; j < i + k; j++) {
        if (s[j] == '+') s[j] = '-';
        else s[j] = '+';
    }
}

string solve(string s, int k) {
    int count = 0;
    int i = s.find_first_not_of('+');
    while (i != string::npos && i <= s.length() - k) {
        count++;
        swap(s, k, i);
        i = s.find_first_not_of('+');
    }
    if (i == string::npos) {
        return to_string(count);
    } else {
        return "IMPOSSIBLE";
    }

}

int main() {
    int T; cin >> T;
    for (int i = 0; i < T; i++) {
        string s;
        int k;
        cin >> s; cin >> k;
        cout << "Case #" << i+1 <<": "<< solve(s, k) <<endl;
    }
    return 0;
}
