#include <bits/stdc++.h>
using namespace std;

struct vec2{
  int x;
  int y;
  vec2(int X=0,int Y=0):x(X),y(Y){}
  vec2 operator+(vec2 a)const{return vec2(x+a.x,y+a.y);}
  vec2 operator-(vec2 a)const{return vec2(x-a.x,y-a.y);}
  double length()const{return sqrt(x*x+y*y);}
};

struct byX{bool operator()(vec2 a,vec2 b){return a.x<b.x or a.x==b.x and a.y<b.y;}};
struct byY{bool operator()(vec2 a,vec2 b){return a.y<b.y or a.y==b.y and a.x<b.x;}};

int main(){
  int const n=4;
  double best=1e9;
  vec2 point[n]={
    vec2(0,0),
    vec2(2,0),
    vec2(0,2),
    vec2(1,1)};
  sort(point,point+n,byX());
  set<vec2,byY> relevant;
  for (int i=0,j=0,k=0; i<n; i++){
    while (j<k and point[j].x+best<=point[i].x) relevant.erase (point[j++]);
    while (k<i and point[k].x-best<=point[i].x) relevant.insert(point[k++]);
    auto left=relevant.lower_bound(point[i]-vec2(0,best)),
         right=relevant.upper_bound(point[i]+vec2(0,best));
    while (left!=right){
      best=min(best,(point[i]-*left).length());
      ++left;
    }
  }
  printf("%lf\n",best);
}
