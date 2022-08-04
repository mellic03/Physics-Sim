#!/bin/sh
gcc ./src/player/player.c ./src/physics/physics.c ./src/main.c -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
