#include <iostream>
#include <string>

using namespace std;

string solve(long long N) {
    string s;
    s = to_string(N);
    int n = s.length(), i = 0;
    while ( i < n-1 && s[i] - '0' <= s[i+1] - '0') {
        i++;
    }
    if (i < n - 1) {
        while (i > 0 && s[i] == s[i-1]) {
            i--;
        }
        s[i] = '0' + ((s[i] - '0') - 1 );
        i++;
        while (i < n) {
            s[i] = '9';
            i++;
        }
    }
    s.erase(0, min(s.find_first_not_of('0'), s.size()-1));
    return s;
}

int main() {
    int T; cin >> T;
    for (int i = 0; i < T; i++) {
        long long N; cin >> N;
        cout << "Case #" << i+1 <<": "<< solve(N) <<endl;
    }
    return 0;
}
