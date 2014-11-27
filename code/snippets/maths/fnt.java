/*
  Fast number-theoretic transform

  performs FFT on a field for integer accuracy - less code & much more
  useful for convolution

  Convolution of two vectors A and B generalises multiplication of
  polynomials. The resulting vector will have V[i] = sum(A[x] * B[i-x]).
  This can be useful in a couple of situations - you'll know them when
  you see them.

  could probably be extended to 64 bits or greater but needs extra stuff
  to avoid overflow. Best to switch to Java and use BigInts. Use a prime
  from the list in the 'Mathematics' section.
*/

class Convolve {
  static long mod(long n, long k) {
    if (n < 0) return mod(k-mod(-n,k),k);
    return n % k;
  }

  static long modPow(long n, long k) {
    long r = (k % 2 == 1 ? n : 1);
    if (k > 0) r *= modPow((n * n) % FIELD, k/2);
    return r % FIELD;
  }

  static final long tmp[] = new long[4096]; // increase as necessary
  static final long FIELD = 5l * (1l<<25l) + 1; // needs to be a prime equal to 1 (mod tmp.length)
  static final long BASE = modPow(3l, (FIELD-1) / tmp.length);

  // v.length should equal tmp.length (so adjust it as necessary)
  static void numericTransform(long[] v, int n, int o, int dirn, int s) {
    if (n < 2) return;
    long p = modPow(BASE, tmp.length);
    long z = modPow(BASE, mod(s*dirn, FIELD-1));

    numericTransform(v,n/2,o+0,dirn,s*2);
    numericTransform(v,n/2,o+s,dirn,s*2);
    for (int i=0,j=n/2; j<n; ++i,++j) {
      tmp[i]=v[o+(i*2+0)*s];
      tmp[j]=v[o+(i*2+1)*s];
    }
    for (int i=0,j=n/2; j<n; ++i,++j) {
      v[o+i*s]=mod(tmp[i] + tmp[j] * p, FIELD);
      v[o+j*s]=mod(tmp[i] - tmp[j] * p, FIELD);
      p = (p * z) % FIELD;
    }
  }

  // a = a * b
  public static void convolve(long[] a, long[] b) {
    if (a == a) numericTransform(a,a.length,0,+1,1);
    if (a != b) numericTransform(b,b.length,0,+1,1);
    for (int i=a.length; i-->0;) a[i]=mod(a[i]*b[i], FIELD);
    if (a == a) numericTransform(a,a.length,0,-1,1);
    if (a != b) numericTransform(b,b.length,0,-1,1);
    for (int i=a.length; i-->0;) a[i]=mod(a[i]*modPow(tmp.length, FIELD-2), FIELD);
  }
}

public class fnt {
  public static void main(String[] args){
    long u[] = new long[4096]; System.arraycopy(new long[]{1,2,3,4}, 0, u, 0, 4);
    long v[] = new long[4096]; System.arraycopy(new long[]{1,2,4,9}, 0, v, 0, 4);
    Convolve.convolve(u, v);
    for (int i=0; i<8; i++)
      System.out.println(u[i]);
  }
}
