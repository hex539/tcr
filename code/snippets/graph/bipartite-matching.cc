#include <iostream>
#include <vector>
using namespace std;

// use one-based offsets- vertex 0 is special

// can also be used to find largest antichain in a partially ordered set
// (the maximum-sized subset where no two elements are comparable) by
// adding edges from the outgoing part of every vertex to the incoming
// part of every vertex which it is directly/indirectly comparable to
// and then finding a bipartite vertex cover.

// same technique applies for finding minimum number of disjoint paths to
// cover all vertices of a directed acyclic graph, but only link
// directly-connected vertices.

namespace hk{
  int n,m;       // number of vertices in left/right partitions [1..n] [n+1..n+m] (*m is not actually used)
  int a[100002]; // match id
  int q[ 50002]; // queue for bfs
  int d[ 50002]; // [distance from source - 1]
  vector<int> e[ 50002]; // edges [1..n] -> [n+1..n+m]


  bool bfs(){
    int *p=q,*r=q; d[0]=-1;
    for (int i=n+1; i-->1;) if (!a[i]) d[i]=0, r++[0]=i; else d[i]=-1;
    for (;p!=r;++p)
      for (auto y: e[*p])
        if (!~d[a[y]])
          d[r++[0]=a[y]]=d[*p]+1;
    return ~d[0];
  }

  bool dfs(int x){
    if (x==0) return true;
    for (auto y: e[x])
      if (d[a[y]]==d[x]+1 and dfs(a[y]))
        return a[x]=y, a[y]=x;
    d[x]=-1; return false;
  }

  /* minimally sized set of vertices that has at least
   * one endpoint of every edge as a member */
  vector<int> bipartite_vertex_cover(){
    vector<int> result;

    while (bfs()) for (int i=1; i<=n; i++) a[i] or dfs(i);

    for (int i=1; i<=n; ++i)
      if (~d[i]){
        for (auto y: e[i])
          if (y!=a[i] and a[y])
            result.push_back(y), a[y]=0;
      }
      else result.push_back(i);

    return result;
  }
}

int main(){
  ios::sync_with_stdio(false);

  int ec;
  cin>>hk::n>>hk::m>>ec;
  while (ec--){
    int u,v; cin>>u>>v;
    v+=hk::n;
    hk::e[u].push_back(v);
  }

  int count=0;
  while (hk::bfs()) for (int i=1; i<=hk::n; i++) if (!hk::a[i] and hk::dfs(i)) ++count;
  cout<<count<<endl;
}
