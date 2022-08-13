#ifndef PHYSICS_H
#define PHYSICS_H

#include <raylib.h>

#define G 1 // gravitational constant
#define MAX_MASS_OBJECTS 4096

extern int current_mass_object_count;

typedef struct MassObject {
  Vector2 pos, vel;
  float mass, radius;
  int can_move;
} MassObject;


void createMassObject(Vector2 pos, Vector2 vel, float mass);

void deleteMassObject(int index, MassObject arr[]);

void attract(MassObject *atttracted, MassObject attractor, int dist);

extern MassObject mass_objects[MAX_MASS_OBJECTS];

int init_physics(void);

#endif /* PHYSICS_H */

