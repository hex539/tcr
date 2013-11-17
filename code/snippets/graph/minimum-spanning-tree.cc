#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

#define nullptr 0
typedef vector<int> vi;

/**
 *  Disjoint-set data structure
 *   - like link/cut tree but only supports
 *     the LINK and FINDROOT operations
**/

typedef struct UnionFind{
  UnionFind* p;
  int rank;

  UnionFind(): p(this), rank(0) {}

  UnionFind* root(){
    return p==this? p: p=p->root();
  }

  bool merge(UnionFind* v){
    UnionFind *a=root(), *b=v->root();
    if (a==b) return false;
    if (b->rank>a->rank) swap(a,b);
    b->p=a, a->rank++;
    return true;
  }
} Vertex;

struct Edge{
  Vertex *src,*dst;
  int cost;

  bool operator<(Edge const& other) const{
    return cost<other.cost;
  }
};

vector<Edge> mst(Edge* edge,int n){
  sort(edge,edge+n);

  vector<Edge> result;
  for (int i=0; i<n; i++)
    if (edge[i].src->merge(edge[i].dst))
      result.push_back(edge[i]);

  return result;
}

/**
 *  Example usage
 */

int main(){
  Vertex v[4];
  Edge e[]={
    {v+0,v+1, 2},
    {v+1,v+2, 3},
    {v+2,v+3, 4},
    {v+0,v+2, 1}
  };

  vector<Edge> result=mst(e,4);
  for (int i=0; i<result.size(); i++)
    printf("[%d %d] %d\n",(int)(result[i].src-v),(int)(result[i].dst-v),result[i].cost);
}
