#ifndef PHYSICS_H
#define PHYSICS_H

#include <raylib.h>


// MASSOBJECTS
//---------------------------------------
#define G 1 // gravitational constant
#define MAX_MASS_OBJECTS 4096
//---------------------------------------

// GEL PARTICLES
//---------------------------------------
#define MAX_GEL_PARTICLES 1024

// TOOLS
#define PUSH_TOOL_STRENGTH 0.2
#define PUSH_TOOL_RADIUS 150

// VISCOUS LIQUID
#define VLIQUID_PARTICLE_RADIUS 5
#define VLIQUID_PUSH_RADIUS 40
#define VLIQUID_PULL_RADIUS 150
#define VLIQUID_PUSH_STRENGTH 5
#define VLIQUID_PULL_STRENGTH 1
//---------------------------------------

typedef struct MassObject {
  Vector2 pos, vel;
  float mass, radius;
  int can_move;
} MassObject;


typedef struct GelParticle {
  Vector2 pos, vel;
  int active;
} GelParticle;


// GRAVITY
//-----------------------------------------------------------------------------------------------
extern int mass_object_count;
extern MassObject mass_objects[MAX_MASS_OBJECTS];
void createMassObject(Vector2 pos, Vector2 vel, float mass);
void deleteMassObject(int index, MassObject arr[]);
void attract(MassObject *atttracted, MassObject attractor, int dist);
//-----------------------------------------------------------------------------------------------


// GEL PARTICLES
//-----------------------------------------------------------------------------------------------
extern int gel_particle_count;
extern GelParticle gel_particles[MAX_GEL_PARTICLES];
void sort_gel_particles(GelParticle arr[]);
void create_gel_particle(Vector2 pos, Vector2 vel);
void delete_gel_particle(int index, GelParticle arr[]);
void attract_gel(GelParticle *attracted, GelParticle attractor, float pull_radius, float pull_force, float push_radius, float push_force);
void push_gel_particles(Vector2 pos);

//-----------------------------------------------------------------------------------------------


int init_physics(void);

#endif /* PHYSICS_H */

