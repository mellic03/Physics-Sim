#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <stdbool.h>
#include "player.h"
#include "../physics/phystools.h"
#include "../physics/physics.h"
#include "../physics/gamemath.h"
#include "../ui/ui.h"

int mouse_down_flag = 0;
Vector2 mouseTrack = {0, 0};
Vector2 percievedMouse = {0, 0};

bool is_following_MassObject = false;
int index_to_follow = 0;


void player_control(Camera2D *cam, Vector2 percievedMouse) {

  if (is_following_MassObject) {
    cam->target = mass_objects[index_to_follow].pos;
    DrawRectangle(mass_objects[index_to_follow].pos.x, mass_objects[index_to_follow].pos.y, 20, 20, (Color){255, 0, 0, 2});
  }

  else {
    if (IsKeyDown(KEY_A)) { cam->target.x -= 5 / cam->zoom; }
    if (IsKeyDown(KEY_D)) { cam->target.x += 5 / cam->zoom; }
    if (IsKeyDown(KEY_W)) { cam->target.y -= 5 / cam->zoom; }
    if (IsKeyDown(KEY_S)) { cam->target.y += 5 / cam->zoom; }
  }
  if (IsKeyDown(KEY_R)) { is_following_MassObject = false; }
  if (IsKeyDown(KEY_T)) { cam->target = (Vector2){0, 0}; }

  cam->zoom += 0.2 * cam->zoom * GetMouseWheelMove();
  cam->offset = (Vector2){GetScreenWidth()/2, GetScreenHeight()/2};

  if (GetMouseX() > 400 || GetMouseY() > 100) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      if (mouse_down_flag == 0) {
        mouseTrack = percievedMouse;
        mouse_down_flag = 1;
      }
      // Vector2 test = rotateVectorAboutPoint(percievedMouse, mouseTrack);
      // DrawLine(mouseTrack.x, mouseTrack.y, test.x, test.y, BLUE);

      switch (tool_mode) {
        case (GELMODE):
          create_gel_particle(percievedMouse, (Vector2){0, 0});
        break;
      }

    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
      switch (tool_mode) {
        case (GELMODE):
          push_gel_particles(percievedMouse);
        break;
      }

    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      mouse_down_flag = 0;

      MassObject obj;

      switch (tool_mode) {
        case (SINGLEMODE):
          Vector2 dirVec = Vector2Subtract(mouseTrack, percievedMouse);
          dirVec.x /= 50;
          dirVec.y /= 50;
          createMassObject(mouseTrack, dirVec, 10);
        break;

        case (MATRIXMODE):
          for (int i=-10; i<10; i++) {
            for (int j=-10; j<10; j++) {
              Vector2 dirVec = Vector2Subtract(mouseTrack, percievedMouse);
              dirVec.x /= 20;
              dirVec.y /= 20;
              dirVec.x += rand()%4 - 2;
              dirVec.y += rand()%4 - 2;

              createMassObject(
                (Vector2){
                  mouseTrack.x + 50*i + rand()%500-250,
                  mouseTrack.y + 50*j + rand()%500-250
                },
                dirVec,
                rand()%15 + 5
              );
            }
          }
        break;



        case (FOLLOWMODE):
          for (int i=0; i<MAX_MASS_OBJECTS; i++) {
            if (Vector2Distance(percievedMouse, mass_objects[i].pos) < mass_objects[i].radius) {
              is_following_MassObject = true;
              index_to_follow = i;
            }
          }
        break;
      }
    }
  }


}

void player_ui(void) {
  if (is_following_MassObject)
  draw_massobject_info_window(index_to_follow);
}

