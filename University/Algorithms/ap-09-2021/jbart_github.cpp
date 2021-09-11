#include<iostream>
#include<vector>
#include<queue>
#include<set>
using namespace std;
const int maxN=50;

struct str
{
    int a;
    int b;
    int w;

    bool operator< (str const &q) const {return w <= q.w;};

    str(int _a,int _b,int _w)
    {
        a=_a;
        b=_b;
        w=_w;
    }

    str()
    {

    }

};
str good(str s, int n)
{
    if(s.a!=n)
        swap(s.a,s.b);

    return s;
}
void print(set<str> a)
{
    for(set<str>::iterator it=a.begin();it!=a.end();it++)
    {
        cout<<it->a<<" "<<it->b<<" "<<it->w<<endl;
    }
}
int minima[maxN][maxN];
int main()
{
    ios_base::sync_with_stdio(0);
    int n,m,a,b,w;
    cin>>n>>m;

    int l=n-1;

    int* odw = new int[n+5];
    for(int i=0;i<n+5;i++)
    {
        odw[i]=0;
    }

    vector<str> tab;
    vector<str> drzewo;
    vector<vector<str> > drzewo2(n+2);
    set<str> mojset;

    for(int i=0;i<m;i++)
    {
        cin>>a>>b>>w;
        str s(a,b,w);

        tab.push_back(s);
        mojset.insert(s);
    }
    while(l>0)
    {
        if(!(odw[mojset.begin()->a]==1 && odw[mojset.begin()->b]==1)) // jesli nieodwiedzone
        {
            odw[mojset.begin()->a]=1; // odwiedz
            odw[mojset.begin()->b]=1;
            drzewo.push_back(*mojset.begin()); // dodaj krawedz do drzewa
            drzewo2[mojset.begin()->a].push_back(good(*mojset.begin(),mojset.begin()->a)); // dodaj do drzewa krawedzie
            drzewo2[mojset.begin()->b].push_back(good(*mojset.begin(),mojset.begin()->b));
            l--;
        }
        mojset.erase(mojset.begin());
    }

    /**/
    
    for(auto x : drzewo2){
        for(auto y : x){
            cerr << "("<<y.a<<", "<<y.b<<", "<<y.w<<") ";
        }
        cerr << "\n";
    }
    cerr << "\n";
    
    /**/

    for(int sou=1;sou<=n;sou++)
    {
        queue<int> kol;
        minima[sou][sou]=-1;
        kol.push(sou);
        while(!kol.empty())
        {
            int u=kol.front();
            kol.pop();
            for(int i=0;i<drzewo2[u].size();i++)
            {

                if(minima[sou][drzewo2[u][i].b]==0)
                {
                   kol.push(drzewo2[u][i].b);
                   minima[sou][drzewo2[u][i].b]=max(minima[sou][u],drzewo2[u][i].w);
                }
            }
        }
    }
//    cout<<tab.size()<<endl;
    for(int i=0;i<tab.size();i++)
    {
        //cout<<tab[i].a<<" "<<tab[i].b<<endl;
        if(tab[i].w<=minima[tab[i].a][tab[i].b])
            cout<<"TAK"<<endl;
        else
            cout<<"NIE"<<endl;
    }

/*
    for(int i=0;i<drzewo.size();i++)
    {
        cout<<drzewo[i].a<<" "<<drzewo[i].b<<" "<<drzewo[i].w<<endl;
    }
    for(int i=0;i<drzewo2.size();i++)
    {
        cout<<i<<endl;
        for(int j=0;j<drzewo2[i].size();j++)
        {
            cout<<drzewo2[i][j].a<<" "<<drzewo2[i][j].b<<" "<<drzewo2[i][j].w<<endl;;
        }
        cout<<endl<<endl;
    }
    for(int i=1;i<n+1;i++)
    {
        for(int j=1;j<n+1;j++)
        {
            cout<<minima[i][j]<<" ";
        }
        cout<<endl;
    }*/
    delete odw;

    return 0;
}