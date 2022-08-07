#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include "player.h"
#include "../physics/phystools.h"
#include "../physics/physics.h"
#include "../physics/gamemath.h"
#include "../ui/ui.h"

int mouse_down_flag = 0;
Vector2 mouseTrack = {0, 0};
Vector2 percievedMouse = {0, 0};

void player_control(Camera2D *cam) {

  if (IsKeyDown(KEY_A)) { cam->target.x -= 5 / cam->zoom; }
  if (IsKeyDown(KEY_D)) { cam->target.x += 5 / cam->zoom; }
  if (IsKeyDown(KEY_W)) { cam->target.y -= 5 / cam->zoom; }
  if (IsKeyDown(KEY_S)) { cam->target.y += 5 / cam->zoom; }
  cam->zoom += 0.2 * cam->zoom * GetMouseWheelMove();
  cam->offset = (Vector2){GetScreenWidth()/2, GetScreenHeight()/2};

  // percievedMouse.x = (GetMouseX() - cam->offset.x + cam->target.x) / cam->zoom;
  // percievedMouse.y = (GetMouseY() - cam->offset.y + cam->target.y) / cam->zoom;

  percievedMouse.x = (GetMouseX() + cam->target.x - cam->offset.x);// / cam->zoom;
  percievedMouse.y = (GetMouseY() + cam->target.y - cam->offset.y);// / cam->zoom;

  // DrawCircle(percievedMouse.x, percievedMouse.y, 20, RED);

  if (GetMouseX() > 400 || GetMouseY() > 200) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      if (mouse_down_flag == 0) {
        mouseTrack = percievedMouse;
        mouse_down_flag = 1;
      }
      Vector2 test = rotateVectorAboutPoint(percievedMouse, mouseTrack);
      DrawLine(mouseTrack.x, mouseTrack.y, test.x, test.y, BLUE);
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      mouse_down_flag = 0;

      MassObject obj;

      switch (tool_mode) {
        case (SINGLEMODE):
          Vector2 dirVec = Vector2Subtract(mouseTrack, percievedMouse);
          dirVec.x /= 50;
          dirVec.y /= 50;
          push(createMassObject(mouseTrack, dirVec, 10), mass_objects);
        break;

        case (MATRIXMODE):
          for (int i=-10; i<10; i++) {
            for (int j=-10; j<10; j++) {
              Vector2 dirVec = Vector2Subtract(mouseTrack, percievedMouse);
              dirVec.x /= 20;
              dirVec.y /= 20;
              dirVec.x += rand()%4 - 2;
              dirVec.y += rand()%4 - 2;
              push(createMassObject((Vector2){mouseTrack.x + 50*i + rand()%500-250, mouseTrack.y + 50*j + rand()%500-250}, dirVec, 8), mass_objects);
            }
          }
        break;
      }
    }
  }


}

