#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;

template <class X> struct Set{
  template <class C> struct V{
    int height, size;
    V *c[2];
    C key;

    V(C const k):height(1),size(1),key(k) {c[0]=c[1]=0;}
    ~V(){delete c[0]; delete c[1];}

    void calc(){
      for (int i = 1 + (height = size = 1); i--;) if (c[i])
        height = max(height, 1 + c[i]->height),
        size += c[i]->size;
    }

    void rotate(V *&p,int i){
      p=c[i];
      c[i]=p->c[!i];
      p->c[!i]=this;
      calc(); p->calc();
    }

    void adjust(V *&p){
      int i = (calc(), not c[0] or c[1] and c[0]->height < c[1]->height);
      if (not c[i] or c[i]->height <= (c[!i]? c[!i]->height + 1: 1)) return;
      if (c[i]->c[!i] and c[i]->c[!i]->height == height - 2) c[i]->rotate(c[i],!i);
      return rotate(p,i);
    }

    void insert(C const k,V *&p){
      if ((k<key) == (key<k)) return;
      bool d=(key<k);
      if (c[d]) return
        c[d]->insert(k,c[d]),
        c[d]->adjust(c[d]);
      c[d]=new V(k);
    }

    void erase(C k,V *&p){
      if (k<key or key<k) {if (c[key<k]) c[key<k] -> erase(k,c[key<k]);}
      else if (c[0] and c[1]) for (V *v=c[1]; v->c[0] or (key=v->key, c[1]->erase(key,c[1]), not true); v=v->c[0]);
      else return p=c[!*c], c[!*c]=0, delete this;
      adjust(p);
    }

    int index(C k){
      int res=0;
      V* i=this;
      do if (k<i->key) i=i->c[0];
      else if (i->key<k) res+=i->size, i=i->c[1], res-=(i?i->size:0);
      else return res+(i->c[0]?i->c[0]->size:0);
      while (i); return -1;
    }
  };

  V<X>* root;

  Set():root(0){}
  ~Set(){delete root;}
  void insert(X const k){ if (root) root->insert(k,root), root->adjust(root); else root=new V<X>(k); }
  void erase(X const k){  if (root) root->erase(k,root); if (root) root->adjust(root); }
  int count(X const k){   return root? root->index(k)!=-1: 0; }
  int index(X const k){   return root? root->index(k): -1; }
  int size(){             return root? root->size: 0; }
};

int main(){
  Set<int> s;
  for (long long a=4234324, b=23424, c=2344646, i=1000000; i--;)
    { if (i&1) s.insert(c); else s.erase(c); c=((a*561)^(b*3367))%(1<<24), swap(a,c); }
  for (int i=0; i<(1<<24); i++) if (s.count(i)) printf("%d\n",i);
}
