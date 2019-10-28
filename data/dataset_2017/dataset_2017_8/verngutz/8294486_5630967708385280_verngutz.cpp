#include <bits/stdc++.h>
#define EPS 1e-6
using namespace std;

int main() {
    int T;
    cin >> T;
    for(int t = 1; t <= T; t++) {
        double D;
        int N;
        cin >> D >> N;
        double K1, S1;
        cin >> K1 >> S1;
        double T1 = (D - K1) / S1;
        double minspeed = K1 / T1 + S1;
        for(int i = 2; i <= N; i++) {
            double k, s;
            cin >> k >> s;
            double t = (D - k) / s;
            minspeed = min(minspeed, k / t + s);
        }
        cout << "Case #" << t << ": " << fixed << setprecision(6) << minspeed << endl;
    }
    return 0;
}
