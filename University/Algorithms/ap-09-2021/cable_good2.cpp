/* To find the connectivity of a graph, use Menger ’s theorem, * the relationship between the vertex connectivity K (G) of the undirected graph G and the maximum number of independent orbits between the vertices * if G is a complete graph K {G} = | V (G) | -1 * else K (G) = min (P {A, B}) A, B are not adjacent * */

#include <cstdio>
#include <cstring>
#include <queue>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#define LL long long 

using namespace std;

const int Max = 110;

const int INF = 0x3f3f3f3f;

int Map[Max][Max];


int MaxFlow(int n,int s,int t)
{
    cerr << "MAXFlow called with ("<<s<<","<<t<<") size " << n << "\n";

    int Flow[Max][Max]; //Record the current network flow.

    int MinFlow[Max];//Record the minimum value on the path

    int pre[Max];//Record parent node

    queue<int>Q;

    int ans  = 0;

    memset(Flow,0,sizeof(Flow));

    while(1)
    {
        while(!Q.empty())
        {
            Q.pop();
        }

        Q.push(s);

        memset(pre,-1,sizeof(pre));

        pre[s] = -2;

        MinFlow[s]=INF;

        while(!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            for(int i=0;i<n;i++)
            {
                if(pre[i]==-1&&Flow[u][i]<Map[u][i])
                {
                    pre[i]=u;
                    Q.push(i);  
                    MinFlow [i] = min(MinFlow[u],(Map[u][i]-Flow[u][i]));

                }
            }
            if(pre[t]!=-1)//Determine whether there is an augmented track.
            {
                int k = t;

                /*
                cerr << "path: ";
        while(v != beg){
            cerr << v << " <- ";
            p = path[v];
            cap[p][v] -= flow;
            cap[v][p] += flow;

            v = p;
        }
        cerr << beg <<"\n";
                */

                cerr << "path: ";
                while(pre[k]>=0)
                {
                    cerr << pre[k] << " <- ";
                    Flow[pre[k]][k]+=MinFlow[t];
                    Flow[k][pre[k]]-=MinFlow[t];
                    k = pre[k];
                }
                cerr << -1 <<"\n";
                break;
            }
        }
        if(pre[t]==-1)
        {
             cerr << "MinFlow ans: " << ans << "\n";
            return ans;

        }
        else
        {
            cerr << "MinFlow: " << MinFlow[t] << " (adding)\n";
            ans += MinFlow[t];
        }
    }

}

int n,m;

int main()
{
    int test;
    cin >> test;
    while(test--){
        cin >> n >> m;
        int u,v;
        memset(Map,0,sizeof(Map));
        for(int i=0;i<n;i++)
        {
            Map[i][i+n]=1;
        }
        for(int i=1;i<=m;i++)
        {
            scanf(" (%d,%d)",&u,&v);
            Map[u+n][v]=Map[v+n][u]=INF;
        }
        int ans = INF;
        for(int i=1;i<n;i++)//Enumerate to find the smallest number of independent tracks
        {
            ans  = min(ans,MaxFlow(n*2,n,i));
        }
        if(ans == INF)
        {
            ans = n;
        }
        printf("%d\n",ans);
    }
    return 0;
}