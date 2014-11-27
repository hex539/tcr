import java.util.*;
import java.io.*;

public class Main{

  public static void main(String[] args) throws IOException{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    int numNums = Integer.parseInt(br.readLine());

    String[] lineTwo = br.readLine().split(" ");

    Integer[] numbers = makeInts(lineTwo);
    TreeSet<Integer> numberSet = new TreeSet<Integer>(Arrays.asList(numbers));
    numberSet.add(0);

    int max = 0;

    for (int num: numbers){ //loop through numbers

      for (int div=1; num*div<=200000; div++){ //for some large divisor

        int mod = (numberSet.lower(num*(div+1))) % num;
        if (numberSet.contains(num*div+mod)) {
          max = mod > max ? mod : max;
        }
      }
    }

    System.out.println(max);

  }

  static Integer[] makeInts(String[] str){
    Integer[] ret = new Integer[str.length];

    for (int i = 0; i < str.length; i++){
      ret[i] = Integer.parseInt(str[i]);
    }

    return ret;
  }

}
