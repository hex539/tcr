#include <bits/stdc++.h>
using namespace std;
typedef unsigned uint;
#define dvec(T,N) typedef vector<T> N

struct edge_t {
  int dst;
  uint cost;
  edge_t(int a=-1, uint b=-1) {
    dst = a;
    cost = b;
  }
  bool operator < (edge_t const& other) const {
    return cost > other.cost;
  }
};

dvec(int,vi);
dvec(uint,vu);
dvec(edge_t,ve);
dvec(ve,vve);

/**
  Floyd-Warshall algorithm - O(N^3)

  Slow
*/
uint distance_fw(vve const &edge){
  int const n = edge.size();

  uint matrix[n][n]={};

  for (int i=n; i--;)
    for (int j=n; j--;)
      matrix[i][j]=~(unsigned)(i!=j);

  for (int i=n; i--;)
    for (int j=edge[i].size(); j--;)
      matrix[i][edge[i][j].dst]=edge[i][j].cost;

  for (int i=n; i--;)
    for (int j=n; j--;)
      for (int k=n; k--;)
        matrix[j][k]=min(matrix[j][k],matrix[j][i]+matrix[i][k]);

  return matrix[0][n-1];
}

/**
  Dijkstra's algorithm - O(MlogM)

  Only efficient for positive edge weights - can take O(NM . logM)
  time to identify negative cycles
**/
uint distance_djk(vve const &edge) {
  int its = edge.size() * edge.size();

  vu dist(edge.size(), -1); dist[0] = 0;
//vi prev(edge.size(), -1);

  priority_queue<edge_t> todo;
  todo.push(edge_t(0,0));
  while (not todo.empty() and its--) {
    int k = todo.top().dst; todo.pop();
    for (int i = edge[k].size(); i--;) {
      if (dist[k] + edge[k][i].cost < dist[edge[k][i].dst]) {
//      prev[edge[k][i].dst] = k;
        dist[edge[k][i].dst] = dist[k] + edge[k][i].cost;
        todo.push(edge_t(edge[k][i].dst, dist[edge[k][i].dst]));
      }
    }
  }
  return ++its? dist.back(): -1;
}
