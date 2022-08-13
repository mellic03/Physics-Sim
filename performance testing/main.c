#include <stdio.h>
#include <math.h>
#include <time.h>

int fastpow(int base, int exponent) {
  int n = 1;
  for (int i=0; i<exponent; i++)
    n *= base;
  return n;
}

int shitsqrt(int n) {
  int a = 0;
  while (a*a < n) {
    a += 1;
  }
  return a;
}


int main() {
  // Start timer
  clock_t t;
  t = clock();


  for (int i=0; i<1000000000; i++) {
    int n = shitsqrt(i);
  }


  // End timer.
  t = clock() - t;
  float time_taken = ((float)t)/CLOCKS_PER_SEC;

  printf("CPU = %0.10lf\n", time_taken);

  return 0;
}