#include <bits/stdc++.h>

using namespace std;

const int N = 1111;

struct State {
    int a[3];

    State(int first) {
        a[0] = a[1] = a[2] = 0;
        a[first] = 1;
    }

    bool operator < (const State &o) const {
        for (int i = 0; i < 3; ++i) if (a[i] != o.a[i]) {
            return a[i] < o.a[i];
        }
        return false;
    }
};

set<State> was[3][3];
vector<int> save;
int has[9];
int n;
bool success;

clock_t start;

char to_char(int x) {
    if (x == 0) return 'R';
    if (x == 1) return 'Y';
    assert(x == 2);
    return 'B';
}

void go(int first, int last, State cur) {
    //if ((double)(clock() - start) / CLOCKS_PER_SEC > 15) return;
    if (success) return;
    if (was[first][last].count(cur)) return;

    was[first][last].insert(cur);
    if (cur.a[0] + cur.a[1] + cur.a[2] == n) {
        if (first != last) {
            assert(save[0] != save.back());
            assert(save.size() == n);
            success = true;
            int cnt[3] = {0, 0, 0};
            for (int i = 0; i < n; ++i) {
                cout << to_char(save[i]);
                cnt[save[i]] += 1;
                if (i + 1 < n) assert(save[i] != save[i + 1]);
            }
            assert(save[n - 1] != save[0]);
            for (int i = 0; i < 3; ++i) {
                if (cnt[i] != has[i]) {
                    cerr << i << ' ' << cnt[i] << ' ' << has[i] << endl;
                    assert(0);
                }
            }
            cout << endl;
        }
        return;
    }
    int cand[2] = {-1, -1};
    for (int nxt = 0; nxt < 3; ++nxt) if (nxt != last && cur.a[nxt] < has[nxt]) {
        if (cand[0] == -1) cand[0] = nxt; else cand[1] = nxt;
    }
    if (cand[1] != -1 && has[cand[0]] - cur.a[cand[0]] < has[cand[1]] - cur.a[cand[1]]) {
        swap(cand[0], cand[1]);
    }
    for (int i = 0; i < 2; ++i) if (cand[i] != -1) {
        int nxt = cand[i];
        cur.a[nxt] += 1;
        save.push_back(nxt);
        go(first, nxt, cur);
        save.pop_back();
        cur.a[nxt] -= 1;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int T; cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        start = clock();
        cin >> n;
        vector<int> a(6);
        for (int i = 0; i < 6; ++i) {
            cin >> a[i];
        }
        has[0] = a[0];
        has[1] = a[2];
        has[2] = a[4];
        sort(a.begin(), a.end());
        cout << "Case #" << tc << ": ";
        if (a[3] + a[4] < a[5]) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        success = false;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                was[i][j].clear();
            }
        }
        for (int i = 0; i < 3; ++i) if (has[i]) {
            save.clear();
            save.push_back(i);
            go(i, i, State(i));
        }
        if (!success) {
            assert(0);
            cout << "IMPOSSIBLE\n";
        }
    }
    return 0;
}
