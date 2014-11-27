import java.io.*;
import java.util.*;

public class FastInput extends In{
  public static void main(String[] args) {
    int a = nextInt();
    int b = nextInt();
    System.out.println(a + b);
  }
}

class In {
  static BufferedReader mBr = new BufferedReader(new InputStreamReader(System.in));
  static String[] mTok = {};
  static int mI = 0;

  static String nextLine() {
    mI = mTok.length;
    try {return mBr.readLine();}
    catch (Throwable e) {return null;}
  }

  static String nextString() {
    for (;;) {
      if (mI == mTok.length) {
        mTok = nextLine().split(" ");
        mI = 0;
      } else if (mTok[mI].length() == 0) {
        mI++;
      } else {
        return mTok[mI++];
      }
    }
  }

  static int nextInt() {
    return Integer.parseInt(nextString());
  }

  static double nextDouble() {
    return Double.parseDouble(nextString());
  }
}
