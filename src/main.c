#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

#include "engine/engine.h" 
#include "physics/physics.h"
#include "player/player.h"
#include "physics/phystools.h"
#include "physics/gamemath.h"
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

  MassObject mass_objects[MAX_MASS_OBJECTS];
  setDefaultMassObjectArray(mass_objects);
  // mass_objects[0] = createMassObject((Vector2){1, 0}, (Vector2){0, 0}, 5000);
  // mass_objects[0].can_move = 0;

  int game_paused = 0;

  int mouse_down_flag = 0;
  Vector2 mouseTrack = {0, 0};
  Vector2 percievedMouse = {0, 0};

  // Main game loop
  while (!WindowShouldClose()) {

    // Update variables here

    percievedMouse.x = (GetMouseX() - camera.offset.x + camera.target.x) / camera.zoom;
    percievedMouse.y = (GetMouseY() - camera.offset.y + camera.target.y) / camera.zoom;


    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      mouse_down_flag = 0;
      Vector2 dirVec = Vector2Subtract(mouseTrack, percievedMouse);
      dirVec.x /= 50;
      dirVec.y /= 50;
      MassObject obj = createMassObject(mouseTrack, dirVec, 10);
      push(obj, mass_objects);
    }

    player_control(&camera);
 
    if (game_paused == 0)
      updateMassObjects(mass_objects);
    if (IsKeyPressed(KEY_SPACE))
      game_paused = 1;
    if (IsKeyReleased(KEY_SPACE))
      game_paused = 0;

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
      BeginMode2D(camera);

      // ClearBackground((Color){240, 240, 240, 255});
      ClearBackground(BLACK);
      
      // Axis lines
      for (int x=-10000; x<=10000; x+=100) { DrawLine(x, -10000, x, 10000, GRAY); }
      for (int y=-10000; y<=10000; y+=100) { DrawLine(-10000, y, 10000, y, GRAY); }

      drawMassObjects(mass_objects);

      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (mouse_down_flag == 0) {
          mouseTrack = percievedMouse;
          mouse_down_flag = 1;
        }
        Vector2 test = rotateVectorAboutPoint(percievedMouse, mouseTrack);
        DrawLine(mouseTrack.x, mouseTrack.y, test.x, test.y, BLUE);
      }

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
