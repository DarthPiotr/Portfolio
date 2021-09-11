 
// ingenious dynamic programming on tree
#include <algorithm>
#include <cstdio>
#include <deque>
#include <utility>
#include <vector>
#include <iostream>
using namespace std;

typedef pair<int, int> pii;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define fi first
#define mp make_pair
#define pb push_back
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
vector<int> e[N];

// {C, {A, B}}
// C: whether A covers the parent edge
// A: cost of subtree(v)
// B: cost of subtree(v)+parent edge; parent edge is the end of some path
// A <= B <= A+1
int dfs_depth;
pair<bool, pii> dfs(int v, int p)
{
    for(int ddd=0; ddd < dfs_depth; ++ddd) cerr << " ";
    cerr << "Entering dfs with v: " << v << "; p: " << p << "\n";
  deque<pii> c;
  int t = -1;
  bool has = false;
  for (auto u: e[v]) // dla każdego sąsiada v
    if (u != p) {    // który nie jest jego rodzicem
    dfs_depth++;
      auto r = dfs(u, v); // wywołujemy dfs
    dfs_depth--;
      if (! r.fi) // jeśli dfs zwrócił pierwsze 0 (fałsz) - czy A obejmuje krawędź rodzica
        has = true; // ustaw has na true
      if (r.se.fi == r.se.se){ // jeśli A == B
        c.push_front(r.se);   // dodaj {A, B} na początek stosu
        for(int ddd=0; ddd < dfs_depth; ++ddd) cerr << " ";
    cerr << "Adding at front\n";
      }
      else{
        c.pb(r.se);           // dodaj {A, B} na koniec stosu
        for(int ddd=0; ddd < dfs_depth; ++ddd) cerr << " ";
    cerr << "Adding at end\n";
      }
      t = u;            // t na obecny wierzchołek
    }
  if (c.empty()){   // jeśli nic nie dodano = wierzchołek v jest końcowy
      for(int ddd=0; ddd < dfs_depth; ++ddd) cerr << " ";
      cerr << "Final vertex. Returning {0, {0, 1}}\n";
    return {false, pii{0, 1}};
  }

    for(int ddd=0; ddd < dfs_depth; ++ddd) cerr << " ";
      cerr << "C:\n";
      
      for(int iii = 0; iii < c.size(); ++iii){
     for(int ddd=0; ddd < dfs_depth; ++ddd) cerr << " ";
     cerr << "=> {"<<c[iii].first<<", "<<c[iii].second<<"}\n";
      }

  bool cover = false;
  int f = 0, g = 0, i = 0;
  for (; i+1 < c.size() && c[i+1].fi == c[i+1].se; i += 2) // beneficial to pair B if the A=B for some child
    f += c[i].se+c[i+1].se-1, cover = true;
  if (i < c.size()) {
    g = f+c[i].se;
    if (c[i].fi == c[i].se)
      cover = true;
    // if A < B for all children and some child is uncovered
    f += ! cover && has ? cover = true, c[i].se : c[i].fi;
    while (++i < c.size())
      f += c[i].fi, g += c[i].fi;
  } else
    g = f+1; // all children are paired, one more edge is needed to cover the parent edge
    for(int ddd=0; ddd < dfs_depth; ++ddd) cerr << " ";
     cerr << "Returning {"<<cover<<", {"<<f<<", "<<g<<"}}\n";
  return {cover, {f, g}};
}

int n;

int main()
{
  for (int cc = ri(); cc--; ) {
    n = ri();
    for (int i = 0; i < (n); i++)
      e[i].clear();
    for (int i = 0; i < (n-1); i++) {
      int u = ri(), v = ri();
      e[u].pb(v);
      e[v].pb(u);
    }

for (int i = 0; i < (n); i++){
    cerr << i << ": ";
    for(int j = 0; j < e[i].size(); ++j){
        cerr << e[i][j] << " ";
    }
    cerr << "\n";
}



    dfs_depth = 0;
    printf("%d\n", dfs(0, -1).se.fi);
  }
}