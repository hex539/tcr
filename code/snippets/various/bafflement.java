import java.util.Scanner;

public class Main
{
  public static void main(String[] args)
  {
    Scanner in = new Scanner(System.in);
    String line = in.nextLine();

    String[] vals = line.split("\\s+");
    int size = Integer.valueOf(vals[0]);
    System.out.println(generateFibonnaci(size+2));  
  }
  
  static long generateFibonnaci(int max)
  {
    long[] array = new long[max];
    array[0] = 0;
    array[1] = 1;
    
    for (int n = 2; n < max; n++)
    {
      array[n] = array[n-1] + array[n-2];
    }
    long val = array[max-3] + array[max-1];
    return val;
  }  
}
