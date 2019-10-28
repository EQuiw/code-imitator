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

int doit(string s, int len) {
    int howmany = 0;
    while(true) {
        if(s.size() == len) {
            int f1 = 0;
            int f2 = 0;
            rep(i,0,len) {
                if(s[i] == '+') f1++;
                else f2++;
            } 
            if(f1 == len) {
            
            } else if(f2 == len) {
                howmany++;
            } else {
                howmany += 1000000;
            }
        
            break;
        } else { 
            if(s[0] == '+') {
                s.erase(s.begin());
            } else {
                rep(i,0,len) {
                    if(s[i] == '+') s[i] = '-';
                    else s[i] = '+';
                }
                howmany++;
            }
        }
    }
    return howmany;
}

int main() {
	cin.sync_with_stdio(false);
    ofstream fout("ans.txt");
    int n;
    cin >> n;
    rep(i,0,n) {
        string s;
        cin >> s;
        int m;
        cin >> m;
        int bst = INF;
        bst = min(doit(s,m), bst);
        reverse(s.begin(), s.end());
        bst = min(doit(s,m), bst);
        fout << "Case #" << i+1 << ": ";
        if(bst > 10000) fout << "IMPOSSIBLE" << endl;
        else fout << bst << endl;
    }
	return 0;
}

