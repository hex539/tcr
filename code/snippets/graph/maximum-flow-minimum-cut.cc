#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll const lots=1ll<<40ll;

struct Graph{
  int s,t;
  vector<map<int,ll>> edge;
  vector<ll> level;

  bool bfs(){
    level=vector<ll>(edge.size(),-1);
    queue<int> todo;
    level[s]=0;

    for (todo.push(s); not todo.empty(); todo.pop()){
      for (auto i: edge[todo.front()]){
        if (i.second<=0 or ~level[i.first]) continue;
        level[i.first]=level[todo.front()]+1;
        todo.push(i.first);
      }
    }
    return ~level[t];
  }

  ll dfs(int x, ll m=lots){
    if (x==t or not m) return m;
    ll res=0,k;

    for (auto &i: edge[x]){
      if (level[i.first]==level[x]+1 and (k=dfs(i.first,min(m-res,i.second)))){
        res+=k;
        i.second-=k;
        edge[i.first][x]+=k;
      }
    }

    if (not res) level[x]=-1;
    return res;
  }

  ll min_cut(){
    ll res=0;
    while (bfs()) res+=dfs(s);
    return res;
  }
};

int main(){
  Graph g={0,4};
  g.edge.resize(5);

  // The complete graph K_4
  for (int i=4; i--;)
    for (int j=4; j--;)
      if (i!=j)
        g.edge[i][j]=1;

  // Weight-2 edge to sink
  g.edge[3][4]=2;

  cout<<g.min_cut()<<endl;
}
