import static java.lang.Math.*;

class Interval implements Comparable<Interval> {
  public int start, end;

  public Interval(int s,int e) {
    start = s;
    end = e;
  }

  int size() {
    return end - start;
  }

  Interval intersected(Interval other) {
    return new Interval(
      max(start, other.start),
      max(end, other.end)
    );
  }

  Interval merged(Interval other) {
    return new Interval(
      min(start, other.start),
      max(end, other.end)
    );
  }

  @Override
  public int compareTo(Interval other) {
    return start != other.start ?
        Integer.valueOf(start).compareTo(other.start)
    :   Integer.valueOf(end).compareTo(other.end);
  }
}

class BS {
  public static int findLower(int[] v, int x) {
    int i = -1;
    for (int r = v.length; r > 0; r /= 2)
      while (i+r < v.length && v[i+r] < x)
        i += r;
    return i + 1;
  }

  public static int findUpper(int[] v, int x) {
    int i = -1;
    for (int r = v.length; r > 0; r /= 2)
      while (i+r < v.length && v[i+r] <= x)
        i += r;
    return i + 1;
  }

  public static Interval findAll(int[] v, int x) {
    return new Interval(findLower(v, x), findUpper(v, x));
  }
}

public class BinarySearch {
  public static void main(String[] args) {
    int[] v = {1,2,3,4,4,4,4,5,6};
    Interval all = BS.findAll(v, 4);
    System.out.println("[" + all.start + ".." + all.end + ") = " + all.size() + " elements equal to 4");
  }
}
