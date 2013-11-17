// <climits> <cstdio>

/**
  SegTree<Width> // where Width is a power of two
  ------------

  Used for updating a contiguous range of numbers
  to contain the same number and also to query the
  sum of numbers in a contiguous range.

  Some simple modifications: use more than one dimension (quadtree, octree), change the operator from (=x)
  A node can store anything, not just a sum: (minima, GCDs, products, n-D intervals with seg[l] = r)
**/

template <int Width>
struct SegTree {
  int val[Width*2];
  int psh[Width];

  SegTree(void) {
    for (int i=Width*2; i--;) val[i]=0;
    for (int i=Width  ; i--;) psh[i]=INT_MIN;
  }

  void simplify(int i) {
    if (i+1 < Width and psh[i] != INT_MIN) {
      val[i*2+1] = psh[i] / 2;
      val[i*2+2] = psh[i] / 2;
      if (i*2+2<Width) {
        psh[i*2+1] = psh[i] / 2;
        psh[i*2+2] = psh[i] / 2;
      }
      psh[i] = INT_MIN;
    }
  }

  void update(int a,int b,int d, int i=0,int l=0,int r=Width) {
    simplify(i);
    if (a<r and b>l) {
      if (a<=l and b>=r) {
        val[i] = d * (r-l); if (i+1 < Width)
        psh[i] = d * (r-l);
      } else {
        int m = (l+r)/2;
        if (a<m) update(a,b,d, i*2+1, l,m);
        if (b>m) update(a,b,d, i*2+2, m,r);
        val[i] = val[i*2+1] + val[i*2+2];
      }
    }
  }

  int query(int a,int b, int i=0,int l=0,int r=Width) {
    simplify(i);
    if (a<r and b>l) {
      if (a<=l and b>=r) {
        return val[i];
      } else {
        int m = (l+r)/2;
        return query(a,b, i*2+1, l,m) + query(a,b, i*2+2, m,r);
      }
    } else
      return 0;
  }
};

/**
Example usage
**/

int main(){
  SegTree<1024> seg;

  seg.update(0,16, 10); // set values from 0 to 15 inclusive to be 10
  seg.query(0,16); // 160
  seg.query(1,15); // 140
}
