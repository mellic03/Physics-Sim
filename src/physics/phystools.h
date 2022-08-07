#ifndef PHYSTOOLS_H
#define PHYSTOOLS_H
#include "physics.h"

void setDefaultMassObjectArray(MassObject arr[]);

void deleteMassObject(int index, MassObject arr[]);

int push(MassObject obj, MassObject arr[]);

void updateMassObjects(MassObject arr[]);

void drawMassObjects(MassObject arr[]);

#endif /* PHYSTOOLS_H */