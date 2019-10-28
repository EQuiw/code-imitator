#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
int T_T;
int n,k;
struct node
{
    int l,r;
    node(int _l=0,int _r=0):l(_l),r(_r){}
    bool operator < (const node & a) const {
        return (r-l == a.r-a.l)?a.l<l:(r-l < a.r-a.l);
    }
};
int main(void)
{
    freopen("C-small-1-attempt1.in","r",stdin);
    freopen("out-small1.txt","w",stdout);
    scanf("%d",&T_T);
    for (int cas=1;cas<=T_T;cas++)
    {
        scanf("%d%d",&n,&k);
        priority_queue <node> q;
        q.push(node(1,n));
        for (int i=0;i<k-1;i++)
        {
            node a = q.top();
//            printf("[%d, %d]\n",a.l,a.r);
            q.pop();
            int m = (a.l+a.r)>>1;
            if (a.l < m) {
                q.push(node(a.l,m-1));
//                printf("push [%d, %d]\n",a.l,m-1);
            }
            if (m < a.r) {
                q.push(node(m+1,a.r));
//                printf("push [%d, %d]\n",m+1,a.r);
            }
        }
        int mx,mn;
        node a = q.top();
//        printf("[%d, %d]\n",a.l,a.r);
        int m = (a.l+a.r)>>1;
        mx = max(a.r-m,m-a.l);
        mn = min(a.r-m,m-a.l);
        printf("Case #%d: %d %d\n",cas,mx,mn);
    }
    return 0;
}
