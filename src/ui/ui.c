#include <raylib.h>
#include <raymath.h>
#include "ui.h"
#include "../physics/physics.h"
#include "../physics/phystools.h"

int tool_mode = 5;

void draw_button(Button btn, int mode) {
  DrawRectangle(btn.x, btn.y, btn.w, btn.h, btn.color);
  DrawText(btn.text, btn.x, btn.y, 24, BLACK);
  if (tool_mode == mode) {
    DrawCircle(btn.x+btn.w/2, btn.y+50, 10, BLACK);
  }
}

int button_is_clicked(Button btn) {
  int mx = GetMouseX();
  int my = GetMouseY();
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && mx > btn.x && mx < btn.x+btn.w && my > btn.y && my < btn.y+btn.h) {
    return 1;
  }
  return 0;
}

void draw_tool_menu(void) {
  DrawRectangle(0, 0, 400, 100, WHITE);

  Button single = {25, 25, 50, 50, "single", BLUE}; // Single MassObject
  Button matrix = {125, 25, 50, 50, "matrix", GREEN}; // Matrix of MassObjects
  Button gel = {225, 25, 50, 50, "gel", YELLOW};
  Button follow = {325, 25, 50, 50, "follow", VIOLET};

  draw_button(single, SINGLEMODE);
  if (button_is_clicked(single)) {
    tool_mode = SINGLEMODE;
  }

  draw_button(matrix, MATRIXMODE);
  if (button_is_clicked(matrix)) {
    tool_mode = MATRIXMODE;
  }
  
  draw_button(gel, GELMODE);
  if (button_is_clicked(gel)) {
    tool_mode = GELMODE;
  }

  draw_button(follow, FOLLOWMODE);
  if (button_is_clicked(follow)) {
    tool_mode = FOLLOWMODE;
  }
}

void draw_massobject_info_window(int i) {

  DrawRectangle(0, 100, 400, 400, GRAY);
  
  DrawText(TextFormat("\nobjects: %d\nmass: %0.1f\nradius: %0.1f", mass_object_count, mass_objects[i].mass, mass_objects[i].radius), 25, 100, 24, BLACK);

  Button create_ring = {25, 250, 50, 50, "create ring", BLUE};
  draw_button(create_ring, SPINMODE);
  if (button_is_clicked(create_ring)) {
    create_massobject_ring(mass_objects[i].pos, mass_objects[i].mass, mass_objects[i].radius);
  }

}

