#include "phystools.h"
#include <raymath.h>
#include <stdio.h>
#include "gamemath.h"

void setDefaultMassObjectArray(MassObject arr[]) {
  for (int i=0; i<MAX_MASS_OBJECTS; i++) {
    arr[i].pos = (Vector2){0, 0};
    arr[i].vel = (Vector2){0, 0};
    arr[i].acc = (Vector2){0, 0};
    arr[i].mass = 0;
    arr[i].radius = 0;
    arr[i].can_move = 0;
  }
}

void deleteMassObject(int index, MassObject arr[]) {
  arr[index].pos = (Vector2){0, 0};
  arr[index].vel = (Vector2){0, 0};
  arr[index].acc = (Vector2){0, 0};
  arr[index].mass = 0;
  arr[index].radius = 0;
  arr[index].can_move = 0;
}

// Push a MassObject to an array of MassObjects.
// Return 0 for success, 1 for failure.
int push(MassObject obj, MassObject arr[]) {
  for (int i=0; i<MAX_MASS_OBJECTS; i++) {
    if (arr[i].mass == 0) {
      arr[i] = obj;
      return 0;
    }
  }
  return 1;
}

// Update the positions of all MassObjects.
void updateMassObjects(MassObject arr[]) {
  for (int i=0; i<MAX_MASS_OBJECTS; i++) {
    for (int j=0; j<MAX_MASS_OBJECTS; j++) {
      if (i!=j && arr[i].mass!=0 && arr[j].mass!=0) {

        double dist = Vector2Distance(arr[i].pos, arr[j].pos);

        if (dist <= arr[i].radius + arr[j].radius) {
          // Momentum before collision == momentum after collision
          // Momentum = Mass * Velocity
          // Velocity = Momentum / Mass
          
          Vector2 momentum_i = Vector2Scale(arr[i].vel, arr[i].mass);
          Vector2 momentum_j = Vector2Scale(arr[j].vel, arr[j].mass);
          Vector2 momentum = Vector2Add(momentum_i, momentum_j);

          if (arr[i].mass >= arr[j].mass) {
            arr[i].mass += arr[j].mass;
            arr[i].vel = Vector2Scale(momentum, (1/arr[i].mass));
            deleteMassObject(j, arr);
          }

          else {
            arr[j].mass += arr[i].mass;
            arr[j].vel = Vector2Scale(momentum, (1/arr[j].mass));
            deleteMassObject(i, arr);
          }
        }

        double distSq = dist*dist;
        // double F = G * (arr[i].mass * arr[j].mass) / distSq;
        double F = ((G*arr[j].mass) / distSq);

        Vector2 direction_vector = Vector2Normalize(Vector2Subtract(arr[j].pos, arr[i].pos));
        direction_vector = Vector2Scale(direction_vector, F);
        arr[i].vel = Vector2Add(arr[i].vel, direction_vector);  
      }
    }
    arr[i].pos = Vector2Add(arr[i].pos, arr[i].vel);
    arr[i].radius = sqrt(arr[i].mass/PI);
  }
}


void drawMassObjects(MassObject arr[]) {
  for (int i=0; i<MAX_MASS_OBJECTS; i++) {
    if (arr[i].mass != 0) {
      DrawCircle(arr[i].pos.x, arr[i].pos.y, arr[i].radius, BLUE);
    }
  }
}
