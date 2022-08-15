#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

#include "physics/gamemath.h"
#include "physics/physics.h"
#include "player/player.h"
#include "physics/phystools.h"
#include "physics/physics.h"
#include "ui/ui.h"

int screen_width = 2560;
int screen_height = 1440;

int main() {

  // float n = 1;
  // float rate = 0.4;
  // for (int i=0; i<1000000; i++) {
  //   n *= rate;
  //   n += 1;
  //   printf("%f\n", n);
  // }

  // Initialization
  //--------------------------------------------------------------------------------------
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screen_width, screen_height, "PhysGame");
  SetTargetFPS(60);

  Camera2D camera;
  camera.target = (Vector2){0, 0};
  camera.zoom = 1.0f;
  camera.rotation = 0.0f;

  Vector2 percievedMouse;

  init_physics();

  int game_paused = 0;

  // Main game loop
  while (!WindowShouldClose()) {

    // Update variables here

    if (game_paused == 0) {
      updateMassObjects(mass_objects);
      update_gel_particles();
    }
    if (IsKeyDown(KEY_SPACE))
      game_paused = 1;
    else
      game_paused = 0;


    if (IsKeyDown(KEY_F))
      SetTargetFPS(100000);
    if (IsKeyReleased(KEY_F))
      SetTargetFPS(60);

    if (IsKeyDown(KEY_UP)) {
      for (int i=0; i<gel_particle_count; i++) {
        gel_particles[i].pos.y += 1;
      }
    }

    percievedMouse = GetScreenToWorld2D(GetMousePosition(), camera);

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
      BeginMode2D(camera);
      ClearBackground(BLACK);
      
      player_control(&camera, percievedMouse);

      drawMassObjects();
      draw_gel_particles();

      EndMode2D();
      // Handle UI here
      //-------------------------
      draw_tool_menu();
      player_ui();
      //-------------------------
    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  CloseWindow();

  return 0;
}
