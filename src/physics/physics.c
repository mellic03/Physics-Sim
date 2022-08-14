#include <raylib.h>
#include <raymath.h>
#include "physics.h"
#include "phystools.h"
#include "gamemath.h"

MassObject mass_objects[MAX_MASS_OBJECTS];
int mass_object_count = 0;

GelParticle gel_particles[MAX_GEL_PARTICLES];
int gel_particle_count = 0;

// GRAVITY
//-----------------------------------------------------------------------------------------------
void sort_mass_objects(MassObject arr[]) {
  for (int i=0; i<mass_object_count+1; i++) {
    if (arr[i].mass == 0) {
      for (int j=mass_object_count; j>i; j--) {
        if (arr[j].mass != 0) {
          MassObject temp = arr[i];
          arr[i] = arr[j];
          arr[j] = temp;
          break;
        }
      }
    }
  }
}

void createMassObject(Vector2 pos, Vector2 vel, float mass) {
  if (mass_object_count >= MAX_MASS_OBJECTS)
    return;
  mass_objects[mass_object_count].pos = pos;
  mass_objects[mass_object_count].vel = vel;
  mass_objects[mass_object_count].mass = mass;
  mass_objects[mass_object_count].radius = shitsqrt(mass_objects[mass_object_count].mass / PI);
  mass_objects[mass_object_count].can_move = 1;
  mass_object_count += 1;
  return;
}

void deleteMassObject(int index, MassObject arr[]) {
  arr[index].pos = (Vector2){0, 0};
  arr[index].vel = (Vector2){0, 0};
  arr[index].mass = 0;
  arr[index].radius = 0;
  arr[index].can_move = 0;
  mass_object_count -= 1;
  sort_mass_objects(mass_objects);
}

void attract(MassObject *attracted, MassObject attractor, int dist) {
  float F = ((G*attractor.mass) / (dist*dist));
  Vector2 direction_vector = Vector2Normalize(Vector2Subtract(attractor.pos, attracted->pos));
  direction_vector = Vector2Scale(direction_vector, F);
  attracted->vel = Vector2Add(attracted->vel, direction_vector);
}
//-----------------------------------------------------------------------------------------------


// GEL PARTICLES
//-----------------------------------------------------------------------------------------------
void sort_gel_particles(GelParticle arr[]) {
  for (int i=0; i<gel_particle_count+1; i++) {
    if (arr[i].active == 0) {
      for (int j=gel_particle_count; j>i; j--) {
        if (arr[j].active != 0) {
          GelParticle temp = arr[i];
          arr[i] = arr[j];
          arr[j] = temp;
          break;
        }
      }
    }
  }
}

void create_gel_particle(Vector2 pos, Vector2 vel) {
  if (gel_particle_count >= MAX_GEL_PARTICLES)
    return;
  else {
    gel_particles[gel_particle_count].pos = pos;
    gel_particles[gel_particle_count].vel = vel;
    gel_particles[gel_particle_count].active = 1;
    gel_particle_count += 1;
  }
}

void delete_gel_particle(int index, GelParticle arr[]) {
  arr[index].pos = (Vector2){0, 0};
  arr[index].vel = (Vector2){0, 0};
  arr[index].active = 0;
  gel_particle_count -= 1;
  sort_gel_particles(gel_particles);
}

void attract_gel(GelParticle *attracted, GelParticle attractor, int pull_radius, int pull_force, int push_radius, int push_force) {

  float dist = Vector2Distance(attracted->pos, attractor.pos);

  Vector2 dirVec = Vector2Subtract(attractor.pos, attracted->pos);
  dirVec = Vector2Normalize(dirVec);
  
  // Attractive force
  if (dist > push_radius && dist < pull_radius) {
    float attractive_force = ((G*pull_force) / (dist + 1));
    dirVec = Vector2Scale(dirVec, attractive_force);
    attracted->pos = Vector2Add(attracted->pos, dirVec);
  }

  // Repulsive force
  else if (dist <= push_radius) {
    float repulsive_force = -((G*push_force) / (dist + 1));
    dirVec = Vector2Scale(dirVec, repulsive_force);
    attracted->pos = Vector2Add(attracted->pos, dirVec);
  }
}
//-----------------------------------------------------------------------------------------------




int init_physics(void) {
  for (int i=0; i<MAX_MASS_OBJECTS; i++) {
    mass_objects[i].pos = (Vector2){0, 0};
    mass_objects[i].vel = (Vector2){0, 0};
    mass_objects[i].mass = 0;
    mass_objects[i].radius = 0;
    mass_objects[i].can_move = 0;
  }
  for (int i=0; i<MAX_GEL_PARTICLES; i++) {
    gel_particles[i].pos = (Vector2){0, 0};
    gel_particles[i].vel = (Vector2){0, 0};
    gel_particles[i].active = 0;
  }
  return 0;
}
