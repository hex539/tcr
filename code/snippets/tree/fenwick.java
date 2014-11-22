class FenwickTree {
  final int[] mV;

  // construct with capacity of n
  FenwickTree(int n) {
    mV = new int[n];
  }

  // update value x by adding y to it
  public void addTo(int x,int y) {
    while (x < mV.length) {
      mV[x] += y;
      x |= x+1;
    }
  }

  // sum of values from [0..x]
  public int getSum(int x) {
    return x >= 0 ? mV[x] + getSum((x & (x-1)) - 1) : 0;
  }

  // sum of values from [a..b]
  public int getValue(int a, int b) {
    return getSum(b) - getSum(a-1);
  }
}
