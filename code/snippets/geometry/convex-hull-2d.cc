#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
#define $(x) ((x).size())
#define allof(x) ((x).begin(),(x).end())

struct pt{
  int x,y;
  bool operator<(pt const u)const{return x<u.x or x==u.x and y<u.y;}
  pt operator-(pt const u)const{pt res={x-u.x,y-u.y}; return res;}
};
int cross2d(pt const a,pt const b){return a.y*b.x-a.x*b.y;}
int dot(pt const a,pt const b){return a.x*b.x+a.y*b.y;}
typedef pair<int,int> pi;
typedef vector<pt> vpt;
typedef vector<pi> vpi;

/// extract the convex hull of an iterable range
vpt convex_hull(pt* beg,pt* end){
  vpt up,dn,res(beg,end);
  sort(res.begin(),res.end());
  for (auto v: res){
    while (up.size()>1 and cross2d(v-up[$(up)-1],up[$(up)-1]-up[$(up)-2]) <= 0) up.pop_back(); up.push_back(v);
    while (dn.size()>1 and cross2d(v-dn[$(dn)-1],dn[$(dn)-1]-dn[$(dn)-2]) >= 0) dn.pop_back(); dn.push_back(v);
  }
  res.clear();
  res.insert(res.end(), up. begin()+1, up. end());
  res.insert(res.end(), dn.rbegin()+1, dn.rend());
  return res;
}

/// find all antipodal line/point pairs
void rotating_calipers(pt* begin,pt* end,int(*callback)(pt const&,pt const&,pt const&)){ if (begin+3>end) return;
  for (pt *a=begin, *b=end-1, *c=begin+1; a!=end; b=a++){
    pt nml=(*b-*a);
    swap(nml.x,nml.y); nml.y*=-1;
    pt *pc=(c==begin? end:c)-1;
    pt *nc=(c==end-1? begin:c+1);
    while (dot(*c-*pc,nml)<0 or dot(*c-*nc,nml)<0){
      callback(*a,*b,*c);
      pc=c;
      c=nc;
      nc=(c==end-1? begin:c+1);
    }
    callback(*a,*b,*c);
  }
}

/**
  Example usage
   - solving the problem TFOSS from SPOJ Tutorial problemset
**/

long long best;
int rc_callback(pt const& a,pt const& b,pt const& c){
  best=max(best,(long long) dot(a-c,a-c));
  best=max(best,(long long) dot(b-c,b-c));
  return 0;
}

int main(){
  #ifndef ONLINE_JUDGE
  freopen("tfoss.in","r",stdin);
  #endif

  int tsts; scanf("%d",&tsts); while (tsts--){
    best=0;
    int n; scanf("%d",&n);
    pt p[n]; for (int i=n; i--;) scanf("%d %d",&p[i].x,&p[i].y);
    vpt h=convex_hull(p,p+n);
    rotating_calipers(&h[0],&h[0]+$(h),rc_callback);
    printf("%lld\n",best);
  }
}
