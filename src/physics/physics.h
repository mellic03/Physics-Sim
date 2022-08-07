#ifndef PHYSICS_H
#define PHYSICS_H

#include <raylib.h>

#define G 0.4 // gravitational constant
#define MAX_FORCE 2
#define MAX_MASS_OBJECTS 1000000

extern int current_mass_object_count;

typedef struct MassObject {
  Vector2 pos, vel, acc;
  double mass, radius;
  int can_move;
} MassObject;

MassObject createMassObject(Vector2 pos, Vector2 vel, double mass);

void deleteMassObject(int index, MassObject arr[]);

void attract(MassObject *atttracted, MassObject attractor);

extern MassObject mass_objects[MAX_MASS_OBJECTS];

int init_physics(void);

#endif /* PHYSICS_H */

