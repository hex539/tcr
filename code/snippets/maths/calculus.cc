#include <bits/stdc++.h>
typedef long double ld; using namespace std;

ld const tolerance = 1e-10L;

/* Function to evaluate */
ld fun(ld x){
  return abs(x) * cosl(x); // for example
}

/* Simpson's rule */
ld approx_curve(ld a,ld b){
  ld c=(a+b)/2;
  return (b-a)*(1/6.L)*(fun(a) + fun(b) + 4.L*fun(c));
}

/* Integrate from a..b to within error of a small multiple of `tolerance`
   -- consider randomising control points to avoid degenerate cases by
      altering mid from 50%/ split to eg. 0.5*(1+frand())/ split
*/
ld integrate(ld a,ld b,ld tot=1e234L){
  ld mid = (a+b)/2;

  ld lef = approx_curve(a,mid),
     rgt = approx_curve(mid,b);

  ld err = fabsl(lef+rgt-tot);
  if (err > tolerance){
    tot = integrate(a,mid,lef) + integrate(mid,b,rgt);
  }
  return tot;
}

int main(){
  cout.precision(8);
  cout<<fixed<<integrate(0,4)<<endl; // -4.6808536020953
}
