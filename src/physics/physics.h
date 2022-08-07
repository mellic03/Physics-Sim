#include <raylib.h>

#define G 1 // gravitational constant
#define MAX_FORCE 2
#define MAX_MASS_OBJECTS 64

#ifndef PHYSICS_H
#define PHYSICS_H

typedef struct MassObject {
  Vector2 pos, vel, acc;
  double mass, radius;
  int can_move;
} MassObject;

MassObject createMassObject(Vector2 pos, Vector2 vel, double mass);

void attract(MassObject *atttracted, MassObject attractor);

void update_position(MassObject *object);

#endif /* PHYSICS_H */

