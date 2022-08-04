#include <raylib.h>
#include "../physics/physics.h"

#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player {
  MassObject mo;
  Vector2 pos, dir, norm_dir, vel, acc;
  double mass;
  int health;
} Player;

Player create_player();
void player_control(Player *player);
void player_draw(Player player);

#endif /* PLAYER_H */
