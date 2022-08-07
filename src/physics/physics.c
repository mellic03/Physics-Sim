#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include "physics.h"
#include "gamemath.h"
#include <stdio.h>


MassObject createMassObject(Vector2 pos, Vector2 vel, double mass) {
  MassObject obj;
  obj.pos = pos;
  obj.vel = vel;
  obj.mass = mass;
  obj.radius = sqrt(obj.mass / PI);
  obj.can_move = 1;
  return obj;
}

// Updates velocity and position of a MassObject
void attract(MassObject *attracted, MassObject attractor) {
  
  double distSq = Vector2Distance(attracted->pos, attractor.pos);
  distSq *= distSq;
  double F = ((attracted->mass*attractor.mass) / distSq);
  Vector2 direction_vector = Vector2Normalize(Vector2Subtract(attracted->pos, attractor.pos));
  direction_vector.x *= -0.01 * F;
  direction_vector.y *= -0.01 * F;


  attracted->vel = Vector2Add(attracted->vel, direction_vector);
}


void update_position(MassObject *object) {
  object->vel = Vector2Add(object->vel, object->acc); // Add accleration to velocity
  object->pos = Vector2Add(object->pos, object->vel); // Add velocity to position
}
