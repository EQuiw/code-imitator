#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
typedef long long ll;
typedef pair<int,int> pt;
const int base = 1000000007;
const int maxn = 100002;

ll n;
int a[maxn], c[maxn];

bool tidy(int n) {
    int b[20], dem, i,j;
    dem = 0;
    while (n>0) {
        dem++;
        b[dem] = n%10;
        n /= 10;
    }
    for (i=1;i<dem;i++) if (b[i] < b[i+1]) return false;
    return true;
}

void solve1(int test) {
    int i,j,k;

    for (i=n;i>=1;i--) if (tidy(i)) {
        cout << i << "\n";
        break;
    }
}

void solve2(int test) {
    int i,j,k;
    int b[22];
    bool spec = false;

    int dem = 0;
    while (n > 0) {
        b[++dem] = n%10;
        n /= 10;
    }
    for (i=1;i<=dem;i++) {a[i] = b[dem-i+1]; c[i] = 0;}

    for (i=1;i<=dem;i++) {
        if (a[i] >= c[i-1]) c[i] = a[i];
        else {
            j = i-1;
            while (j>0 && c[j]==0) {
                c[j] = 9;
                j--;
            }
            c[j]--;
            if (c[1]==0) {spec = true; break;}

            while (j>0  && c[j] < c[j-1]) {
                c[j-1] = c[j];
                j--;
            }

            for (k=j+1;k<=dem;k++) c[k] = 9;
            break;
        }
    }

    if (spec) {for (i=1;i<dem;i++) cout << 9; cout << "\n";}
    else {for (i=1;i<=dem;i++) cout << c[i]; cout << "\n";}
}

void solve(int test) {
    int i,j,k,u,v;

    cout << "Case #" << test << ": ";
    cin >> n;
    if (n<=000) solve1(test);
    else solve2(test);
}

int main()
{
    int i,t;
    freopen("cjb.in","r",stdin);
    freopen("outputb.out","w",stdout);

    scanf("%d",&t);
    for (i=1;i<=t;i++) solve(i);

    return 0;
}
