#include <raylib.h>
#include <math.h>
#include <raymath.h>
#include "player.h"

Player create_player() {
  Player player;
  player.dir = (Vector2){0.05, 0};
  player.mass = 10;

  player.mo.pos = (Vector2){0, -1500};
  player.mo.vel = (Vector2){5, 0};
  player.mo.mass = 5;

  return player;
}


void player_control(Player *player) {

  if (IsKeyDown(KEY_A)) { player->dir = Vector2Rotate(player->dir, -0.05f); }
  if (IsKeyDown(KEY_D)) { player->dir = Vector2Rotate(player->dir, +0.05f); }
  if (IsKeyDown(KEY_SPACE)) { player->mo.vel = Vector2Add(player->mo.vel, player->dir); }

  player->mo.vel = Vector2Add(player->mo.vel, player->mo.acc);
  player->mo.pos = Vector2Add(player->mo.pos, player->mo.vel);
  player->norm_dir = Vector2Normalize(player->dir);

  player->pos = player->mo.pos;

}

void player_draw(Player player) {

  if (IsKeyDown(KEY_SPACE)) {
    DrawCircle((player.pos.x - 25*player.norm_dir.x), (player.pos.y - 25*player.norm_dir.y), 15, ORANGE);
    DrawCircle((player.pos.x - 35*player.norm_dir.x), (player.pos.y - 35*player.norm_dir.y), 10, ORANGE);
  }
  
  DrawCircle((player.pos.x - 20*player.norm_dir.x), (player.pos.y - 20*player.norm_dir.y), 10, BLUE);
  DrawCircle(player.pos.x, player.pos.y, 20, BLUE);
  DrawCircle((player.pos.x + 30*player.norm_dir.x), (player.pos.y + 30*player.norm_dir.y), 15, BLUE);

  DrawText(
    TextFormat("vX: %1.1lf", player.mo.vel.x),
    player.pos.x-450,
    player.pos.y-450,
    24,
    BLACK
  );
 
  DrawText(
    TextFormat("vY %1.1lf", player.mo.vel.y),
    player.pos.x-450,
    player.pos.y-400,
    24,
    BLACK
  );
  
  DrawText(
    TextFormat("|v| %1.1lf", sqrt(pow(player.mo.vel.x, 2) + pow(player.mo.vel.y, 2))),
    player.pos.x -450,
    player.pos.y-350,
    24,
    BLACK
  );
}

