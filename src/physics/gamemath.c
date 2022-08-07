#include "gamemath.h"
#include <raymath.h>
#include <math.h>

int fastpow(int base, int exponent) {
  int n = 1;
  for (int i=0; i<exponent; i++) {
    n *= base;
  }
  return n;
}

Vector2 rotateVectorAboutPoint(Vector2 vec, Vector2 point) {

  double slope = (vec.y-point.y) / (vec.x-point.x);
  double b = point.y - slope*point.x;
  double dX = fabs(point.x-vec.x);

  if (dX == 0) {
    dX = 0.0001;
  }

  double new_x;
  double new_y;
  if (vec.x < point.x) {
    new_x = point.x + 5*dX;
  }
  else {
    new_x = point.x - 5*dX;
  }
  new_y = slope*new_x + b;
  return (Vector2){new_x, new_y};
}
