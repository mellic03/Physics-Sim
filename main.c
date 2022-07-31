#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include "physics.h"
#include "player.h"

#define screen_width 1000
#define screen_height 1000


int main() {
  // Initialization
  //--------------------------------------------------------------------------------------

  InitWindow(screen_width, screen_height, "PhysGame");
  SetTargetFPS(60);

  struct Player player = create_player();
  Camera2D camera;
  camera.zoom = 1.0f;
  camera.rotation = 0.0f;

  struct mass_object attractor;
  attractor.mass = 500;
  attractor.radius = 100;
  attractor.pos = (Vector2){0, 0};


  // Main game loop
  while (!WindowShouldClose()) {

    // Update variables here
    player_control(&player);
    camera.target.x = player.pos.x - screen_width/2;
    camera.target.y = player.pos.y - screen_height/2;

    player.mo.acc = attract(player.mo, attractor);

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
      BeginMode2D(camera);

      ClearBackground((Color){240, 240, 240, 255});

      // Axis lines
      for (int x=-1000; x<=1000; x+=100) { DrawLine(x, -1000, x, 1000, BLACK); }
      for (int y=-1000; y<=1000; y+=100) { DrawLine(-1000, y, 1000, y, BLACK); }

      player_draw(player);
      DrawCircle(attractor.pos.x, attractor.pos.y, attractor.radius, BLACK);

      EndMode2D();
    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  CloseWindow();

  return 0;
}
