#include <raylib.h>

#ifndef PHYSICS_H
#define PHYSICS_H

typedef struct MassObject {
  Vector2 pos, vel, acc;
  double mass, radius;
} MassObject;

Vector2 attract(MassObject object1, MassObject object2);
Vector2 attract_down(MassObject mo, int ground_y);

void update_position(MassObject *object);

#endif /* PHYSICS_H */

