#ifndef UI_H
#define UI_H

#include <raylib.h>

#define SINGLEMODE 0
#define ARRAYMODE 1
#define MATRIXMODE 2

typedef struct Button {
  int x, y;
  int w, h;
  Color color;
} Button;

void draw_button(Button btn);
void draw_tool_menu(void);

#endif /* UI_H */
