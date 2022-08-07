#!/bin/sh
gcc ./src/physics/gamemath.c ./src/player/player.c ./src/physics/physics.c ./src/physics/phystools.c ./src/main.c -o main -lraylib -lGL -lm -lpthread -ldl -lrt -O3 -lX11
