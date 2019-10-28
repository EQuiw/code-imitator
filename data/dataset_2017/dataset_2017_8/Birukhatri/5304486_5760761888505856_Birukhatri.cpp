/********************************************
*                                           *
*    Solved By : Bir Bahadur Khatri(B'ru)   *
*      Be Positive,be Happy.                *
*                                           *
*********************************************/

#define ff first
#define D double
#define sz size()
#define ss second
#define PB push_back
#define MP make_pair
#define SQR(n) (n*n)
#define CHR getchar()
#define NL printf("\n")
#include<bits/stdc++.h>
#define ULL unsigned LL
#define PI 2.0*acos(0.0)
#define LL long long int
#define S1(a) a=in<int>()
#define SL1(a) a=in<LL>()
#define Max(a,b) ((a>b)?a:b)
#define Min(a,b) ((a<b)?a:b)
#define all(a) a.begin(),a.end()
#define _Max(a,b,c) Max(a,Max(b,c))
#define _Min(a,b,c) Min(a,Min(b,c))
#define cp printf("are you okay??\n")
#define SL2(a,b) a=in<LL>(),b=in<LL>()
#define F(i,a,b) for(int i=a;i<b; i++)
#define S2(a,b) a=in<int>(),b=in<int>()
#define R(i,a,b) for(int i=a-1;i>=b; i--)
#define BitCnt(a) __builtin_popcountll(a)
#define MEM(a,val) memset(a,val,sizeof(a))
#define SL3(a,b,c) a=in<LL>(),b=in<LL>(),c=in<LL>()
#define S3(a,b,c) a=in<int>(),b=in<int>(),c=in<int>()
#define trace1(x)                cerr << #x << ": " << x << endl;
#define InpOut freopen("A.in","r",stdin),freopen("A1.out","w",stdout)
#define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;
#define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl;
using namespace std;
template <typename T> T in(){char ch;T n = 0;bool ng = false;while (1){ch = getchar();if (ch == '-'){ng = true;ch = getchar();break;}if (ch>='0' && ch<='9')     break;}while (1){n = n*10 + (ch - '0');ch = getchar();if (ch<'0' || ch>'9')   break;}return (ng?-n:n);}
template<typename T>inline T POW(T B,T P){ if(P==0) return 1; if(P&1) return B*POW(B,P-1);  else return SQR(POW(B,P/2));}
template<typename T>inline T Gcd(T a,T b){if(a<0)return Gcd(-a,b);if(b<0)return Gcd(a,-b);return (b==0)?a:Gcd(b,a%b);}
template<typename T>inline T Lcm(T a,T b) {if(a<0)return Lcm(-a,b);if(b<0)return Lcm(a,-b);return a*(b/Gcd(a,b));}
long long Bigmod(long long base, long long power, long long MOD){long long ret=1;while(power){if(power & 1)ret=(ret*base)%MOD;base=(base*base)%MOD;power>>=1;}return ret;}
bool isVowel(char ch){ ch=toupper(ch); if(ch=='A'||ch=='U'||ch=='I'||ch=='O'||ch=='E') return true; return false;}
long long ModInverse(long long number, long long MOD){return Bigmod(number, MOD-2, MOD);}
bool isConst(char ch){if (isalpha(ch) && !isVowel(ch)) return true; return false;}
///**********************************************************//

#define MD1 1000000007ULL
#define MD2 1000000009ULL
#define MD3 1000000021ULL
#define BS1 10000019ULL
#define BS2 10000079ULL
#define BS3 10000103ULL
#define PUL pair<ULL,ULL>
#define PII pair<int,int>

#define lchild lft,l,mid
#define rchild rgt,mid+1,r
#define ngood  r<st||l>ed
#define good   st<=l&&ed>=r
#define seg    int mid=(l+r)/2,lft=2*id,rgt=lft+1

///         0123456789
#define MX  1007
#define MOD 1000000007
#define INF 2000000000000000LL
#define EPS 1e-9
/// ==========================================////

char ss[55][55];
int n,m;

void lol(int x,int y,char ch)
{
    if(y<1) return;
    if(ss[x][y]!='?') return ;
    ss[x][y]=ch;
    lol(x,y-1,ch);
}

void lol1(int x,int y,char ch)
{
    if(x>n) return;
    if(ss[x][y]!='?') return;
    ss[x][y]=ch;
    lol(x,y-1,ch);
    lol1(x+1,y,ch);
}

void lol2(int x,int y,int ch)
{
    if(x<1) return;
    if(ss[x][y]!='?') return;
    ss[x][y]=ch;
    lol(x,y-1,ch);
    lol2(x-1,y,ch);
}


int main()
{
    freopen("A.in","r",stdin);
    freopen("A1.out","w",stdout);

    int tc; scanf("%d",&tc);

    for(int cas=1;cas<=tc;cas++)
    {

        cin>>n>>m;

        for(int i=1;i<=n;i++)
        {
            scanf("%s",&ss[i][1]);
        }

        for(int j=1;j<=m;j++)
        {
            for(int i=1;i<=n;i++)
            {
                if( (ss[i][j]!='?') )
                {
                    lol1(i+1,j,ss[i][j]);
                    lol2(i-1,j,ss[i][j]);
                    lol(i,j-1,ss[i][j]);
                }
            }
        }

        for(int j=1;j<=m;j++)
        {
            for(int i=1;i<=n;i++)
            {
                if(ss[i][j]=='?') ss[i][j]=ss[i][j-1];
            }
        }

        printf("Case #%d:\n",cas);

        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                printf("%c",ss[i][j]);
            }
            puts("");
        }
        trace1(cas)

    }

}
