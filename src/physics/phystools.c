#include "phystools.h"
#include "physics.h"
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamemath.h"


// Update the positions of all MassObjects.
void updateMassObjects(MassObject arr[]) {
  for (int i=0; i<current_mass_object_count+1; i++) {
    for (int j=0; j<current_mass_object_count+1; j++) {
      if (i!=j && arr[i].mass!=0 && arr[j].mass!=0) {

        float dist = Vector2Distance(arr[i].pos, arr[j].pos);

        if (dist < arr[i].radius + arr[j].radius) {
          Vector2 momentum = Vector2Add(Vector2Scale(arr[i].vel, arr[i].mass), Vector2Scale(arr[j].vel, arr[j].mass));
          if (arr[i].mass >= arr[j].mass) {
            arr[i].mass += arr[j].mass;
            arr[i].vel = Vector2Scale(momentum, (1/arr[i].mass));
            deleteMassObject(j, arr);
          }
          arr[i].radius = shitsqrt(arr[i].mass/PI);
        }

        else {
          attract(&arr[i], arr[j], dist);
        }

      }
    }
    arr[i].pos = Vector2Add(arr[i].pos, arr[i].vel);
  }
}

void drawMassObjects(MassObject arr[]) {
  for (int i=0; i<current_mass_object_count+1; i++) {
    if (arr[i].mass != 0) {
      DrawCircleV(arr[i].pos, arr[i].radius, BLUE);
    }
  }
}

void create_massobject_ring(Vector2 pos, float mass, float r) {
  for (int i=-500; i<500; i+=140) {
    for (int j=-500; j<500; j+=140) {
      if (rand()%2 == 1) {
        Vector2 a = {pos.x + i, pos.y + j};
        Vector2 b = Vector2Subtract(a, pos);
        float dist_from_mouse = Vector2Distance(pos, a);
        Vector2 dirVec = {b.y, -b.x};
        dirVec = Vector2Normalize(dirVec);
        float scale = shitsqrt((G*mass) / dist_from_mouse);
        dirVec = Vector2Scale(dirVec, scale);
        createMassObject(a, dirVec, 1);
      }
    }
  }
}

