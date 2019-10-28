#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;


const double eps = 1e-8;
const double pi = acos(-1.0);

const int N = 1005;

vector<pair<int, string>> vec;

int main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    int T;
    cin >> T;

    for (int cas = 1; cas <= T; cas++) {
        int n;
        int r, o, y, g, b, v;
        vec.clear();
        cin >> n >> r >> o >> y >> g >> b >> v;

        vec.push_back(make_pair(r, "R"));
        vec.push_back(make_pair(y, "Y"));
        vec.push_back(make_pair(b, "B"));

        sort(vec.begin(), vec.end());


        vector<string> result;

        if (vec[0].first + vec[1].first < vec[2].first) {
            printf("Case #%d: IMPOSSIBLE\n", cas);
            continue;
        }

        while (vec[2].first > 0 && vec[1].first > 0) {
            result.push_back(vec[2].second);
            vec[2].first--;
            result.push_back(vec[1].second);
            vec[1].first--;
        }
        if (vec[2].first > 0) {
            while (vec[2].first > 0 && vec[0].first > 0) {
                result.push_back(vec[2].second);
                vec[2].first--;
                result.push_back(vec[0].second);
                vec[0].first--;
            }
        }

        for (int i = 0; i < result.size(); i++) {
            if (result[i] == vec[1].second) {
                if (vec[0].first > 0) {
                    result[i] = vec[0].second + result[i];
                    vec[0].first--;
                }
                if (vec[0].first > 0) {
                    result[i] = result[i] + vec[0].second;
                    vec[0].first--;
                }
            }
        }

        bool ok = vec[0].first == 0;
        string ans = "";
        for (int i = 0; i < result.size(); i++) {
            ans += result[i];
        }

        if (ans.length() != r + b + y) {
            ok = false;
        }

        for (int i = 1; i < ans.length(); i++) {
            if (ans[i] == ans[i - 1]) {
                ok = false;
            }
        }

        if (ans[ans.length() - 1] == ans[0]) {
            ok = false;
        }


        if (!ok) {
            printf("Case #%d: IMPOSSIBLE\n", cas);
        } else {
            printf("Case #%d: %s\n", cas, ans.c_str());
        }
    }
    return 0;
}

