// <algorithm>

struct LinkCut{
  bool rev;
  LinkCut *p,*l,*r;
  LinkCut(LinkCut* p=0): p(p), l(0), r(0) {rev=false;}

  bool root() {return not p or p->l != this and p->r != this;}

  void push() {
    if (rev) {
      if (l) l->rev^=1;
      if (r) r->rev^=1;
      swap(l,r);
      rev=0;
    }
  }

  void rot(LinkCut* LinkCut::*a,LinkCut* LinkCut::*b) {
    if (not root()) (p->l==this?p->l:p->r)=(this->*a);
    (this->*a)->p=p, p=(this->*a);
    (this->*a)=(p->*b), (p->*b)=this;
    if (this->*a) (this->*a)->p=this;
  }

  void rotate() {
    if (p->l==this) p->rot(&LinkCut::l,&LinkCut::r);
    else            p->rot(&LinkCut::r,&LinkCut::l);
  }

  void splay() {
    while (not root()) {
      if (not p->root()) p->p->push(); p->push(); push();
      if (not p->root()) ((p->l==this)==(p->p->l==p)? p:this)->rotate();
      rotate();
    }
    push();
  }

  void reverse() {
    splay(); rev^=1; push();
  }

  void link(LinkCut* x) {
    splay(); x->splay(); p=x; p->l=this; splay();
  }

  void cut() {
    splay(); if (r) r->p=p; p=r=0;
  }

  void expose() {
    for (LinkCut* i=this,*j=0; i; j=i,i=i->p) {
      i->splay();
      i->l=j;
    }
    splay();
  }

  void evert() {
    expose();
    push();
    if (r) r->reverse(), r=0;
  }

  LinkCut* findroot() {
    expose();
    LinkCut* x=this;
    while (x->r) x=x->r, x->push();
    return x;
  }

  LinkCut* lca(LinkCut* x) {
    if (findroot() != x->findroot()) return 0;
    if (x == this) return x;
    expose(), x->expose(), splay(); if (x->p) return this;
    expose(), x->splay(); return p? x: x->p;
  }
};
