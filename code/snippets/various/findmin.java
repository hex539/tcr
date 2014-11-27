import java.util.*;
import java.io.*;

public class Main {
  static int[][] queries;
  static int arrayLength;
  static int numQueries;
  static int[] arr;
  static Node tree = null;

  public static void main(String[] args) throws IOException{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    String[] lineOne = br.readLine().split(" ");
    arrayLength = Integer.parseInt(lineOne[0]);
    numQueries = Integer.parseInt(lineOne[1]);

    String[] lineTwo = br.readLine().split(" ");

    arr = new int[arrayLength];
    for (int i = 0; i < arrayLength; i++){
      arr[i] = Integer.parseInt(lineTwo[i]);
    }

    //build a tree from the array
    tree = buildTree(arr);

    // process these in realtime
    for (int i = 0; i < numQueries; i++){

      String[] query = br.readLine().split(" ");

      int low = Integer.parseInt(query[0]);
      int high = Integer.parseInt(query[1]);

      System.out.println(rangeMinimumQuery(tree, low, high));
    }
  }

  public static Node buildTree(int[] arr){
    LinkedList<Node> queueOne = new LinkedList<Node>();
    LinkedList<Node> queueTwo = new LinkedList<Node>();
    LinkedList<Node> temp;

    for (int i = 0; i < arr.length; i++){
      Node tempNode = new Node(arr[i], i, i);
      queueOne.add(tempNode);
    }

    while (queueOne.size() > 1){
      while (queueOne.size() > 0){
        if (queueOne.size() == 1){
          queueTwo.add(queueOne.poll());
        }
        else{
          Node tempOne = queueOne.poll();
          Node tempTwo = queueOne.poll();

          int min = tempOne.min < tempTwo.min ? tempOne.min : tempTwo.min;

          Node parent = new Node(min, tempOne.lowIx, tempTwo.highIx, tempOne, tempTwo);

          queueTwo.add(parent);
        }
      }

      temp = queueOne;
      queueOne = queueTwo;
      queueTwo = temp;
    }

    return queueOne.poll();
  }

  public static int rangeMinimumQuery(Node parent, int startIx, int endIx){
    //DFS down possible paths, only if they are better than the already given best
    if (parent == null){
      return Integer.MAX_VALUE;
    }
    else if ((parent.lowIx >= startIx && parent.highIx <= endIx)){
      //if the range of the current node is fully contained within it

      //return min of range

      return parent.min;
    }
    else if (rangeOverlap(parent, startIx, endIx)){
      //if the range overlaps the total range

      Node left = parent.leftChild;
      Node right = parent.rightChild;

      return (Math.min(rangeMinimumQuery(left, startIx, endIx), rangeMinimumQuery(right, startIx, endIx)));
    }
    else{
      return Integer.MAX_VALUE;
    }
  }

  public static boolean rangeOverlap(Node node, int lowIx, int highIx){
    return (node.lowIx <= highIx && node.highIx >= lowIx) || (node.highIx >= lowIx && node.lowIx <= highIx);
  }

  private static class Node{
    int min;
    int lowIx;
    int highIx;
    Node leftChild = null;
    Node rightChild = null;

    public Node(int min, int lowIx, int highIx, Node leftChild, Node rightChild){
      this.min = min;
      this.lowIx = lowIx;
      this.highIx = highIx;
      this.leftChild = leftChild;
      this.rightChild = rightChild;
    }

    public Node(int min, int lowIx, int highIx){
      this.min = min;
      this.lowIx = lowIx;
      this.highIx = highIx;
    }

    public String toString(){
      return Integer.toString(min);
    }
  }
}
