#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include "physics/physics.h"
#include "player/player.h"

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

  MassObject attractor;
  attractor.mass = 5000;
  attractor.radius = 500;
  attractor.pos = (Vector2){0, 0};

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

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
      BeginMode2D(camera);

      ClearBackground((Color){240, 240, 240, 255});
      
      DrawRectangle(-1000, -1000, 1000, 1000, (Color){0, 200, 200, 255});
      DrawRectangle(-1000, 0, 1000, 1000, (Color){0, 200, 0, 255});
      DrawRectangle(0, -1000, 1000, 1000, (Color){200, 0, 200, 255});
      DrawRectangle(0, 0, 1000, 1000, (Color){200, 200, 50, 255});
      
      // Axis lines
      for (int x=-10000; x<=10000; x+=100) { DrawLine(x, -10000, x, 10000, BLACK); }
      for (int y=-10000; y<=10000; y+=100) { DrawLine(-10000, y, 10000, y, BLACK); }

      DrawCircle(attractor.pos.x, attractor.pos.y, attractor.radius, BLACK);

      EndMode2D();
    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  CloseWindow();

  return 0;
}
