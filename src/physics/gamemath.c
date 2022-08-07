#include "gamemath.h"

int fastpow(int base, int exponent) {
  int n = 1;
  for (int i=0; i<exponent; i++) {
    n *= base;
  }
  return n;
}
