#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
  Fast number-theoretic transform

  performs FFT on a field for integer accuracy less code & much more
  useful for convolution

  could probably be extended to 64 bits or greater but needs extra stuff
  to avoid overflow. Best to switch to Java and use BigInts. Use a prime
  from the list later on
*/

ll const field = 5ll * (1ll<<25ll) + 1; // needs to be prime
ll mow(ll n,ll k){return k? ((k&1? n:1) * mow((n*n)%field,k/2))%field: 1;}
ll const maxn  = 4096;
ll const base  = mow(3ll, (field-1) / maxn);

void fnt(ll *v,ll n,ll dirn=+1,ll s=1){
  if (n<2) return;

  fnt(v+0,n/2,dirn,s*2);
  fnt(v+s,n/2,dirn,s*2);

  static ll tmp[maxn];
  for (int i=0,j=n/2; j<n; ++i,++j){
    tmp[i]=v[i*2*s+0];
    tmp[j]=v[i*2*s+s];
  }

  for (int i=0,j=n/2; j<n; ++i,++j){
    v[i*s]=(tmp[i]+field+((tmp[j]*mow(base,maxn+i*s*dirn)%field)))%field;
    v[j*s]=(tmp[i]+field-((tmp[j]*mow(base,maxn+i*s*dirn)%field)))%field;
  }
}

void convolve(ll *a,ll *b,ll n){
  if (true) fnt(a,n,+1);
  if (a!=b) fnt(b,n,+1);
  for (int i=n; i--;) (a[i]*=b[i])%=field;
  fnt(a,n,-1);
  for (int i=n; i--;) (a[i]*=mow(maxn,field-2))%=field;
}

int main(){
  static ll u[4096]={1,2,3,4};
  static ll v[4096]={1,2,4,9};
  convolve(u,u,maxn);
  for (int i=0; i<10; i++)
    cout<<u[i]<<" ";
  cout<<endl;
}
