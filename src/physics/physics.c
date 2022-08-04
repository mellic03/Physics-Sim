#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include "physics.h"

#define G 9.807 // gravitational acceleration on earth.
#define MAX_FORCE 2

// Returns an acceleration vector from attracted->attractor
Vector2 attract(MassObject attracted, MassObject attractor) {
  
  // F is the amount of force exerted on each object in the direction of the other object.
  double distSq = pow(Vector2Distance(attracted.pos, attractor.pos), 2);
  double F = G * ((attracted.mass*attractor.mass) / distSq);
  //F = (F > MAX_FORCE) ? MAX_FORCE : F;

  Vector2 direction_vector = Vector2Normalize(Vector2Subtract(attracted.pos, attractor.pos));

  direction_vector.x *= -F;
  direction_vector.y *= -F;

  return (direction_vector);
}

Vector2 attract_down(MassObject mo, int ground_y) {

  Vector2 direction_vector = (Vector2){0, 0.03};

  return (direction_vector);
}

void update_position(MassObject *object) {
  object->vel = Vector2Add(object->vel, object->acc); // Add accleration to velocity
  object->pos = Vector2Add(object->pos, object->vel); // Add velocity to position
}
