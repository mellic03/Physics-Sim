#ifndef UI_H
#define UI_H

#include <raylib.h>

#define SINGLEMODE 0
#define ARRAYMODE  1
#define MATRIXMODE 2
#define SPINMODE   3
#define FOLLOWMODE 4
#define GELMODE    5

extern int tool_mode;

typedef struct Button {
  int x, y;
  int w, h;
  char text[32];
  Color color;
} Button;

typedef struct Slider {
  int value_to_change;
  int step_size;
  int min, max;
} Slider;


void draw_tool_menu(void);
void draw_massobject_info_window(int index_of_massobject);

#endif /* UI_H */
