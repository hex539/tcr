import java.util.*;

class Item implements Comparable<Item> {
  int iKey;
  String sKey;
  int iValue;

  // Which field should we use for compareTo during a sort?
  public static int compareBy = 0;

  @Override
  public int compareTo(Item other) {
    switch (compareBy) {
      case 0: return new Integer(iKey).compareTo(other.iKey);
      case 1: return sKey.compareTo(other.sKey);
      default: return 0;
    }
  }
}

// Example: read in N distinct strings. For each one print how many it is greater than.
public class SchwartzSort{
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);

    int n = in.nextInt();
    Item[] items = new Item[n];
    for (int i = 0; i < n; i++) {
      items[i] = new Item();
      items[i].iKey = i;
      items[i].sKey = in.next();
    }

    Item.compareBy = 1;
    Arrays.sort(items);
    for (int i = 0; i < n; i++) {
      items[i].iValue = i;
    }
    Item.compareBy = 0;
    Arrays.sort(items);

    StringBuilder sb = new StringBuilder();
    for (int i = 0; i < n; i++) {
      if (i > 0) sb.append(' ');
      sb.append(items[i].iValue);
    }
    System.out.println(sb);
  }
}
