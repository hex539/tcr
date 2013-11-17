#include <algorithm>
#include <cstdio>
#include <vector>
#include <map>
using namespace std;

map<int,int> flow[1000];
map<int,int> cost[1000];

int mincost_flow(int n){
  for (int res=0;;){
    vector<int> dist(n,1<<29);
    vector<int> from(n,-1);
    dist[0]=0;
    for (int spfa=1; spfa--;)
      for (int i=0; i<n; i++){
        map<int,int>::iterator it=flow[i].begin(), jt=cost[i].begin();
        for (; it!=flow[i].end(); ++it,++jt){
          if (it->second>0 and dist[i]+jt->second<dist[it->first]){
            dist[it->first]=dist[i]+jt->second;
            from[it->first]=i;
            spfa=1;
          }
        }
      }
    if (dist[n-1]==1<<29) return res;
    for (int i=n-1; i; i=from[i])
      res+=cost[from[i]][i],
      flow[i][from[i]]++,
      flow[from[i]][i]--;
  }
}

void add_edge(int x,int y,int cap,int tax){
  flow[x][y]+=cap;
  flow[y][x]+=0;
  cost[x][y]=tax;
  cost[y][x]=-tax;
}

/**
  Example usage
**/

int main() {
  add_edge(0,1, 4,4); // 4*4
  add_edge(1,2, 3,6); // 2*6
  add_edge(1,3, 3,9); // 2*9
  add_edge(2,4, 2,2); // 2*2
  add_edge(3,4, 5,0); // 3*0
  printf("%d\n",mincost_flow(5)); // 50
}
