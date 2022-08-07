#ifndef PHYSICS_H
#define PHYSICS_H

#include <raylib.h>

#define G 1 // gravitational constant
#define MAX_FORCE 2
#define MAX_MASS_OBJECTS 1024


typedef struct MassObject {
  Vector2 pos, vel, acc;
  double mass, radius;
  int can_move;
} MassObject;

MassObject createMassObject(Vector2 pos, Vector2 vel, double mass);

void attract(MassObject *atttracted, MassObject attractor);

#endif /* PHYSICS_H */

