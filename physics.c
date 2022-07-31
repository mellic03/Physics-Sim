#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include "physics.h"

#define G 9.807 // gravitational acceleration on earth.
#define MAX_FORCE 10 // Maximum allowed force.
#define MAX_SPEED 10 // Maximum allowed speed.


// Returns an acceleration vector from attracted->attractor
Vector2 attract(struct mass_object attracted, struct mass_object attractor) {
  
  // F is the amount of force exerted on each object in the direction of the other object.
  double distSq = pow(Vector2Distance(attracted.pos, attractor.pos), 2);
  double F = G * ((attracted.mass*attractor.mass) / distSq);

  Vector2 direction_vector = Vector2Normalize(Vector2Subtract(attracted.pos, attractor.pos));

  direction_vector.x *= F;
  direction_vector.y *= F;
  direction_vector.x = -direction_vector.x;
  direction_vector.y = -direction_vector.y;

  Vector2 acc = {direction_vector.x/attracted.mass, direction_vector.y/attracted.mass};

  return (acc);
}


void update_position(struct mass_object *object) {
  object->vel = Vector2Add(object->vel, object->acc); // Add accleration to velocity
  object->pos = Vector2Add(object->pos, object->vel); // Add velocity to position
}
