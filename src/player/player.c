#include <raylib.h>
#include <raymath.h>
#include "player.h"

int mouse_down_flag = 0;


void player_control(Camera2D *cam) {

  if (IsKeyDown(KEY_A)) { cam->target.x -= 5; }
  if (IsKeyDown(KEY_D)) { cam->target.x += 5; }
  if (IsKeyDown(KEY_W)) { cam->target.y -= 5; }
  if (IsKeyDown(KEY_S)) { cam->target.y += 5; }
  cam->zoom += 0.5 * cam->zoom * GetMouseWheelMove();
  cam->offset = (Vector2){GetScreenWidth()/2, GetScreenHeight()/2};


  // if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
  //   mouse_down_flag = 0;
  //   Vector2 dirVec = Vector2Subtract(mouseTrack, percievedMouse);
  //   dirVec.x /= 50;
  //   dirVec.y /= 50;
  //   MassObject obj = createMassObject(mouseTrack, dirVec, 10);
  //   push(obj, mass_objects);
  // }

}

