#ifndef UI_H
#define UI_H

#include <raylib.h>

#define SINGLEMODE 0
#define ARRAYMODE 1
#define MATRIXMODE 2
#define SPINMODE 3
#define FOLLOWMODE 4

extern int tool_mode;

typedef struct Button {
  int x, y;
  int w, h;
  char text[32];
  Color color;
} Button;

void draw_tool_menu(void);
void draw_massobject_info_window(int index_of_massobject);

#endif /* UI_H */
