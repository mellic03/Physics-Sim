#ifndef PHYSTOOLS_H
#define PHYSTOOLS_H
#include "physics.h"

void updateMassObjects(MassObject arr[]);
void drawMassObjects(void);
void create_massobject_ring(Vector2 pos, float mass, float r);

void draw_gel_particles(void);
void update_gel_particles(void);

#endif /* PHYSTOOLS_H */