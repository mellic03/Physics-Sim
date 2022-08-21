#include "phystools.h"
#include "physics.h"
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamemath.h"

// Update the positions of all MassObjects.
void updateMassObjects(MassObject arr[]) {
  for (int i=0; i<mass_object_count+1; i++) {
    for (int j=0; j<mass_object_count+1; j++) {
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

void drawMassObjects(void) {
  for (int i=0; i<mass_object_count+1; i++) {
    if (mass_objects[i].mass != 0) {
      DrawCircleV(mass_objects[i].pos, mass_objects[i].radius, BLUE);
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

int wall_left   = -700;
int wall_right  =  700;
int wall_top    = -700;
int wall_bottom =  700;

void update_gel_particles(void) {

  for (int i=0; i<gel_particle_count; i++) {
    for (int j=0; j<gel_particle_count; j++) {
      if (i != j) {
        float dist = Vector2Distance(gel_particles[i].pos, gel_particles[j].pos);
        attract_gel(&gel_particles[i], gel_particles[j], VLIQUID_PULL_RADIUS, VLIQUID_PULL_STRENGTH, VLIQUID_PUSH_RADIUS, VLIQUID_PUSH_STRENGTH);
      }
    }


    gel_particles[i].vel = Vector2Scale(gel_particles[i].vel, 0.98);
    gel_particles[i].pos = Vector2Add(gel_particles[i].pos, gel_particles[i].vel);

    // Gravity
    // gel_particles[i].vel.y += 0.001;

    // Keep in bounds
    if (gel_particles[i].pos.x > wall_right)
      gel_particles[i].pos.x = wall_right-1;
    else if (gel_particles[i].pos.x < wall_left)
      gel_particles[i].pos.x = wall_left+1;
    if (gel_particles[i].pos.y > wall_bottom)
      gel_particles[i].pos.y = wall_bottom-1;
    else if (gel_particles[i].pos.y < wall_top)
      gel_particles[i].pos.y = wall_top+1;
  }
}

void draw_gel_particles(void) {
  // Draw bounding box
  DrawLine(wall_left, wall_top, wall_right, wall_top, WHITE);
  DrawLine(wall_right, wall_top, wall_right, wall_bottom, WHITE);
  DrawLine(wall_right, wall_bottom, wall_left, wall_bottom, WHITE);
  DrawLine(wall_left, wall_bottom, wall_left, wall_top, WHITE);

  for (int i=0; i<gel_particle_count; i++) {
    DrawCircleV(gel_particles[i].pos, 5, (Color){200, 200, 200, 255});
    for (int j=0; j< gel_particle_count; j++) {
      float dist = Vector2Distance(gel_particles[i].pos, gel_particles[j].pos);
      if (dist <= 1.5*VLIQUID_PUSH_RADIUS) {
        DrawLineV(gel_particles[i].pos, gel_particles[j].pos, (Color){0, 150, 255, 255});
      }
    }
  }

}