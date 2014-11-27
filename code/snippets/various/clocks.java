import java.util.*;
import java.io.*;

public class Main {;

  static int numHands;
  static int[] clockOne;
  static int[] clockTwo;
  static int numDegrees = 360000;

  //data for RK
  static long primeMod = 10000007; 
  static long base = 23; 
  static long power;

  public static void main(String[] args) throws IOException{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    numHands = Integer.parseInt(br.readLine());

    //read in the clock data using the utility method
    clockOne = readClock(br, numHands);
    clockTwo = readClock(br, numHands);

    //normalize to relative angles
    clockOne = makeRelative(clockOne);
    clockTwo = makeRelative(clockTwo);

    //maximum power of the base mod primeMod
    power = iPow(base, numHands - 1);
    boolean match = false;
    long clockOneHash = 0;

    //generate the hash for the first clock by treating them as characters and using standard RK
    for (int i = 0; i < numHands; i++){
      clockOneHash = (clockOneHash * base) % primeMod;
      clockOneHash = (clockOneHash + clockOne[i]) % primeMod;
    }

    //roll the hash across two, wrapping when end is reached (as lengths are the same)
    long clockTwoHash = 0;

    //make it work for simple case where clocks are same first
    for (int i = 0; i < numHands * 2; i++){
      //ensure the base multiplication
      clockTwoHash = (clockTwoHash * base) % primeMod;
      //add the new character
      clockTwoHash = (clockTwoHash + clockTwo[i % numHands]) % primeMod;

      if (i >= numHands - 1){
        if (clockOneHash == clockTwoHash){
          match = true;
          break;
        }

        //remove the item about to become irrelevant
        clockTwoHash = ((clockTwoHash - (clockTwo[(i + 1) % numHands]) * power) % primeMod + primeMod) % primeMod;
      }
    }

    //print the result

    String toPrint = match ? "possible" : "impossible";
    System.out.println(toPrint);
  }

  private static int[] readClock(final BufferedReader br, final int n) throws IOException{
    int[] ret = new int[n];
    String str = br.readLine() + " ";
    for (int i = 0, j = 0; i < n; ++i){
      while (str.charAt(j) == ' '){
        ++j;
      }
      while (str.charAt(j) != ' '){
        ret[i] = (ret[i] * 10) + (str.charAt(j) - '0');

        ++j;
      }
    }
    Arrays.sort(ret);
    return ret;
  }

  private static int[] makeRelative(int[] clock){
    int[] toReturn = new int[clock.length];
    for (int i = 0; i < clock.length; i++){
      toReturn[i] = i==0 ? (clock[i] - clock[clock.length-1] + numDegrees) % numDegrees : (clock[i] - clock[i-1]);
    }
    return toReturn;
  }

  private static long iPow(long base, long exp){
    long toRet = 1;
    if (exp == 0) return 1;
    return (((exp & 1) == 1 ? base : 1) * iPow((base * base) % primeMod, exp/2)) % primeMod;
  }

  private static String clockToString(int[] clock){
    StringBuilder sb = new StringBuilder();
    for (int item: clock){
      sb.append(Integer.toString(item));
    }
    return sb.toString();
  }

}
