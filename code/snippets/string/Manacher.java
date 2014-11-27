// Finds all palindromes

import static java.lang.Math.*;

public class Manacher {
  static int[] findPalindromes(char[] s) {
    int[] span = new int[s.length*2-1];

    int r = 0;
    for (int i = 1; i < span.length; i++) {
      if (i <= r + span[r]) span[i] = min(span[r*2 - i], r + span[r]);
      while (i/2-span[i]>=0 && (i+1)/2+span[i]<s.length && s[i/2-span[i]] == s[(i+1)/2+span[i]]) ++span[i];
      --span[i];
      if (i+span[i] > r+span[r]) r = i;
    }
    return span;
  }

  public static void main(String[] args) {
    String s = "palla ala racecar";
    int[] pals = findPalindromes(s.toCharArray());
    for (int i = 0; i < pals.length; i++)
      if (pals[i] > 0)
        System.out.println("'" + s.substring(i/2-pals[i], (i+1)/2+pals[i]+1) + "'");
  }
}
