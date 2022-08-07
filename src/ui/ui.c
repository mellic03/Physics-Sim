#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include "ui.h"

int tool_mode = 0;

void draw_button(Button btn) {
  DrawRectangle(btn.x, btn.y, btn.w, btn.h, btn.color);
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
  
  Button single = {0, 25, 50, 50, BLUE}; // Single MassObject
  Button array = {100, 25, 50, 50, GREEN}; // Matrix of MassObjects

  draw_button(single);
  if (button_is_clicked(single)) {
    tool_mode = SINGLEMODE;
  }

  draw_button(array);
  if (button_is_clicked(array)) {
    tool_mode = MATRIXMODE;
  }
}


