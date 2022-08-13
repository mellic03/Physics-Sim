#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "../physics/physics.h"

void player_control(Camera2D *cam, Vector2 percievedMouse);
void player_ui(void);


#endif /* PLAYER_H */
