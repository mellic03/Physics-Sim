#ifndef PHYSTOOLS_H
#define PHYSTOOLS_H
#include "physics.h"

void updateMassObjects(MassObject arr[]);

void drawMassObjects(MassObject arr[]);

void create_massobject_ring(Vector2 pos, float mass, float r);
void sort_mass_objects(MassObject arr[]);

#endif /* PHYSTOOLS_H */