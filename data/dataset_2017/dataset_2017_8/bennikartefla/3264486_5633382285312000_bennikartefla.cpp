#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = (a); i < (b); i++)
#define iter(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end();++it)
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = ~(1<<31);
const double pi = acos(-1);

bool check(int a) {
    string s = to_string(a);
    vi k;
    rep(i,0,s.size()) {
        char m = s[i];
        k.push_back(m-'0');
    }
    vi ne = k;
    sort(ne.begin(), ne.end());
    rep(i,0,k.size()) if(k[i] != ne[i]) return false;
    return true;
}

int main() {
	cin.sync_with_stdio(false);
    ofstream fout("ans.txt");
    int n;
    cin >> n;
    rep(i,0,n) {
        int m;
        cin >> m;
        for(int a = m; a >= 0; a--) {
            if(check(a)) {
                fout << "Case #" << i+1 << ": " <<  a << endl;
                break;
            }
        }
    }
	return 0;
}

