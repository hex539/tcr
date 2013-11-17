#include <bits/stdc++.h>
using namespace std; typedef long long ll;

bool isPrime(ll n){
  for (ll i = 2; i*i <= n; ++i) {
    if (n % i == 0) return false;
  }
  return true;
}

// modify for overflow if numbers are very large
bool isPrime64(ll n){
  static int small_primes[8] = {2,3,5,7,11,13,17,19};
  if (n<=20 or n%2==0) return binary_search(small_primes, small_primes+8, n);
  ll s=0,m=n-1; for (;m%2==0; m>>=1) ++s;
  for (int k=20; k--;){
    ll x=(rand()%(n-3))+2;
    for (ll i=m-1,q=x; i; (q*=q)%=n, i/=2) if (i&1) (x*=q)%=n;
    if (x-1!=0 and x+1!=n){
      for (ll i=s-1; i--;)
        if (1==((x*=x)%=n) or x+1==n) break;
      if (x+1!=n) return false;
    }
  }
  return true;
}

bool isPrime32(ll n){
  if (n<=4 or !(n&1)) return (n|1)==3;
  ll s=0,m=n-1; for (;m%2==0; m>>=1) ++s;
  static const ll small[]={2,7,61};
  for (int k=0; k<3; k++){
    ll x=small[k];
    if (n<=x) return n==x;
    for (ll i=m-1,q=x; i; (q*=q)%=n, i/=2) if (i&1) (x*=q)%=n;
    if (x-1!=0 and x+1!=n){
      for (ll i=s-1; i--;)
        if (1==((x*=x)%=n) or x+1==n) break;
      if (x+1!=n) return false;
    }
  }
  return true;
}

int phi(int n) {
  int res = n;
  for (int i=2; i*i <= n; ++i)
    if (n%i == 0)
      for (res -= res/i; n%i == 0; n /= i);
  if (n>1) res -= res/n;
  return res;
}

struct egcd {
  int x, y, z;

  egcd(int const a, int const b): x(1), y(0), z(a){
    if (not b) return;
    *this = egcd(b, a%b);
    x -= y * (a/b);
    swap(x, y);
  }
};

void mod_inverses(int p,int *inv){
  for (int i=(inv[1]=1)+1; i<p; ++i) inv[i]=(p-(p/i)*inv[p%i]%p)%p;
}

/*  egcd a(144,60);
    printf("%d\n",egcd(144,60).z);
    printf("%d %d %d\n",a.x,a.y,a.z);
*/
