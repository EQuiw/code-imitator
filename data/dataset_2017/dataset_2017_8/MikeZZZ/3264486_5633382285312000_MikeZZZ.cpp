#include <bits/stdc++.h>
using namespace std;
const int N = 20 + 5;
int T, Case;
long long n;

string f(long long n) {
    string ret = "";
    while(n/10) {
        int a = n/10%10, b = n%10;
        if(a > b) {
            ret = string(ret.size()+1, '9');
            n = n/10 - 1;
        }else {
            ret = char(b+'0') + ret;
            n = n/10;
        }
    }
    if(n > 0) ret = char(n+'0') + ret;
    while(ret.size() && ret[0] == '0') ret = ret.substr(1);
    if(ret.size() == 0) ret = "0";
    return ret;
}

int main() {
    freopen("B-small-attempt0.in","r",stdin);
    freopen("out.out","w",stdout);
    scanf("%d", &T);
    while(T--) {
        scanf("%lld", &n);
        printf("Case #%d: %s\n", ++Case, f(n).c_str());
    }
    return 0;
}
