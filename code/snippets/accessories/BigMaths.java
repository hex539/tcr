import java.lang.*;
import java.util.*;
import java.math.*;
import java.io.*;

public class BigMaths extends In {
  public static void main(String[] args) throws Exception {
    // Random rand = new Random();
    // System.out.println(rand.nextInt());
    BigInteger[][] dp = new BigInteger[10001][2];

    dp[0][0] = BigInteger.ONE;
    dp[0][1] = BigInteger.ZERO;

    for (int i = 0; i < 10000; i++) {
      dp[i+1][0] = dp[i][0].add(dp[i][1]);
      dp[i+1][1] = dp[i][0];
    }

    while (stdin.hasMoreTokens()) {
      int n = nextInt();
      BigInteger res = dp[n-2][0].add(dp[n][0]);
      System.out.println(res);
    }
  }
}

// Fast input class!
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
