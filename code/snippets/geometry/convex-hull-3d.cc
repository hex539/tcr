// <algorithm> <cstdio> <vector> <cmath> {typedef long double real} // O(N^2 . logN)
#define V3C vec3 const&
#define EPS (1e-10L)
bool fcmp(real a,real b=0L){return fabs(a-b)<=EPS;}
struct vec3{
  real x,y,z;
  vec3(real x=0,real y=0,real z=0):x(x),y(y),z(z){}
  bool operator < (V3C a) const {return x+EPS<a.x or x-EPS<a.x and (y+EPS<a.y or y-EPS<a.y and z+EPS<a.z);}
  vec3 operator + (V3C a) const {return vec3(x+a.x,y+a.y,z+a.z);}                   // addition
  vec3 operator - (V3C a) const {return vec3(x-a.x,y-a.y,z-a.z);}                   // subtraction
  real operator * (V3C a) const {return x*a.x+y*a.y+z*a.z;}                         // dot product
  vec3 operator / (V3C a) const {return vec3(y*a.z-z*a.y,z*a.x-x*a.z,x*a.y-y*a.x);} // cross product
  vec3 operator * (real const a) const {return vec3(x*a,y*a,z*a);}                  // scalar multiply
  vec3 operator / (real const a) const {return vec3(x/a,y/a,z/a);}                  // scalar divide
  real length() const {return sqrtl(*this**this);}                                  // no idea
  vec3 normalise() const {return *this/length();}                                   // "" """"
};
struct tri3{
  vec3 *a,*b,*c;
  tri3(vec3 *a=0,vec3 *b=0,vec3 *c=0):a(a),b(b),c(c) {if(b<a)swap(a,b);if(c<a)swap(a,c);if(c<b)swap(b,c);}
  bool operator < (tri3 const& o) const {return a<o.a or (a==o.a and b<o.b or b==o.b and c<o.c);}
  real area() const {return fabs(((*b-*a)/(*c-*a)).length())/2L;}
};
bool colinear (V3C a,V3C b,V3C c) {return fcmp(1,fabs(((b-a).normalise())*((c-a).normalise())));}
bool coplanar (V3C a,V3C b,V3C c,V3C d) {return colinear(a,b,c) or fcmp(0,((b-a)/(c-a))*(d-a));}
real tetrahedron_vol (V3C a,V3C b,V3C c,V3C d) {return fabs((a-d)*((b-d)/(c-d)))/6L;}

vector<tri3> hull(vec3 *begin,vec3 *end){
  vector<tri3> res;
  if (end-begin<4) return res;
  for (vec3 *i=begin; i+1<end; ++i) if (end[-1]<*i)                               swap(end[-1],*i);
  for (vec3 *i=begin; i+2<end; ++i) if (*i<end[-2])                               swap(end[-2],*i);
  for (vec3 *i=begin; i+3<end; ++i) if (not colinear(*i,end[-2],end[-1]))         swap(end[-3],*i);
  for (vec3 *i=begin; i+4<end; ++i) if (not coplanar(*i,end[-3],end[-2],end[-1])) swap(end[-4],*i);
  if (coplanar(end[-1],end[-2],end[-3],end[-4])) return res;

  vec3 centre;
  for (vec3 *i=end; i-->end-4;) centre=centre+(*i/4L);
  for (int i=5; --i;) res.push_back(tri3(&end[-4+(3<i)],&end[-3+(2<i)],&end[-2+(1<i)]));

  for (vec3 *i=end-4; i-->begin;){
    int size=0;
    vector<pair<vec3*,vec3*> > toggle;
    for (int j=0; j<res.size(); ++j){
      vec3 *u=res[j].a,
           *v=res[j].b,
           *w=res[j].c,
          nml=(*v-*u)/(*w-*u),
          mid=(*u+*v+*w)/3L;
      if ((nml*(centre-mid))*(nml*(*i-mid))<0L)
        toggle.push_back(make_pair(u,v)),
        toggle.push_back(make_pair(u,w)),
        toggle.push_back(make_pair(v,w));
      else res[size++]=res[j];
    }
    res.resize(size);
    sort(toggle.begin(),toggle.end());
    for (int k,j=toggle.size()-1; j>=0; j=k){
      for (k=j; k>=0 and not (toggle[k]<toggle[j]); k--);
      if ((j-k)&1) res.push_back(tri3(toggle[j].first,toggle[j].second,i));
    }
  }
  return res;
}

int main(){
  int tsts; scanf("%d",&tsts); while (tsts--){
    static vec3 v[1234];
    int n; scanf("%d",&n); for (int i=n; i--;) scanf("%Lf %Lf %Lf",&v[i].x,&v[i].y,&v[i].z);
    vector<tri3> res=hull(v,v+n);
    real sa=0L, vol=0L;
    vec3 centre;
    for (vector<tri3>::iterator i=res.begin(); i!=res.end(); ++i)
      sa+=i->area(), centre=centre+(*i->a+*i->b+*i->c)/(res.size()*3);
    for (vector<tri3>::iterator i=res.begin(); i!=res.end(); ++i)
      vol+=tetrahedron_vol(centre,*i->a,*i->b,*i->c);
    printf("%.8Lf %.8Lf\n",sa,vol);
  }
}
