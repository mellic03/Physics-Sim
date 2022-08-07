#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include "physics/physics.h"
#include "player/player.h"
#include "physics/phystools.h"

int screen_width = 1920;
int screen_height = 1080;

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
  int mouseXTrack = 0; 
  int mouseYTrack = 0;

  // Main game loop
  while (!WindowShouldClose()) {

    screen_width = GetScreenWidth();
    screen_height = GetScreenHeight();

    // Update variables here
    if (IsKeyDown(KEY_A)) { camera.target.x -= 5; }
    if (IsKeyDown(KEY_D)) { camera.target.x += 5; }
    if (IsKeyDown(KEY_W)) { camera.target.y -= 5; }
    if (IsKeyDown(KEY_S)) { camera.target.y += 5; }
    camera.zoom += 0.1 * GetMouseWheelMove();
    camera.offset = (Vector2){screen_width/2, screen_height/2};

    int percievedMouseX = GetMouseX() - camera.offset.x + camera.target.x;
    int percievedMouseY = GetMouseY() - camera.offset.y + camera.target.y;


    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      mouse_down_flag = 0;
      Vector2 dirVec = Vector2Subtract((Vector2){mouseXTrack, mouseYTrack}, (Vector2){percievedMouseX, percievedMouseY});
      dirVec.x /= 20;
      dirVec.y /= 20;
      MassObject obj = createMassObject((Vector2){mouseXTrack, mouseYTrack}, dirVec, 200);
      push(obj, mass_objects);
    }

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
      
      // DrawRectangle(-1000, -1000, 1000, 1000, (Color){0, 200, 200, 255});
      // DrawRectangle(-1000, 0, 1000, 1000, (Color){0, 200, 0, 255});
      // DrawRectangle(0, -1000, 1000, 1000, (Color){200, 0, 200, 255});
      // DrawRectangle(0, 0, 1000, 1000, (Color){200, 200, 50, 255});
      
      // Axis lines
      // for (int x=-10000; x<=10000; x+=100) { DrawLine(x, -10000, x, 10000, BLACK); }
      // for (int y=-10000; y<=10000; y+=100) { DrawLine(-10000, y, 10000, y, BLACK); }

      drawMassObjects(mass_objects);
      DrawCircle(percievedMouseX, percievedMouseY, 20, RED);

      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (mouse_down_flag == 0) {
          mouseXTrack = percievedMouseX;
          mouseYTrack = percievedMouseY;
          mouse_down_flag = 1;
        }
        DrawLine(mouseXTrack, mouseYTrack, percievedMouseX, percievedMouseY, BLUE);
      }

      EndMode2D();
    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  CloseWindow();

  return 0;
}
