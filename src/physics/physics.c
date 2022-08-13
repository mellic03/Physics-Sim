#include <raylib.h>
#include <raymath.h>
#include "physics.h"
#include "phystools.h"
#include "gamemath.h"

MassObject mass_objects[MAX_MASS_OBJECTS];
int current_mass_object_count = 0;


// Push all MassObjects with mass 0 to the end of the array up to current_mass_object_count
void sort_mass_objects(MassObject arr[]) {
  for (int i=0; i<current_mass_object_count+1; i++) {
    if (arr[i].mass == 0) {
      for (int j=current_mass_object_count; j>i; j--) {
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
  if (current_mass_object_count >= MAX_MASS_OBJECTS)
    return;
  mass_objects[current_mass_object_count].pos = pos;
  mass_objects[current_mass_object_count].vel = vel;
  mass_objects[current_mass_object_count].mass = mass;
  mass_objects[current_mass_object_count].radius = shitsqrt(mass_objects[current_mass_object_count].mass / PI);
  mass_objects[current_mass_object_count].can_move = 1;
  current_mass_object_count += 1;
  return;
}

void deleteMassObject(int index, MassObject arr[]) {
  arr[index].pos = (Vector2){0, 0};
  arr[index].vel = (Vector2){0, 0};
  arr[index].mass = 0;
  arr[index].radius = 0;
  arr[index].can_move = 0;
  current_mass_object_count -= 1;
  sort_mass_objects(mass_objects);
}

void attract(MassObject *attracted, MassObject attractor, int dist) {
  float F = ((G*attractor.mass) / (dist*dist));
  Vector2 direction_vector = Vector2Normalize(Vector2Subtract(attractor.pos, attracted->pos));
  direction_vector = Vector2Scale(direction_vector, F);
  attracted->vel = Vector2Add(attracted->vel, direction_vector);  
}

int init_physics(void) {
  // Set all properties of all MassObjects  to 0
  for (int i=0; i<MAX_MASS_OBJECTS; i++) {
    mass_objects[i].pos = (Vector2){0, 0};
    mass_objects[i].vel = (Vector2){0, 0};
    mass_objects[i].mass = 0;
    mass_objects[i].radius = 0;
    mass_objects[i].can_move = 0;
  }
  return 0;
}
