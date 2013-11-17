// <algorithm> <cstdio> <deque> {typedef long long ll}
ll w[200000];
ll dp[20][200000];

struct equation_t{
  ll plus, grad; // both decreasing
  equation_t *next, *prev; // circular linked list

  equation_t(ll a,ll b): plus(a), grad(b) {next=prev=this;}
  template<class C> C eval(C x) {return plus+grad*x;}
};

void add(equation_t*& to,equation_t* const with){
  if (not to) to=with;
  equation_t* end=to->prev;
  end->next=with; with->prev=end;
  to ->prev=with; with->next=to ;
}

void pop(equation_t*& to){
  if (not to or to->prev==to){
    delete to;
    to=0;
  }else{
    equation_t *beg=to->next, *end=to->prev;
    delete to;
    to=beg;
    beg->prev=end;
    end->next=beg;
  }
}

int main(){
  ll naive=0;
  int n,k; scanf("%d %d",&n,&k);
  for (int i=0; i<n; i++) scanf("%lld",w+i), naive+=w[i]*i;
  for (int i=n; i--;) w[i]+=w[i+1];
  for (int i=k+1; i--;) for (int j=n+1; j--;) dp[i][j]=-(1ll<<50ll);
  dp[0][0]=0;

/*
  (i=1..k-1) (j=0..n-1) (u=0..j-1) dp[i][j]=max(dp[i][j],dp[i-1][u]+(j-u)*w[j]);
  ==
  (i=0..k-2) (j=0..n-1) (u=j..n-1) dp[i+1][u]=max(dp[i+1][u],dp[i][j]-j*w[u]+u*w[u]);
  ==
*/

  equation_t *eq=0;
  for (int i=0; i+1<k; i++){
    for (int j=0; j<n; j++){
      if (dp[i][j]!=(-1ll<<50ll)){
        add(eq,new equation_t(dp[i][j],-j));
        while (eq->prev->prev!=eq){
          equation_t *c=eq->prev, *b=c->prev, *a=b->prev;

          if ( (b->plus-a->plus)*(a->grad-c->grad) >= (c->plus-a->plus)*(a->grad-b->grad)
           and (c->plus-b->plus)*(a->grad-c->grad) <= (c->plus-a->plus)*(b->grad-c->grad))
            break;
          delete b;
          a->next=c, c->prev=a;
        }
      }
      while (eq and eq->next!=eq)
        if (eq->next->eval(w[j+1])>eq->eval(w[j+1]))
          pop(eq);
        else
          break;
      if (eq)
        dp[i+1][j+1]=eq->plus+(j+1+eq->grad)*w[j+1];
    }
    while (eq) pop(eq);
  }

  ll best=0;
  for (int i=n; i--;) best=max(best,dp[k-1][i]);
  printf("%lld\n",naive-best);
}


