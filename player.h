#include <raylib.h>
#include "physics.h"

#ifndef PLAYER_H
#define PLAYER_H

struct Player {
  struct mass_object mo;
  Vector2 pos, dir, norm_dir, vel, acc;
  double mass;
  int health;
};

struct Player create_player();
void player_control(struct Player *player);
void player_draw(struct Player player);

#endif /* PLAYER_H */
