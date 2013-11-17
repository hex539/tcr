// <algorithm> <climits> <cstdio>

/**
  Fenwick<Width,[Deg=1]>

  Generalised Fenwick tree

     /\    =    /----------
    /  \   =   /
   / + .\  =  /
  /  + ..\ = /
  The above is a graph of the cumulative area for a range insertion.

  Simple usage:
    - insert(x_pos, 1) to insert an event
    - insert(x_pos,-1) to erase an event
    - eval(x0,x1) to count events within a half-open [range)
**/

template <int Width,int Deg>
struct Fenwick {
  int fen[Width][Deg];

  Fenwick() {
    for (int i=Width; i--;)
      for (int j=Deg; j--;)
        fen[i][j] = 0;
  }

  void insert(int x, int y_x0 = 1, int y_x1 = 0, int y_x2 = 0) {
    int const y_xn[] = {
      y_x0,
      y_x1,
      y_x2
    };
    for (int i=x; i<Width; i|=i+1)
      for (int j=0; j<Deg; j++)
        fen[i][j] += y_xn[j];
  }

  int eval(int x0,int x1=INT_MIN) {
    if (x1 != INT_MIN)
      return eval(x1) - eval(x0-1);
    else {
      int res = 0;
      for (int i=x0; i>=0; --(i&=i+1))
        for (int j=Deg; j--;)
          res += fen[i][j] * pow(x0,j);
      return res;
    }
  }
};

int main(){
  Fenwick<1024,3> solver;
  solver.insert(1, 1,0,0); // insert a constant function f(x) = 1    (where x>=1) 0 otherwise
  solver.insert(0, 0,2,0); // insert a linear function f(x) = 2*x    (where x>=0) 0 otherwise
  solver.insert(5, 0,0,1); // insert a quadractic funcion f(x) = x^2 (where x>=5) 0 otherwise

  // evaluate for x = 10
  // y = 1 + 10*2 + 10^2 = 121
  printf("%d\n",solver.eval(10));

  // evaluate for x = 3
  // only the first two terms are evaluated as x<5
  // y = 1 + 3*2 = 7
  printf("%d\n",solver.eval(3));
}
