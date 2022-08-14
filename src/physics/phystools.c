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


int wall_left = -500;
int wall_right = 1000;
int wall_bottom = 500;

void update_gel_particles(void) {

  for (int i=0; i<gel_particle_count; i++) {
    for (int j=0; j<gel_particle_count; j++) {
      if (i != j) {
        float dist = Vector2Distance(gel_particles[i].pos, gel_particles[j].pos);
        attract_gel(&gel_particles[i], gel_particles[j], VLIQUID_PULL_RADIUS, VLIQUID_PULL_STRENGTH, VLIQUID_PUSH_RADIUS, VLIQUID_PUSH_STRENGTH);
      }
    }

    // Gravity
    // gel_particles[i].pos.y += 1;

    // Keep in bounds
    // if (gel_particles[i].pos.x > wall_right)
    //   gel_particles[i].pos.x = wall_right-1;
    // else if (gel_particles[i].pos.x < wall_left)
    //   gel_particles[i].pos.x = wall_left+1;
    // if (gel_particles[i].pos.y > wall_bottom)
    //   gel_particles[i].pos.y = wall_bottom-1; 
  }
}

void draw_gel_particles(void) {
  // DrawRectangle(wall_left, -5000, -wall_left+wall_right, 5000 + wall_bottom, BLACK);
  for (int i=0; i<gel_particle_count; i++) {
    // DrawPixelV(gel_particles[i].pos, (Color){200, 200, 200, 255});
    for (int j=0; j< gel_particle_count; j++) {
      float dist = Vector2Distance(gel_particles[i].pos, gel_particles[j].pos);
      if (dist < VLIQUID_PUSH_RADIUS + 50) {
        DrawLineV(gel_particles[i].pos, gel_particles[j].pos, (Color){0, 150, 255, 255-(1.7*dist)});
      }
    }
  }

}