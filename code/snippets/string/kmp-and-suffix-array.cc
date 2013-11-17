typedef long long ll; typedef pair<int,int> pi;
// KMP - use Aho-Corasick for multi-matchings
void build_table(int* f,char const* s){
  for (int i=(f[0]=f[1]=1,1); s[i-1]; i++){
    while ( f[i] and s[f[i]]!=s[i-1]) f[i]=f[f[i]];
    if (i>1+f[i] and s[f[i]]==s[i-1]) f[i]++;
    f[i+1]=f[i]; } }
int count_strings(int* f,char const* s,char const* h){
  int r=0;
  for (int i=0,j=0; h[i]; i++){
    while (j and s[j]!=h[i]) j=f[j];
    if (s[j]==h[i]) ++j;
    if (s[j]=='\0') ++r;
  } return r; }
int f[1000]; char s[1000]="aba", h[1000]="abagabababba";
int main() {build_table(f,s); printf("%d\n",count_strings(f,s,h));}

// And now for some suffix array stuff
void sa_sort(int *a,int *b,int *r,int n,int k) {
  static int c[1100000]; memset(c,0,sizeof(int)*++k);
  for (int i=n; i--;) ++c[r[a[i]]];
  for (int i=0,j=0; i<k; i++) swap(j,c[i]+=j);
  for (int i=0,j=0; i<n; i++) b[c[r[a[i]]]++]=a[i]; }

void sa_rec(int *s,int *arr,int n,int k=27) {
  int n0=(n+2)/3, n1=(n+1)/3, n2=(n+0)/3, n02=n0+n2;
  int *s12 = new int[2*n+12], *s0 = s12 + (n02+3); s12[n02+0] = s12[n02+1] = s12[n02+2] = 0;
  int *a12 = s0+n0,           *a0 = a12 + (n02+3); a12[n02+0] = a12[n02+1] = a12[n02+2] = 0;
  for (int i=1,j=0; i+n1<n+n0; i+=(i%3)) s12[j++]=i;
  for (int i=3; i--;) sa_sort(i&1?a12:s12,i&1?s12:a12,s+i,n02,k);

  int names=0,c[3]={-1,-1,-1};
  for (int i=0; i<n02; i++) {
    if ((s[a12[i]]!=c[0] or s[a12[i]+1]!=c[1] or s[a12[i]+2]!=c[2]) &&++names)for(int j=3; j--;)c[j]=s[a12[i]+j];
    s12[a12[i]/3 + (a12[i]%3==1?0:n0) ]=names;
  }
  if (n02<=names)  for (int i=0; i<n02; i++) a12[s12[i]-1]=i; else {
    sa_rec(s12,a12,n02,names);
    for (int i=0; i<n02; i++) s12[a12[i]]=i+1;
  }
  for (int i=0,j=0; i<n02; i++) if (a12[i]<n0) s0[j++]=3*a12[i];

  sa_sort(s0,a0,s,n0,k);
  for (int i=0,j=n0-n1,k=0; k<n; k++){
    int u=(a12[j]<n0? a12[j]*3+1: (a12[j]-n0)*3+2), v=a0[i];
    if (s[u]<s[v] or s[u]==s[v] and (a12[j]<n0? s12[a12[j]+n0]<=s12[v/3]
                                    : s[u+1]<s[v+1] or s[u+1]==s[v+1] and s12[a12[j]-n0+1]<=s12[v/3+n0])){
      arr[k]=u;
      if (n02==++j) for (k++; i<n0; i++,k++) arr[k]=a0[i];
    }else{
      arr[k]=v;
      if (n0==++i) for (k++; j<n02; j++,k++) arr[k]=(a12[j]<n0? a12[j]*3+1: (a12[j]-n0)*3+2);
  } } delete[] s12; }

void suffix_array(char *s, int n, int *arr, int *lcp=0) {
  int *inv=new int[n+3]();
  for (int i=n; i--;) inv[i]=s[i];
  sa_rec(inv,arr,n,256);
  for (int i=n; i--;) inv[arr[i]]=i;
  if (lcp){
    for(int i=0,h=lcp[0]=0; i<n; ++i) if (inv[i]){
      for (int j=arr[inv[i]-1]; s[i+h]==s[j+h]; ++h);
      lcp[inv[i]]=h, h-=!!h;
    }
  } delete []inv; }

int suffix_upper_bound(char const* needle, char const *str, int const *arr, int n){ int l,r,m;
  for (l=0,r=1<<(33-__builtin_clz(n)); m=l+r/2,r; r/=2) if (m<=n and strcmp(needle,str+arr[m-1])>0) l=m;
  return l; }

int main(){
  char const *str="flowerpower";
  int arr[100], lcp[100], n=strlen(str);
  suffix_array(str,n,arr,lcp);
  for (int i=0; i<n; i++) printf("%02d| (%-2d = %2d) %s\n",i+1,arr[i],lcp[i],str+arr[i]);
  printf("'lower' <= %d\n", suffix_upper_bound("lower", str, arr, n)); }
