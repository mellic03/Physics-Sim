#include <raylib.h>
#include <raymath.h>
#include "player.h"

struct Player create_player() {
  struct Player player;
  player.pos = (Vector2){500, 100};
  player.dir = (Vector2){0.05, 0};
  player.mass = 10;

  player.mo.pos = (Vector2){0, -300};
  player.mo.mass = 5;

  return player;
}


void player_control(struct Player *player) {


  if (IsKeyDown(KEY_A)) { player->dir = Vector2Rotate(player->dir, -0.05f); }
  if (IsKeyDown(KEY_D)) { player->dir = Vector2Rotate(player->dir, +0.05f); }
  if (IsKeyDown(KEY_SPACE)) { player->mo.vel = Vector2Add(player->mo.vel, player->dir); }

  player->mo.vel = Vector2Add(player->mo.vel, player->mo.acc);
  player->mo.pos = Vector2Add(player->mo.pos, player->mo.vel);
  player->norm_dir = Vector2Normalize(player->dir);

  player->pos = player->mo.pos;


}

void player_draw(struct Player player) {

  if (IsKeyDown(KEY_SPACE)) {
    DrawCircle((player.pos.x - 25*player.norm_dir.x), (player.pos.y - 25*player.norm_dir.y), 15, ORANGE);
    DrawCircle((player.pos.x - 35*player.norm_dir.x), (player.pos.y - 35*player.norm_dir.y), 10, ORANGE);
  }
  
  DrawCircle((player.pos.x - 20*player.norm_dir.x), (player.pos.y - 20*player.norm_dir.y), 10, BLUE);
  DrawCircle(player.pos.x, player.pos.y, 20, BLUE);
  DrawCircle((player.pos.x + 30*player.norm_dir.x), (player.pos.y + 30*player.norm_dir.y), 15, BLUE);

  DrawText(TextFormat("dX: %1.1lf", player.mo.vel.x), player.pos.x-250, player.pos.y, 24, BLACK);
  DrawText(TextFormat("dY %1.1lf", player.mo.vel.y), player.pos.x, player.pos.y-250, 24, BLACK);
}
