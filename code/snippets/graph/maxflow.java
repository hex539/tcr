import java.util.*;
import static java.lang.Math.*; // bring in globals like min,max,round

/*
 * Dinic's algorithm - O(V^2 E) complexity
 */

class MaxFlow {
  static class Vertex {
    Map<Vertex,Integer> mEdges = new HashMap<>();
    int mId;

    public Vertex(int id) {
      mId = id;
    }

    @Override
    public int hashCode() {
      return mId;
    }

    @Override
    public boolean equals(Object a) {
      return mId == ((Vertex) a).mId;
    }
  }

  List<Vertex> mVerts;

  public MaxFlow(int n) {
    mVerts = new ArrayList<>(n);
    for (int i = 0; i < n; i++) mVerts.add(new Vertex(i));
  }

  public void addEdge(int a,int b,int c) {
    addEdge(mVerts.get(a),mVerts.get(b),c);
  }

  public int getFlow(int s,int t) {
    return getFlow(mVerts.get(s),mVerts.get(t));
  }

  void addEdge(Vertex a,Vertex b,int c) {
    Integer ab = (a.mEdges.containsKey(b) ? a.mEdges.get(b) : 0);
    if (ab + c != 0) {
      a.mEdges.put(b,   ab + c);
    } else {
      a.mEdges.remove(b);
    }
  }

  void upEdge(Vertex a,Vertex b,int c) {
    addEdge(a,b,+c);
    addEdge(b,a,-c);
  }

  int dfs(Vertex s,Vertex t,Map<Vertex,Integer> dist,int cap) {
    if (s.equals(t) || cap == 0) return cap;
    int res = 0;
    List<Map.Entry<Vertex,Integer>> todo = new ArrayList<>();
    for (Map.Entry<Vertex,Integer> y : s.mEdges.entrySet()) {
      if (y.getValue() > 0 && dist.get(y.getKey()) == dist.get(s) + 1) {
        int flo = dfs(y.getKey(), t, dist, min(y.getValue(), cap - res));
        if (flo > 0) {
          todo.add(new AbstractMap.SimpleEntry<>(y.getKey(),flo));
          res += flo;
          cap -= flo;
        }
      }
    }
    for (Map.Entry<Vertex,Integer> y : todo) {
      upEdge(y.getKey(),s,y.getValue());
    }
    if (res == 0) {
      dist.put(s, -2);
    }
    return res;
  }

  boolean bfs(Vertex s,Vertex t,Map<Vertex,Integer> dist) {
    dist.clear();
    dist.put(s, 0);
    Queue<Vertex> todo = new ArrayDeque<>(dist.keySet());
    for (Vertex x; (x = todo.poll()) != null;) {
      for (Map.Entry<Vertex,Integer> y : x.mEdges.entrySet()) {
        if (dist.containsKey(y.getKey()) || y.getValue() <= 0) continue;
        dist.put(y.getKey(), dist.get(x) + 1);
        todo.add(y.getKey());
      }
    }
    return dist.containsKey(t);
  }

  int getFlow(Vertex s,Vertex t) {
    int res = 0;
    Map<Vertex,Integer> done = new HashMap<>();
    while (bfs(s,t,done)) {
      res += dfs(s,t,done,1<<30);
    }
    return res;
  }
}

public class maxflow {
  public static void main(String[] args) {
    MaxFlow m = new MaxFlow(4);
    m.addEdge(0,1, 2); m.addEdge(0,2, 5); // 2 _._ 5
    m.addEdge(1,3, 3); m.addEdge(2,3, 2); // ./   \.
                                          // 3\_._/2
    System.out.println(m.getFlow(0, 3));
  }
}
