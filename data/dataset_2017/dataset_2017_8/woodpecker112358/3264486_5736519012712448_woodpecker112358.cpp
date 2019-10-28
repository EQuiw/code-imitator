#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <string>
#include <cctype>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#include <ctime>
#include <list>
#include <map>
#include <set>
#define PI (acos(-1.0))
#define Abs(a) (((a)<0) ? (-(a)) :(a) )
#define rep(i,n) for((i)=0;(i)<(n);(i)++)
#define Rep(i,n) for(int i=0;i<(n);i++)
#define Rrep(i,n) for(int i=((n)-1);i>=0;i--)
#define rrep(i,n) for((i)=(n)-1;(i)>=0;(i)--)
#define Pii pair<int,int>
#define PB push_back
#define Size(x) ((int)(x.size()))
using namespace std;
typedef long long mint;
typedef unsigned long long umint;
int main()
{
    freopen("A-small-attempt0.in","r",stdin);
    freopen("Aout.txt", "w", stdout);
    int T;
    cin >> T;
    char s[1005];
    for(int t = 1; t <= T; t++)
    {
        cin >> s;
        int k;
        int len = strlen(s);
        vector<int> flips(len, 0);
        cin >> k;
        int flipss = 0;
        int tflips = 0;
        Rep(i, len - k + 1)
        {
            if(i >= k)
            {
                tflips -= flips[i - k];
            }
            int fp = (tflips & 1);
            int fpped = (s[i] != '+');
            if(fp ^ fpped)
            {
                flips[i] = 1;
                flipss++;
                tflips++;
            }
        }
        //cout << flipss << endl;
        printf("Case #%d: ", t);
        int i;
        for(i = len - k + 1; i < len; i++)
        {
            if(i >= k)
            {
                tflips -= flips[i - k];
            }
            int fp = (tflips & 1);
            int fpped = (s[i] != '+');
            if(fp ^ fpped)
            {
                cout << "IMPOSSIBLE" << endl;
                break;
            }
        }
        if(i == len)
        {
            cout << flipss << endl;
        }
        
    }
    return 0;
}


