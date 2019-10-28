#include<bits/stdc++.h>
#include<stdio.h>
#include<string.h>

using namespace std;
typedef long long ll;
typedef double db;
const int N = 100005;

int a[10];

vector<int> construct(vector<int> b) {
    vector<int> res;
    int s = b[0] + b[1] + b[2];
    for(int i=0; i<s; i++) {
        if(i==0||b[0]>0&&res.back()!=0) {
            res.push_back(0),--b[0];
        } else {
            int c = b[1]>b[2]?1:2;
            if(res.back()==c) c = 3-c;
            res.push_back(c),--b[c];
        }
    }
    return res;
}

bool check(int r,int y,int b) {
    if(r<0||y<0||b<0) return false;
    int s = r + y + b;
    int mx = max(r, max(y,b));
    if(mx > s - mx) return false;
    return true;
}

vector<char> to_char(int r,int y,int b) {
    vector<char> res;
    if(r>=y&&r>=b) {
        res.push_back('r');
        if(y>b) res.push_back('y'),res.push_back('b');
        else res.push_back('b'),res.push_back('y');
        return res;
    }
    if(y>=r&&y>=b) {
        res.push_back('y');
        if(r>b) res.push_back('r'), res.push_back('b');
        else res.push_back('b'),res.push_back('r');
        return res;
    }
    if(b>=y&&b>=r) {
        res.push_back('b');
        if(y>r) res.push_back('y'),res.push_back('r');
        else res.push_back('r'),res.push_back('y');
        return res;
    }
    return res;
}

vector<int> to_v(int r,int y,int b) {
    if(r<y) swap(r,y);
    if(r<b) swap(r, b);
    if(y<b) swap(y,b);
    vector<int> res;
    res.push_back(r),res.push_back(y),res.push_back(b);
    return res;
}

char p[]="ROYGBV";

int main() {
#ifdef PKWV
    freopen("B-small-attempt0.in","r",stdin);
    freopen("B-small-attempt0.out","w",stdout);
#endif // PKWV
    int T;
    scanf("%d",&T);
    for(int ca=1; ca<=T; ca++) {
        int n;
        scanf("%d",&n);
        for(int i=0; i<6; i++) scanf("%d",&a[i]);
        int r=a[0] - a[3]; // red - green
        int y = a[2] - a[5]; // yellow - v
        int b = a[4] - a[1]; // blue - orange
        bool ok=check(r, y,b);
        printf("Case #%d: ", ca);
        if(!ok) {
            printf("IMPOSSIBLE\n");
            continue;
        }
        vector<int> v=to_v(r,y,b);
        vector<char> c=to_char(r,y,b);
        for(int i=0; i<c.size(); i++) c[i] = toupper(c[i]);
//        for(int i=0;i<c.size();i++) printf("%c  \n",c[i]);
        vector<int> res = construct(v);
        string str;
        for(int i=0; i<res.size(); i++) {
//            printf("res i : %d\n",res[i]);
            char t = c[res[i]];
            str += t;
            int j(-1);
            if(t=='R') {
                j = 3;
            } else if(t=='Y') j=5;
            else if(t=='B') j = 1;
//            printf("j:  %d\n",j);
            if(a[j]>0) {
                while(a[j]) {
                    str += p[j];
                    str += t;
                    --a[j];
                }
            }
        }
//        printf("size:  %d\n",res.size());
        for(int i=1; i<6; i+=2) {
            if(a[i]>0) {
                while(a[i]) {
                    str+= p[(i+3)%6];
                    str+=p[i];
                    --a[i];
                }
            }
        }
        cout<<str<<endl;
    }
    return 0;
}
