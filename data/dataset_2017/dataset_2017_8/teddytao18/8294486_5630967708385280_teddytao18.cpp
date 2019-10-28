#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;
#define ll long long

int main()
{
    int T;
    scanf("%d",&T);
    for (int t=1;t<=T;t++)
    {
        double d,k,s,time;
        int i,j,n;
        scanf("%lf %d",&d,&n);
        time=0;
        for (i=0;i<n;i++)
        {
            scanf("%lf %lf",&k,&s);
            time=max(time,(d-k)/s);
        }
        printf("Case #%d: %f\n",t,d/time);
    }
}
