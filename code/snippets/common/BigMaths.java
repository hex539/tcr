import java.lang.*;
import java.util.*;
import java.math.*;
import java.io.*;

public class BigMaths {

  // Utility function to return a StringTokenizer for all
  // of the input data
  //
  // if input is line-by-line then 'return new Scanner(read)'
  // might be better
  //
  private static StringTokenizer slurpStdin() throws IOException {
    BufferedReader read = new BufferedReader(new InputStreamReader(System.in));
    StringBuilder res = new StringBuilder();
    for (String s; (s = read.readLine()) != null;) res.append(s + "\n");
    return new StringTokenizer(res.toString());
  }

  public static void main(String[] args) throws Exception {
    StringTokenizer stdin = slurpStdin();

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
      int n = Integer.parseInt(stdin.nextToken());

      BigInteger res = dp[n-2][0].add(dp[n][0]);
      System.out.println(res);
    }
  }
}
