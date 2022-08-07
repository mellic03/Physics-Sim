#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

#include "physics.h"
#include "phystools.h"
#include "gamemath.h"

MassObject mass_objects[MAX_MASS_OBJECTS];
int current_mass_object_count = 0;

MassObject createMassObject(Vector2 pos, Vector2 vel, double mass) {
  MassObject obj;
  obj.pos = pos;
  obj.vel = vel;
  obj.mass = mass;
  obj.radius = sqrt(obj.mass / PI);
  obj.can_move = 1;
  current_mass_object_count += 1;
  return obj;
}

void deleteMassObject(int index, MassObject arr[]) {
  arr[index].pos = (Vector2){0, 0};
  arr[index].vel = (Vector2){0, 0};
  arr[index].mass = 0;
  arr[index].radius = 0;
  arr[index].can_move = 0;
  current_mass_object_count -= 1;
}

// Updates velocity and position of a MassObject
void attract(MassObject *attracted, MassObject attractor) {
  
  double distSq = Vector2Distance(attracted->pos, attractor.pos);
  distSq *= distSq;
  double F = ((attracted->mass*attractor.mass) / distSq);
  Vector2 direction_vector = Vector2Normalize(Vector2Subtract(attracted->pos, attractor.pos));
  direction_vector.x *= -0.01 * F;
  direction_vector.y *= -0.01 * F;

  attracted->vel = Vector2Add(attracted->vel, direction_vector);
}

int init_physics(void) {
  // Set all properties of mass_objects to 0
  for (int i=0; i<MAX_MASS_OBJECTS; i++) {
    mass_objects[i].pos = (Vector2){0, 0};
    mass_objects[i].vel = (Vector2){0, 0};
    mass_objects[i].mass = 0;
    mass_objects[i].radius = 0;
    mass_objects[i].can_move = 0;
  }
  return 0;
}