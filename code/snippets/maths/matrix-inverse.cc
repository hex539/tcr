// <algorithm> <cstdio> {typedef long long ll} (import gcd code or __builtin_gcd for fractions)

struct fraction {
  ll num, den;
  fraction& simplify() {
    ll g = gcd(abs(num),abs(den)) * (den>0? 1:-1);
    return num/=g, den/=g, *this;
  }
  fraction(ll a=0,ll b=1):num(a),den(b) {simplify();}
  fraction& operator=(fraction const b) {num=b.num; den=b.den;}

  fraction operator + (fraction const b) const {return fraction(num*b.den+den*b.num, den*b.den);}
  fraction operator - (fraction const b) const {return fraction(num*b.den-den*b.num, den*b.den);}
  fraction operator * (fraction const b) const {return fraction(num*b.num, den*b.den);}
  fraction operator / (fraction const b) const {return fraction(num*b.den, den*b.num);}
  bool operator < (fraction const b) const {return num*b.den < den*b.num;}
  bool operator > (fraction const b) const {return num*b.den > den*b.num;}
};

fraction abs(fraction v){return v.num>=0? v: fraction(-v.num, v.den);}

int main() {
  long double mat[4][4]={{0,1,0,0}, {1,0,0,0}, {0,0,0,1}, {0,0,1,0}};
  long double inv[4][4]={{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
  long double p,q;

  int best=0;
  for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
      if (abs(mat[j][i]) > abs(mat[best][i]))
        best = j;
    for (int j=0; j<4; j++)
      swap(mat[i][j], mat[best][j]),
      swap(inv[i][j], inv[best][j]);
    for (int j=0; j<4; j++){
      p = mat[j][i];
      q = mat[i][i];
      if (j!=i){
        for (int k=0; k<4; k++)
          mat[j][k] = mat[j][k] - (mat[i][k] * p) / q,
          inv[j][k] = inv[j][k] - (inv[i][k] * p) / q;
      }else{
        for (int k=0; k<4; k++)
          mat[j][k] = mat[j][k] / p,
          inv[j][k] = inv[j][k] / p;
      }
    }
  }
}
