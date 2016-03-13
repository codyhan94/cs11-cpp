// A 2-dimensional point class!
// Coordinates are double-precision floating point.
class Point {

private:
  double x_coord;
  double y_coord;

public:
  // Constructors
  Point();                      // default constructor
  Point(double x, double y);    // two-argument constructor

  // Destructor
  ~Point();

  // Mutator methods
  void setX(double val);
  void setY(double val);

  // Accessor methods
  double getX();
  double getY();
};
