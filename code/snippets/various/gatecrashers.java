import java.util.*; import java.io.*;

public class Main {
  static int numGuests;
  static int incidents;
  static int[][] matrix;

  public static void main(String[] args) throws IOException{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    String[] lineOne = br.readLine().split(" ");
    numGuests = Integer.parseInt(lineOne[0]);
    incidents = Integer.parseInt(lineOne[1]);

    //create the matrix 
    matrix = new int[numGuests*2][numGuests*2];

    //use two sets of cells to represent meeting vs missing
    for (int i = 0; i < incidents; i++){
      String[] line = br.readLine().split(" ");
      int personA = Integer.parseInt(line[0]);
      int personB = Integer.parseInt(line[2]);

      //ensure all assignments are symmetrical as a met b -> b met a
      if (line[1].equals("met")){
        //at the same party at some point so we mark their met boxes
        matrix[2*personA][2*personB] = 1;
        matrix[2*personB][2*personA] = 1;
        matrix[2*personA + 1][2*personB + 1] = 1;
        matrix[2*personB + 1][2*personA + 1] = 1;
      }
      else if (line[1].equals("missed")){
        //must have never been at the same party so we mark their not met boxes
        matrix[2*personA][2*personB + 1] = 1;
        matrix[2*personB][2*personA + 1] = 1;
        matrix[2*personA + 1][2*personB] = 1;
        matrix[2*personB + 1][2*personA] = 1;
      }
    }
    System.out.println(floydWarshall(matrix));
  }

  public static String floydWarshall(int[][] matrix){
    //perform floyd warshall to find the shortest 'path' between two people 
    for (int k = 0; k < matrix.length; k++){
      for (int i = 0; i < matrix.length; i++){
        for (int j = 0; j < matrix.length; j++){
          //increase the path where possible
          if (matrix[j][k] == 1 && matrix[k][i] == 1){
            matrix[j][i] = 1;
          }
        }
      }
    }
    //loop across the actual array section
    for (int i = 0; i < matrix.length/2; i++){
      //if someone has met and missed the same person the matrix is inconsistent and hence someone has to have gatecrashed
      if ((matrix[i*2+0][i*2+1]==1 && matrix[i*2+0][i*2+0] == 1) || (matrix[i*2+0][i*2+1]==0 && matrix[i*2+0][i*2+0] == 0)){
        return "impossible";
      }
    }
    return "possible";
  }
}
