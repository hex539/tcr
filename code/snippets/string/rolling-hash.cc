#include <bits/stdc++.h>
using namespace std; typedef long long ll;

/* O(1) computation for hashes of arbitrary substrings */
/* {base, mod} need to be coprime 32-bit integers */
template<ll base,ll mod> struct hasher{
  vector<ll> val,pin;

  hasher(string const &s){
    val.resize(s.size());
    pin.resize(s.size());

    ll inv=1;
    ll sqr=base;
    for (ll i=mod-2; i; i>>=1){
      if (i&1) (inv*=sqr)%=mod;
      (sqr*=sqr)%=mod;
    }

    ll mul=1;
    pin[0]=1;

    for (int i=1; i<s.size(); i++){
      pin[i]=(pin[i-1]*inv)%mod;
    }
    for (int i=0; i<s.size(); i++){
      val[i]=(s[i]*mul+(i?val[i-1]:0))%mod;
      (mul*=base)%=mod;
    }
  }

  ll describe(int x,int len){
    return ((val[x+len-1]-(x? val[x-1]: 0)+mod)*pin[x])%mod;
  }
};

/* Multiplexes several hashers for robustness */
struct failsafe{
  hasher<353ll,11111117ll> a;
  hasher<191ll,16431563ll> b;
  hasher<569ll,147483667ll> c;

  /* constructor */
  failsafe(string const s):
    a(s),
    b(s),
    c(s) {}

  /* substring hash */
  ll describe(int x,int len){
    return (a.describe(x,len)<<0ll)
       xor (b.describe(x,len)<<10ll)
       xor (c.describe(x,len)<<20ll);
  }

  /* Prefer this to describe(x,len)==describe(y,len) -- it's more accurate */
  bool same(int x,int y,int len){
    return a.same(x,y,len)
       and b.same(x,y,len)
       and c.same(x,y,len);
  }
};

int main(){
  string s="banana";
  failsafe checker(s);
  assert(checker.describe(1,3) == checker.describe(3,3));
  assert(checker.describe(1,2) != checker.describe(4,2));
}
