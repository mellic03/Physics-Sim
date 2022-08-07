#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

#include "engine/engine.h" 
#include "physics/physics.h"
#include "player/player.h"
#include "physics/phystools.h"
#include "physics/physics.h"
#include "ui/ui.h"

int screen_width = 1280;
int screen_height = 720;

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

  init_physics();
  mass_objects[0] = createMassObject((Vector2){1, 0}, (Vector2){0, 0}, 5000);
  mass_objects[0].can_move = 0;


  // Main game loop
  while (!WindowShouldClose()) {

    // Update variables here

    player_control(&camera);
 
    // if (game_paused == 0)
    //   updateMassObjects(mass_objects);
    // if (IsKeyPressed(KEY_SPACE))
    //   game_paused = 1;
    // if (IsKeyReleased(KEY_SPACE))
    //   game_paused = 0;

    updateMassObjects(mass_objects);


    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
      BeginMode2D(camera);

      ClearBackground(BLACK);
      

      player_control(&camera);
      drawMassObjects(mass_objects);


      EndMode2D();
      // Handle UI here
      //-------------------------
      draw_tool_menu();
      //-------------------------


    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  CloseWindow();

  return 0;
}
