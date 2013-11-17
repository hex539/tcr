typedef long double ld

struct vec2 {ld x,y;
  vec2 (ld a=0,ld b=0): x(a), y(b) {}
  vec2 operator + (vec2 const u) const {return vec2(x+u.x,y+u.y);}
  vec2 operator - (vec2 const u) const {return vec2(x-u.x,y-u.y);}
  bool operator < (vec2 const u) const {return x<u.x or x==u.x and y<u.y;}
  ld len() const {return sqrtl(x*x+y*y);}};
ld radius(vec2 a,vec2 b,vec2 c) {return (a-b).len() * (b-c).len() * (c-a).len() / 2.0 / abs(crz(c-a,b-a));}
ld dot(vec2 a,vec2 b) {return a.x*b.x + a.y*b.y;}
ld crz(vec2 a,vec2 b) {return a.y*b.x - a.x*b.y;}

struct t3 {int a, b, c; ld radius; bool operator < (t3 const u) const {return radius<u.radius;}};
vec2 v[400], ha[400], hu[400], hd[400];
bool bad[400];

int main() { // ...
  // convex hull
  sort(v,v+n);
  int uc=0, dc=0, hc=0;
  for (int i=n; i--;) {
    while (uc>1 and crz(v[i]-hu[uc-1],hu[uc-1]-hu[uc-2]) >= 0) --uc; hu[uc++]=v[i];
    while (dc>1 and crz(v[i]-hd[dc-1],hd[dc-1]-hd[dc-2]) <= 0) --dc; hd[dc++]=v[i]; }
  for (int i=uc; i-->1;) ha[hc++] = hu[     i];
  for (int i=dc; i-->1;) ha[hc++] = hd[dc-1-i];
  for (int i=hc; i--;) bad[i]=0;
  // initial list of candidate circles for the 3-control case
  priority_queue<t3> todo;
  for (int i=hc; i>=0; i--) {
    t3 t = {(i-1) % hc, (i  ) % hc, (i+1) % hc, radius(ha[t.a],ha[t.b],ha[t.c])};
    todo.push(t); }
  // generate new candidates
  long double best = (1e30);
  int remain = hc;
  vec2 victor;
  while (not todo.empty()) {
    int a = todo.top().a, b = todo.top().b, c = todo.top().c;
    ld r = todo.top().radius;
    todo.pop();
    if (not bad[a] and not bad[b] and not bad[c]) {
      bad[b] = 1; --remain;
      if (remain>=2 and
        (ha[a].x-ha[b].x) * (ha[b].y-ha[c].y)
      !=(ha[a].y-ha[b].y) * (ha[b].x-ha[c].x) ) {
        if (r<=best) {
          ld ax=ha[a].x, ay=ha[a].y,
             bx=ha[b].x, by=ha[b].y,
             cx=ha[c].x, cy=ha[c].y;
          ld t=((bx+cx)*(bx-cx)+(by+cy)*(by-cy)+(ax+bx)*(cx-bx)+(ay+by)*(cy-by))/((ay-by)*(bx-cx)+(ax-bx)*(cy-by));
          victor.x=((ax+bx)+(ay-by)*t)*0.5;
          victor.y=((ay+by)+(bx-ax)*t)*0.5;
          best=r;
      } }
      bool colin = (ha[a].x-ha[b].x) * (ha[b].y-ha[c].y) == (ha[a].y-ha[b].y) * (ha[b].x-ha[c].x);
      if (remain>=3 and not colin) {
        int d=(c   +1)%hc; while (bad[d]) (++d)%=hc;
        int e=(a+hc-1)%hc; while (bad[e]) (e+=hc-1)%=hc;
        t3 u={e,a,c,radius(ha[e],ha[a],ha[c])};
        t3 v={a,c,d,radius(ha[a],ha[c],ha[d])};
        todo.push(u);
        todo.push(v);
  } } }
  // O(N^2) brute force for the case where there are only 2 control points. Rotating calipers is fine too
  ld worst=0;
  int a=0,b=0,ok=1;
  for (int i=hc; i--;)
    for (int j=i; j--;)
      if ((ha[i]-ha[j]).len()/2>=worst)
        worst=(ha[i]-ha[j]).len()/2,
        a=i, b=j;
  vec2 mep=ha[a]+ha[b]; mep.x/=2; mep.y/=2;
  for (int i=hc; i--;) ok &= ((ha[i]-mep).len() <= worst);
  if (ok and worst<best) victor = mep, best = worst;
  printf("%.2Lf\n",best*2.);
}
