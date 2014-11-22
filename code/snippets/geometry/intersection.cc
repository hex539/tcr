#include <bits/stdc++.h>
typedef long double ll; using namespace std;

struct vec2{
  ld x,y;

  vec2 operator-(vec2 const &a)const{return {x-a.x,y-a.y};}
  vec2 operator+(vec2 const &a)const{return {x+a.x,y+a.y};}
  vec2 operator*(ld const a)const{return {x*a,y*a};}
  vec2 operator/(ld const a)const{return {x/a,y/a};}
  ld cross_z(vec2 const &a) const{return y*a.x - x*a.y;} // z component of cross product
  ld dot(vec2 const &a) const{return x*a.x+y*a.y;} // scalar product
  ld length() const{return hypotl(x,y);} // length
  vec2 rot() const{return {-y,x};} // anticlockwise 90^

  // circle-to-tangent angle for r=`radius` at (0,0)
  ld tangent_angle(ld radius,int which) const{
    return atan2l(y,x) + (M_PI/2.L - asinl(radius/hypot())) * (which? -1: 1);
  }

  bool within_polygon(vector<vec2> const &v) const{
    bool res=false;

    for (int i=0, j=v.size(); i<v.size(); j=i++){
      if ((v[j].y<y) == (v[i].y<y)) continue;

      ld px=v[j].x+(v[i].x-v[j].x)*(y-v[j].y)/(v[i].y-v[j].y);

      if ( ((*this)-v[j]).cross_z(v[i]-v[j]) > 0) continue;

      res=not res;
    }
    return res;
  }

  ld distance_to_line(vec2 s,vec2 t,bool infinite=false){
    vec2 v=t-s;
    s-=*this;
    t-=*this;

    if (not infinite){
      if (v.dot(s) >= 0) return s.length();
      if (v.dot(t) <= 0) return t.length();
    }

    return (s-v*(s.dot(v))).length();
  }
}

