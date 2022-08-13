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
  // mass_objects[0].mass = 100000;
  // mass_objects[0].radius = shitsqrt(mass_objects[0].mass / PI);
  // mass_objects[0].can_move = 1;


  int game_paused = 0;

  // Main game loop
  while (!WindowShouldClose()) {

    // Update variables here

    if (game_paused == 0)
      updateMassObjects(mass_objects);
    if (IsKeyDown(KEY_SPACE))
      game_paused = 1;
    else
      game_paused = 0;


    if (IsKeyDown(KEY_F))
      SetTargetFPS(1000);
    if (IsKeyReleased(KEY_F))
      SetTargetFPS(60);

    percievedMouse = GetScreenToWorld2D(GetMousePosition(), camera);

    // printf("Camera pos: %0.1lf %0.1lf\n", camera.target.x, camera.target.y);

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
      BeginMode2D(camera);
      ClearBackground(BLACK);
      

      player_control(&camera, percievedMouse);
      drawMassObjects(mass_objects);

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
