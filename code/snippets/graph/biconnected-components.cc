#include <bits/stdc++.h>
using namespace std;

// a biconnected component is a subgraph in which the minimum cut
// between any two vertices (a,b) is greater than or equal to 2
//
// note that a vertex may appear in multiple BCCs, but an edge
// is in exactly 1. single edge components are not biconnected
//
// the graph of biconnected components is a tree, proof by
// contradiction (¬tree => cycle => uncontracted BCC)

#define V_MAX 2000    // maximum vertex-count (important: includes blocks)
#define E_MAX 1000000 // maximum edge-count

// unlike SCCs, BCCs are defined in terms of edges
int component[E_MAX];
int components=0;

map<int,int> edge[V_MAX];
stack<int> dfs_tree;
bool seen[E_MAX];
int vertices=0;
int edges=0;

int root[V_MAX];
int idex[V_MAX];
int indices=0;

void add_edge(int a,int b) {if (not edge[a].count(b)) edge[a][b]=edge[b][a]=edges++;}

int dfs(int x){
  if (~idex[x]) return idex[x]; else root[x] = idex[x] = indices++;

  for (auto e: edge[x]){
    if (not seen[e.second])
      seen[e.second]=true, dfs_tree.push(e.second);

    root[x]=min(root[x],dfs(e.first));

    if (idex[x]<=root[e.first])
      for (int i=(++components,-1); i!=e.second; component[i]=components-1)
        i=dfs_tree.top(), dfs_tree.pop();
  }
  return root[x];
}

void build_tree(){
  vector<int> comps;
  for (int i=vertices; i--; comps.clear()){
    for (auto e: edge[i]) comps.push_back(vertices+component[e.second]);
    edge[i].clear(); for (auto j: comps) add_edge(i,j);
  }
}

int main(){
  // simple graph
  edges=0, vertices=2;
  add_edge(0,1);

  // reset state
  fill(idex,idex+vertices,-1);
  fill(seen,seen+edges,false);
  components=indices=0;

  // compute the component for each edge
  for (int i=vertices; i--;) dfs(i);

  // make an unrooted cut tree from this information
  build_tree();
}

