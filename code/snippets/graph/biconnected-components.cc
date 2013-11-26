#define V_MAX 10000
#define E_MAX 100000

int component[E_MAX];
int components=0;

multimap<int,int> edge[V_MAX];
stack<int> dfs_tree;

int root[V_MAX];
int idex[V_MAX];
int indices=0;

void add_edge(int a,int b,int id){
  edge[a].insert({b,id});
  edge[b].insert({a,id});
}

void dfs(int x,int p=-1){
  if (~idex[x]) return; else root[x] = idex[x] = indices++;

  for (auto e: edge[x]){
    if (!~idex[e.first]){
      dfs_tree.push(e.second);
      dfs(e.first,e.second);

      if (idex[x] <= root[e.first]){
        while (true){
          int y = dfs_tree.top(); dfs_tree.pop();
          component[y]=components;
          if (y == e.second) break;
        }
        ++components;
      }

      root[x]=min(root[x],root[e.first]);
    }
    else if (e.second != p and idex[e.first] < idex[x]){
      dfs_tree.push(e.second);

      root[x]=min(root[x],idex[e.first]);
    }
  }
}

int main(){
  int n,m; cin>>n>>m;
  memset(idex,-1,sizeof idex);
  for (int i=0; i<m; i++) {int a,b; cin>>a>>b; --a,--b; add_edge(a,b,i);}

  for (int i=0; i<n; i++) if (!~idex[i]) dfs(i);

  vector<int> bridges;
  static int subscribed[E_MAX];
  for (int i=0; i<m; i++) ++subscribed[component[i]];
  for (int i=0; i<m; i++) if (subscribed[component[i]]==1) bridges.push_back(i);
}
