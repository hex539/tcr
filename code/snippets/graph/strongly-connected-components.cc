#include <bits/stdc++.h>
using namespace std;

int indices = 0;

struct Vertex {
  vector<Vertex*> edge;
  int idex, root, done;
  Vertex () : idex(-1), root(-1), done(0) {}

  int strong() {
    if (done) return done==2? indices: idex;
    done=1;

    static stack<Vertex*> tar; tar.push(this);
    root = idex = indices++;
    for (auto e: edge) root = min(root, e->strong());

    while (done == 1 and root == idex) {
      tar.top()->root = root;
      tar.top()->done = 2;
      tar.pop();
    }
    return root;
  }
};

// --- example usage
int main(){
  int const n = 4;
  int deps[n] = {};
  indices = 0;
  Vertex scc[n];
  Vertex v[n];

  v[0].edge.push_back(v+3); // pretend we read in a graph and want to do something involving
  v[1].edge.push_back(v+2); // dependency resolution on its SCC decomposition, eg. 2SAT.
  v[2].edge.push_back(v+3); // --
  v[3].edge.push_back(v+1); // this graph === (0) -> (1 -> 2 -> 3 -> 1)

  // --- compute strongly-connected indices
  for (int i = n; i --> 0;) {
    v[i].strong();
    scc[v[i].root].idex = i;

    // --- also make an extra DAG out of SCCs
    for (auto e: v[i].edge)
      if (e->root != v[i].root)
        scc[v[i].root].edge.push_back(e),
        deps[e->root]++;
  }

  // --- find SCCs with no in-edges
  vector<int> toposort;
  for (int i = indices; i --> 0;)
    if (deps[i] == 0 and ~scc[i].idex)
      toposort.push_back(i);

  // --- use those to get the full ordering
  for (int i = 0; i < toposort.size(); ++i)
    for (auto e: scc[toposort[i]].edge)
      if (not --deps[e->root])
        toposort.push_back(e->root);

  // --- print out a visualisation
  for (int i = 0; i < toposort.size(); ++i) {
    vector<Vertex*> related(1, v + scc[toposort[i]].idex);
    v[scc[toposort[i]].idex].done = 0;
    printf(":: %d", scc[toposort[i]].idex);
    for (int j = 0; j < related.size(); ++j)
      for (auto e: related[j]->edge)
        if (e->done and e->root == related[j]->root)
          e->done = 0, related.push_back(e),
          printf(" %d", (int)(e - v));
    puts("");
  }
}
