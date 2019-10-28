#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <cstdlib>
#include <queue>

using namespace std;
#define Fill(a, b) memset(a, b, sizeof(a))
#define Debug(x) cout << #x << "=" << (x) << endl;
#define fop(i, a, b) for (i = a; i < b; i++)
#define fope(i, a, b) for (i = a; i <= b; i++)
#define fom(i, a, b) for (i = a; i > b; i--)
#define fome(i, a, b) for (i = a; i >= b; i--)
typedef long long LL;
typedef pair<int, int> P;
const LL inf = 1LL << 61;
const LL mod = 1000000007;
#define DEBUG
#ifdef DEBUG
#endif
struct stu
{
    int num;
    char ch;
    bool operator < (const stu & b) const
    {
        return num > b.num;
    }
};

vector<stu> vec;
int main()
{

    //std::ios::sync_with_stdio(false);
    int i = 0, j = 0, k = 0, kase = 0;
    int t, n;
    int r,y,b,o,g,v;
    freopen("B-small-attempt1.in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d%d%d%d%d%d", &n, &r, &o, &y, &g, &b, &v);
        vec.clear();
    stu tmp;
    tmp.num = r;
    tmp.ch = 'R';
    vec.push_back(tmp);
    tmp.num = y;
    tmp.ch = 'Y';
    vec.push_back(tmp);
    tmp.num = b;
    tmp.ch = 'B';
    vec.push_back(tmp);
    sort(vec.begin(), vec.end());
    int cha_num = 0;
    cha_num = vec[2].num-(vec[0].num-vec[1].num);
    if(cha_num < 0)
    {
        printf("Case #%d: IMPOSSIBLE\n", ++kase);
        continue;
    }
    printf("Case #%d: ", ++kase);
    for(i = 0; i < cha_num; i++)
    {
        printf("%c%c%c", vec[2].ch, vec[1].ch, vec[0].ch);
    }
    for(i = 0; i < vec[1].num-cha_num; i++)
    {
        printf("%c%c", vec[1].ch, vec[0].ch);
    }
    for(i = 0; i < vec[0].num-vec[1].num; i++)
    {
        printf("%c%c", vec[2].ch, vec[0].ch);
    }
    puts("");

    }

    return 0;
}
