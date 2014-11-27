/* class to find where the maximum element is in an array that increases monotonically
   and then decreases monotonically. The increase/decrease has to be strict (A<B<C rather
   than A<=B<=C) for it to work. */

public class TernarySearch {
  static int[] arr = {1,2,3,4,5,6,7,8,5,3,2,1};

  static int getValue(int x) {
    return arr[x];
  }

  // Of course, in practice V should probably be a call to a function
  static int findMax(int l, int r) {
    while (l + 1 < r) {
      int a = (l*2+r) / 3;
      int b = (l+r*2) / 3;
      if (getValue(a) > getValue(b)) r = b; else l = a+1;
    }
    return l;
  }

  public static void main(String[] args) {
    int where = findMax(0, arr.length);
    System.out.println("max element is at position " + where + ": " + getValue(where));
  }
}
