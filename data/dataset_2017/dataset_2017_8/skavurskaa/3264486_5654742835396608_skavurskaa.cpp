#include <bits/stdc++.h>
using namespace std;

class Interval
{
    public:
    int x, y, size, midpoint;
    Interval(){}
    Interval(int xx, int yy)
    {
        x = xx;
        y = yy;
        size = (y-x+1);
        midpoint = (y+x)/2;
    }
    bool operator<(const Interval &i) const
    {
        if (size != i.size) return size > i.size;
        else return x < i.x;
    }
};

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cout << "Case #" << t << ": ";
        long long N, K; cin >> N >> K;

        set<Interval> s;
        Interval cur;
        s.insert(Interval(1,N));
        for (int i = 1; i <= K; i++)
        {
            cur = *s.begin();
            s.erase(s.begin());
            if (cur.x != cur.midpoint)
                s.insert(Interval(cur.x,cur.midpoint-1));
            if (cur.y != cur.midpoint)
                s.insert(Interval(cur.midpoint+1,cur.y));
        }
        cout << cur.size/2 << " " << (cur.size-1)/2 << endl;
    }
}
