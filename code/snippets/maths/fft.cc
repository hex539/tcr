#include <bits/stdc++.h>
using namespace std;

typedef long double flack;
typedef complex<flack> flex;
typedef vector<int> vi;

void fft(flex *v,int n,int s=1){ // n is a power of 2
  static flex tmp[1<<16];
  if (n<=1) return;
  fft(v+0,n/2,s*2);
  fft(v+s,n/2,s*2);

  for (int i=0,j=0,k=n/2; i<n; i+=2,j++,k++)
    tmp[j]=v[(i+0)*s],
    tmp[k]=v[(i+1)*s];

  for (int i=n/2,j=n; --j,i--;)
    v[i*s]=tmp[i]+exp(flex(0,-i*2*M_PI/n))*tmp[j],
    v[j*s]=tmp[i]-exp(flex(0,-i*2*M_PI/n))*tmp[j];
}

vi convolve(vi const &a,vi const &b){
  int p=a.size()+b.size()-1; for (int i=32; i>>=1; p|=p>>i); ++p;

  vector<flex> u(p), v(p);
  copy(a.begin(),a.end(),u.begin());
  copy(b.begin(),b.end(),v.begin());

  fft(&u[0],p);
  fft(&v[0],p);

  for (int i=0; i<p; i++) u[i]=conj(u[i]*v[i]);

  fft(&u[0],p);

  vi res(a.size()+b.size()-1);
  for (int i=res.size(); i--;) res[i]=u[i].real()/p+0.5;
  return res;
}

int main(){
  vi a={1,2,3,4};
  vi b={7,6,5,4};
  vi c=convolve(a,b);

  for (int i=0; i<a.size()+b.size()-1; i++){
    cout<<c[i]<<(i==a.size()+b.size()-2?'\n':' ');
  }

  flex v[8]={0,1,2,3,4,5,6,7};
  fft(v,8);
  for (int i=0; i<8; i++)
    cout<<v[i]<<endl;
}


