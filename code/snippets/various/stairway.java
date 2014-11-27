import java.util.*;
import java.io.*;

public class Main{

  static int numStridesUp;
  static int numStrideDown;
  static int numStairs = 111;
  static int[] memo;

  public static void main(String[] args) throws IOException{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    numStridesUp = Integer.parseInt(br.readLine());

    String[] lineTwo = br.readLine().split(" ");

    int[] strides = makeInts(lineTwo);

    memo = new int[numStairs+1];

    Arrays.fill(memo, -1);

    memo[0] = 1;

    for (int i = 0; i < memo.length; i++){

      for (int j = 0; j < strides.length; j++){

        if (strides[j] > i){
          continue; //no solution for this

        }
        if (memo[i-strides[j]] != -1){
          if (memo[i] == -1){
            memo[i] = 0;
          }

          memo[i] += memo[i-strides[j]];
          memo[i] %= 10000000;
        }
      }
    }

    memo[memo.length-1] = memo[memo.length-1] == -1 ? 0 : memo[memo.length-1];
    String output = String.format("%07d", memo[memo.length-1]);
    System.out.println(output);
  }

  static int[] makeInts(String[] str){
    int[] ret = new int[str.length];
    for (int i = 0; i < str.length; i++){
      ret[i] = Integer.parseInt(str[i]);
    }
    return ret;
  }
}
