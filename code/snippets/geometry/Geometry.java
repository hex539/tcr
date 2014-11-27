import java.awt.geom.*; import java.lang.*; import java.util.*; import java.math.*; import java.io.*;
public class Geometry extends In{
  static void next_point(Point2D.Double p) throws Exception {
    p.x = Double.parseDouble(stdin.nextToken());
    p.y = Double.parseDouble(stdin.nextToken());
  }
  static double getArea(PathIterator it) { double res = 0;
    Point2D.Double orig = new Point2D.Double(), curr = new Point2D.Double(); double[] coords = new double[6];
    while (!it.isDone()) {
      switch (it.currentSegment(coords)) {
        case PathIterator.SEG_CLOSE: {
          res += (curr.y * orig.x - curr.x * orig.y);
          break;
        }
        case PathIterator.SEG_LINETO: {
          res += (curr.y * coords[0] - curr.x * coords[1]);
          curr.x = coords[0];
          curr.y = coords[1];
          break;
        }
        case PathIterator.SEG_MOVETO: {
          orig.x = curr.x = coords[0];
          orig.y = curr.y = coords[1];
          break;
        }
        default: break;
      }
      it.next();
    }
    return Math.abs(res / 2); }

  public static void main(String[] args) throws Exception {
    int n = nextInt(); Point2D.Double[] poly = new Point2D.Double[n];
    Point2D.Double p = new Point2D.Double(); // read in polygon
    for (int i = 0; i < n; i++) {
      next_point(p);
      poly[i] = new Point2D.Double(p.x, p.y);
    }
    Point2D.Double[] cuts = {new Point2D.Double(), new Point2D.Double()}; // read cut axis / thickness
    next_point(cuts[0]);
    next_point(cuts[1]);
    double radius = Double.parseDouble(stdin.nextToken());
    double dx = cuts[1].x - cuts[0].x; // normalise cut plane
    double dy = cuts[1].y - cuts[0].y; {{
      double len = Math.hypot(dx, dy);
      dx /= len;
      dy /= len;
      for (int a = 2; a --> 0;) {
        cuts[a].x = cuts[0].x + dx * 400000 * (a>0? 1: -1);
        cuts[a].y = cuts[0].y + dy * 400000 * (a>0? 1: -1);
    } }
    Path2D.Double rect = new Path2D.Double(); // compute cutting rect
    rect.moveTo(cuts[0].x + radius * dy, cuts[0].y - radius * dx);
    rect.lineTo(cuts[0].x - radius * dy, cuts[0].y + radius * dx);
    rect.lineTo(cuts[1].x - radius * dy, cuts[1].y + radius * dx);
    rect.lineTo(cuts[1].x + radius * dy, cuts[1].y - radius * dx);
    rect.closePath();

    Path2D.Double path = new Path2D.Double(); // prepare polygon for intersection
    path.moveTo(poly[0].x,poly[0].y);
    for (int i=1; i<n; i++) {
      path.lineTo(poly[i].x,poly[i].y);
    }
    path.closePath();
    Area ar = new Area(path); // perform subtraction (WARNING: SLOW -- O(N^2))
    ar.subtract(new Area(rect));
    double area_final = getArea(ar.getPathIterator(new AffineTransform()));
    System.out.println(String.format("%.9f",area_final));
  }
}
