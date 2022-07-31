#include <raylib.h>

#ifndef PHYSICS_H
#define PHYSICS_H

struct mass_object {
  Vector2 pos, vel, acc;
  double mass, radius;
};

Vector2 attract(struct mass_object object1, struct mass_object object2);

void update_position(struct mass_object *object);


#endif /* PHYSICS_H */