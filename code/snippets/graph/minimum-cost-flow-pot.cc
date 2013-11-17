#include <bits/stdc++.h>
using namespace std; typedef long long ll;

ll const inf=1ll<<55ll;
int n; // number of vertices

struct Edge{
  int s,t;
  ll cap,cost;
  Edge *rev;
  static Edge E[];
  static int N;
};
Edge Edge::E[8016];
int Edge::N=0;

vector<Edge*>  edge[8016]; // need 2*edges due to reverses
bool          done[8016];
Edge*          from[8016];
ll            dist[8016], pot[8016];

void add_edge(int s,int t,ll cap,ll cost){
  Edge::E[Edge::N]={s,t,cap,cost,Edge::E+Edge::N+1};
  edge[s].push_back(Edge::E+Edge::N++);

  Edge::E[Edge::N]={t,s, 0,-cost,Edge::E+Edge::N-1};
  edge[t].push_back(Edge::E+Edge::N++);
}

ll augment(){
  /* Reset accumulators */
  for (int i=n; i--;) done[i]=from[i]=0, dist[i]=inf;

  /* Dijkstra's algorithm */
  priority_queue<pair<ll,int>> todo;
  for (todo.push(make_pair(dist[0]=0,0)); not todo.empty();){
    int x=todo.top().second; todo.pop();
    if (done[x]) continue; else done[x]=true;
    for (auto& y: edge[x])
      if (y->cap)
        for (ll d=dist[x]+y->cost+pot[x]-pot[y->t]; d<dist[y->t] and not done[y->t]; ++d)
          todo.push(make_pair(-d,y->t)),
          from[y->t]=y,
          dist[y->t]=d;
  }

  /* Update vertex potentials */
  for (int i=n; i--;) pot[i]=min(inf,pot[i]+dist[i]);
  if (not from[n-1]) return 0;

  /* Propagate augmentation */
  ll flow=inf, cost=0;
  for (int x=n-1; x; x=from[x]->s) flow=min(flow,from[x]->cap), cost+=from[x]->cost;
  for (int x=n-1; x; x=from[x]->s) from[x]->cap-=flow, from[x]->rev->cap+=flow;
  return flow*cost;
}

ll mcmf(){
  ll res=0;
  for (int i=n; i--;) pot[i]=0;
  do res+=augment(); while (done[n-1]);
  return res;
}

// add edges and then... 
ll cost=mcmf();
for (int i=0; i<m; i++)
  cout<<Edge::E[i*2].rev->cap<<(i+1==m?'\n':' ');
