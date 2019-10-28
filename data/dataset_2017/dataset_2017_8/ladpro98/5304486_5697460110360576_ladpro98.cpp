#include <bits/stdc++.h>

using namespace std;

const int N = 55;
const int P = 55;

struct Package {
    int id;
    int L, R;

    Package() {}

    Package(int id, int has, int each) {
        this->id = id;
        L = ceil(has * 10.0 / 11 / each);
        R = floor(has * 10.0 / 9 / each);
    }

    bool operator < (const Package &o) const {
        if (R != o.R) return R < o.R;
        return L < o.L;
    }
};

bool incL(const Package &a, const Package &b) {
    if (a.L != b.L) return a.L < b.L;
    return a.R < b.R;
}

struct Bucket {
    multiset<Package> a[N];
    int ingredient_count;

    Bucket() {
        ingredient_count = 0;
    }

    void reset() {
        ingredient_count = 0;
        for (int i = 0; i < N; ++i) a[i].clear();
    }

    void insert(Package p) {
        a[p.id].insert(p);
        if (a[p.id].size() == 1) {
            ingredient_count += 1;
        }
    }

    void erase(Package p) {
        auto it = a[p.id].find(p);
        if (it == a[p.id].end()) return;
        a[p.id].erase(it);
        if (a[p.id].size() == 0) {
            ingredient_count -= 1;
        }
    }

    vector<Package> grab_kit() {
        vector<Package> res;
        for (int i = 1; i <= ingredient_count; ++i) {
            res.push_back(*a[i].begin());
        }
        return res;
    }
} bucket[N * P];

Package a[N][P];
vector<pair<Package, int> > events[N * P];

void erase_all(Package p) {
    for (int i = p.L; i <= p.R; ++i) {
        bucket[i].erase(p);
    }
}

int n, p;
int r[N];

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int T; cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        vector<int> values;

        cin >> n >> p;
        for (int i = 1; i <= n; ++i) cin >> r[i];
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= p; ++j) {
                int q; cin >> q;
                a[i][j] = Package(i, q, r[i]);
                values.push_back(a[i][j].L);
                values.push_back(a[i][j].R);
            }
        }

        sort(values.begin(), values.end());
        values.resize(unique(values.begin(), values.end()) - values.begin());
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= p; ++j) {
                a[i][j].L = lower_bound(values.begin(), values.end(), a[i][j].L) - values.begin() + 1;
                a[i][j].R = lower_bound(values.begin(), values.end(), a[i][j].R) - values.begin() + 1;
            }
        }

        int max_r = 0;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= p; ++j) {
                if (a[i][j].L <= a[i][j].R) {
                    events[a[i][j].L].push_back(make_pair(a[i][j], +1));
                    events[a[i][j].R].push_back(make_pair(a[i][j], -1));
                    max_r = max(max_r, a[i][j].R);
                }
            }
        }
        int ans = 0;
        for (int pos = 0; pos <= max_r; ++pos) {
            for (auto e : events[pos]) if (e.second == +1) {
                auto it = e.first;
                for (int i = it.L; i <= it.R; ++i) {
                    bucket[i].insert(it);
                }
                for (int i = it.L; i <= it.R; ++i) {
                    if (bucket[i].ingredient_count == n) {
                        vector<Package> kit = bucket[i].grab_kit();
                        for (auto each : kit) {
                            erase_all(each);
                        }
                        ans += 1;
                        break;
                    }
                }
            }

            for (auto e : events[pos]) if (e.second == -1) {
                auto it = e.first;
                for (int i = it.L; i <= it.R; ++i) {
                    bucket[i].erase(it);
                }
            }
            events[pos].clear();
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }
    return 0;
}
